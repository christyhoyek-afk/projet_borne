#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <voyant.h>
#include "baseclient.h"
#include "mode.h"
#include <string.h>
#include <donnees_borne.h>

void lecteurcarte_initialiser()
{
    initialisations_ports();
}

/* Attend l'insertion et retourne le numero lu (ou <= 0 en erreur) */
int lecteurcarte_obtenir_numero(void)
{
    attente_insertion_carte();
    int numero = lecture_numero_carte();
    return numero;
}

void lecteurcarte_lire_carte()
{
    attente_insertion_carte();
    printf("Carte insérée ?.\n");
    int numero = lecture_numero_carte();
    printf("Votre numéro de carte : %d\n", numero);

    if(carte_inseree && voyant_initialisation)
    {
        voyant_setdisponible(VERT);
        int auth = baseclient_authentifier(numero);
        printf("Authentification %s\n", auth ? "réussie" : "échouée");

        if (auth) {
            if (current_mode == 2) {
                for(int i=0; i<8; i++)
                    voyant_setcharge(ON);
                printf("Accès autorisé. Chargement en cours...\n");
                sleep(1); /* simuler */
                voyant_setcharge(OFF);
                voyant_setdisponible(OFF);
            } else {
                printf("Mode gestion base client actif. Carte reconnue.\n");
            }
        } else {
            if (current_mode == 1) {
                /* En mode gestion : appeler la fonction interactive d'enregistrement */
                baseclient_interactive_enregistrer(numero);
            } else {
                voyant_setdisponible(ROUGE);
                printf("Accès refusé. Veuillez contacter le support.\n");
            }
        }
    }
    else
    {
        voyant_setdisponible(ROUGE);
        printf("Erreur de lecture de carte.\n");
    }

}

