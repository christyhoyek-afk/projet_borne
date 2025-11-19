#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include <lcarte.h>
#include <lvoyant.h>

void lecteurcarte_initialiser()
{
    initialisations_ports();
}

void lecteurcarte_lire_carte()
{
    attente_insertion_carte();
    printf("Carte insérée ?.\n");
    numero= lecture_numero_carte();
    printf("Votre numéro de carte : %d\n", numero);

    if(carte_insere && voyant_dispo){
        int authentifier= base_client_authentifier(numero);
        printf("Authentification %d\n", authentifier ? "réussie" : "échouée");

    }
}

