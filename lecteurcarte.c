/**
 * @file lecteurcarte.c
 * @brief Gestion du lecteur de carte et des processus d'authentification
 * 
 * Ce module gère la lecture des cartes, l'authentification des clients,
 * et orchestre le processus complet de charge et de récupération du véhicule.
 * Il coordonne les voyants, les boutons et le générateur.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <voyant.h>
#include "baseclient.h"
#include "mode.h"
#include <string.h>
#include <time.h>
#include <donnees_borne.h>
#include "Generateur_save.h"
#include "bouton.h"

/** @brief Flag indiquant si les voyants ont été initialisés avec succès */
static int voyants_ok = 0;
/** @brief Instance globale du bouton de charge */
static Bouton bouton_charge;

/**
 * @brief Initialise le lecteur de carte et tous les composants associés
 * 
 * Initialise les ports, les voyants et le bouton de charge.
 * Enregistre le statut de l'initialisation des voyants.
 * 
 * @return void
 */
void lecteurcarte_initialiser()
{
	initialisations_ports();
	/* initialise voyants and record status so other functions can test it */
	voyants_ok = voyant_initialisation();
	/* Initialiser le bouton CHARGE */
	Bouton_init(&bouton_charge);
	boutonsInitialise(&bouton_charge);
}

/**
 * @brief Attend l'insertion d'une carte et retourne son numéro
 * 
 * Bloque jusqu'à ce qu'une carte soit insérée, puis lit et retourne
 * le numéro de la carte.
 * 
 * @return Le numéro de carte lu (ou <= 0 en cas d'erreur)
 */
int lecteurcarte_obtenir_numero(void)
{
	attente_insertion_carte();
	int numero = lecture_numero_carte();
	return numero;
}

/**
 * @brief Attend que l'utilisateur retire sa carte
 * 
 * Affiche un message demandant le retrait, attend que la carte
 * soit retirée, puis confirme le retrait.
 * 
 * @return void
 */
void lecteurcarte_attendre_retrait(void)
{
	printf("Veuillez retirer votre carte.\n");
    /* Attend le retrait de la carte (simulation : appuyer sur Entrée) */
	attente_retrait_carte();
	printf("Carte retirée.\n");
}

/**
 * @brief Fonction principale de lecture de carte et gestion du processus
 * 
 * Cette fonction orchestre tout le processus :
 * - Lecture de la carte
 * - Authentification du client
 * - En mode charge : gestion du clignotement, attente du bouton, chargement et récupération
 * - En mode gestion : gestion de l'enregistrement des nouveaux clients
 * 
 * @return void
 */
void lecteurcarte_lire_carte()
{
	attente_insertion_carte();
	printf("Carte insérée.\n");
	int numero = lecture_numero_carte();
	printf("Votre numéro de carte : %d\n", numero);

	if (numero <= 0) {
		voyant_setdisponible(ROUGE);
		printf("Erreur de lecture de carte.\n");
		printf("Veuillez retirer votre carte.\n");
		lecteurcarte_attendre_retrait();
		return;
	}

	voyant_setdisponible(VERT);
	int auth = baseclient_authentifier(numero);
	printf("Authentification %s\n", auth ? "réussie" : "échouée");

	if (auth) {
		if (current_mode == 2) {
			/* Mode charge : clignoter voyant charge, demander retrait carte, attendre bouton */
			printf("Carte reconnue. Clignotement du voyant de charge...\n");
			voyant_toggle_charge(); /* Fait clignoter le voyant charge (8 fois) */
			
			/* Demander à l'utilisateur de retirer sa carte */
			printf("Veuillez retirer votre carte avant d'appuyer sur le bouton CHARGE.\n");
			lecteurcarte_attendre_retrait();
			
			/* Allumer voyant disponible en vert et attendre le bouton CHARGE */
			voyant_setdisponible(VERT);
			printf("En attente du bouton CHARGE...\n");
			
			/* Boucle d'attente : lire l'état du bouton CHARGE */
			int bouton_enfonce = 0;
			time_t t0 = time(NULL);
			while (!bouton_enfonce) {
				int etat = lireBoutonCharge(&bouton_charge);
				printf("État du bouton CHARGE : %d\n", etat);
				if (etat) {
					bouton_enfonce = 1;
                    voyant_setdisponible(OFF);
					break;
				}
				if (time(NULL) - t0 >= 60) {
					printf("Erreur : délai d'une minute dépassé, retour au mode initial.\n");
					voyant_setdisponible(VERT);
					voyant_setcharge(OFF);
					return;
				}
				usleep(100000); /* Vérifier tous les 100ms */
			}
			
			printf("Bouton CHARGE enfoncé. Démarrage de la charge...\n");
			
			/* Le générateur gère la charge complète */
			Generateur_save_chargement_VH();

			/* Authentification à la reprise après fin de charge / arrêt (trappe bloquée tant que non auth) */
			int auth_ok = 0;
			while (!auth_ok) {
				printf("Charge terminée ou arrêtée. Insérez votre carte pour récupérer le véhicule...\n");
				attente_insertion_carte();
				int num_recup = lecture_numero_carte();
				printf("Numéro carte (reprise) : %d\n", num_recup);
				if (num_recup > 0 && baseclient_authentifier(num_recup)) {
					auth_ok = 1;
					printf("Carte reconnue. Vous pouvez récupérer le véhicule.\n");
					voyant_setdisponible(VERT);
				} else {
					printf("Carte non reconnue. Veuillez réessayer.\n");
					voyant_setdisponible(ROUGE);
				}
			}

			/* Une fois ré-authentifié, on autorise la reprise (déverrouillage prise géré par le générateur) */
			Gnenerateur_save_recuperation_VH();
            printf("Véhicule récupéré. Merci et à bientôt !\n");
			lecteurcarte_attendre_retrait();
			
		} else {
			/* Mode gestion : carte reconnue dans la base */
			printf("Mode gestion base client actif. Carte reconnue.\n");
			lecteurcarte_attendre_retrait();
		}
	} else {
		if (current_mode == 1) {
			/* Mode gestion : enregistrer le nouveau client */
			baseclient_interactive_enregistrer(numero);
		} else {
			/* Mode charge : refuser l'accès */
			voyant_toggle_Defaut();
			printf("Accès refusé. Veuillez contacter le support.\n");
			lecteurcarte_attendre_retrait();
		}
	}
}

