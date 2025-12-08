#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <voyant.h>
#include "baseclient.h"
#include "mode.h"
#include <string.h>
#include <donnees_borne.h>

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
	printf("Carte retirée");

}

void lecteurcarte_attendre_retrait(void)
{
    printf("Veuillez retirer votre carte.\n");
    attente_retrait_carte();
    printf("Carte retirée.\n");
}

void lecteurcarte_lire_carte()
{
    attente_insertion_carte();
    printf("Carte insérée ?.\n");
    int numero = lecture_numero_carte();
    printf("Votre numéro de carte : %d\n", numero);
    voyant_setdisponible(VERT);

    /* carte valide si numéro lu et voyants init OK */
    if (numero >= 0 && voyants_ok)
    {
        int auth = baseclient_authentifier(numero);
        printf("Authentification %s\n", auth ? "réussie" : "échouée");

        if (auth) {
            if (current_mode == 2) {
                for(int i=0; i<8; i++)
                voyant_setcharge(VERT);
                printf("Accès autorisé. Chargement en cours...\n");
                sleep(100); /* simuler */
                voyant_setcharge(OFF);
                voyant_setdisponible(OFF);
                printf("Veuillez retirer votre carte.\n");
                lecteurcarte_attendre_retrait();
            } else {
                printf("Mode gestion base client actif. Carte reconnue.\n");
                printf("Veuillez retirer votre carte.\n");
                lecteurcarte_attendre_retrait();
            }
        } else {
            if (current_mode == 1) {
                /* En mode gestion : appeler la fonction interactive d'enregistrement */
                baseclient_interactive_enregistrer(numero);
                printf("Veuillez retirer votre carte.\n");
                lecteurcarte_attendre_retrait();
            } else {
                voyant_setdisponible(ROUGE);
                printf("Accès refusé. Veuillez contacter le support.\n");
                printf("Veuillez retirer votre carte.\n");
                lecteurcarte_attendre_retrait();
            }
        }
    }
    else
    {
        voyant_setdisponible(ROUGE);
        printf("Erreur de lecture de carte.\n");
        printf("Veuillez retirer votre carte.\n");
        lecteurcarte_attendre_retrait();
    }

}

