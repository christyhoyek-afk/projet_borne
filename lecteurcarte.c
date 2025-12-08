#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <voyant.h>
#include "baseclient.h"
#include "mode.h"
#include <string.h>
#include <donnees_borne.h>
#include "Generateur_save.h"
#include "bouton.h"

/* module-level flag indicating whether voyants were initialized */
static int voyants_ok = 0;
/* Instance globale du bouton */
static Bouton bouton_charge;

void lecteurcarte_initialiser()
{
	initialisations_ports();
	/* initialise voyants and record status so other functions can test it */
	voyants_ok = voyant_initialisation();
	/* Initialiser le bouton CHARGE */
	Bouton_init(&bouton_charge);
	boutonsInitialise(&bouton_charge);
}

/* Attend l'insertion et retourne le numero lu (ou <= 0 en erreur) */
int lecteurcarte_obtenir_numero(void)
{
	attente_insertion_carte();
	int numero = lecture_numero_carte();
	return numero;
}

void lecteurcarte_attendre_retrait(void)
{
	printf("Veuillez retirer votre carte...\n");
    /* Attend le retrait de la carte (simulation : appuyer sur Entrée) */
	attente_retrait_carte();
	printf("Carte retirée.\n");
}

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
			
			/* Éteindre voyant disponible et attendre le bouton CHARGE */
			voyant_setdisponible(OFF);
			printf("En attente du bouton CHARGE...\n");
			
			/* Boucle d'attente : lire l'état du bouton CHARGE */
			int bouton_enfonce = 0;
			while (!bouton_enfonce) {
				int etat = lireBoutonCharge(&bouton_charge);
				printf("État du bouton CHARGE : %d\n", etat);
				if (etat) {
					bouton_enfonce = 1;
				} else {
					usleep(100000); /* Vérifier tous les 100ms */
				}
			}
			
			printf("Bouton CHARGE enfoncé. Démarrage de la charge...\n");
			
			/* Le générateur gère la charge complète */
			Generateur_save_chargement_VH();
			
			/* Récupération de la voiture */
			Gnenerateur_save_recuperation_VH();
			
		} else {
			/* Mode gestion : carte reconnue dans la base */
			printf("Mode gestion base client actif. Carte reconnue.\n");
			printf("Veuillez retirer votre carte.\n");
			lecteurcarte_attendre_retrait();
		}
	} else {
		if (current_mode == 1) {
			/* Mode gestion : enregistrer le nouveau client */
			baseclient_interactive_enregistrer(numero);
		} else {
			/* Mode charge : refuser l'accès */
			voyant_setdisponible(ROUGE);
			printf("Accès refusé. Veuillez contacter le support.\n");
			printf("Veuillez retirer votre carte.\n");
			lecteurcarte_attendre_retrait();
		}
	}
}

