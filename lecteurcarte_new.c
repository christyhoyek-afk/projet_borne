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
#include "prise.h"

/* module-level flag indicating whether voyants were initialized */
static int voyants_ok = 0;

void lecteurcarte_initialiser()
{
	initialisations_ports();
	/* initialise voyants and record status so other functions can test it */
	voyants_ok = voyant_initialisation();
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
	/* Attend le retrait de la carte (simulation : appuyer sur Entrée) */
	printf("Appuyez sur Entrée pour confirmer le retrait de la carte : ");
	fflush(stdout);
	char dummy[32];
	fgets(dummy, sizeof(dummy), stdin);
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
			/* Mode charge : exécuter la procédure de charge */
			printf("Carte reconnue. Démarrage de la charge...\n");
			Generateur_save_chargement_VH();
			Gnenerateur_save_recuperation_VH();
			printf("Veuillez retirer votre carte.\n");
			lecteurcarte_attendre_retrait();
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
