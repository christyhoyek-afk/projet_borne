#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <voyant.h>
#include "baseclient.h"
#include <donnees_borne.h>

void lecteurcarte_initialiser()
{
    initialisations_ports();
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
    }
    else
    {
        voyant_setdisponible(ROUGE);
        printf("Erreur de lecture de carte.\n");


    }

   
}

