#include "bouton.h"
#include <stdio.h>   // Remplace iostream
#include <stdlib.h>  // Pour exit()

/*
 * Equivalent du constructeur C++ :
 * initialise la structure.
 */
void Bouton_init(Bouton* b) {
    b->bio = NULL;
    b->bshmid = 0;
}

/*
 * Initialise les boutons et la mémoire partagée.
 */
void boutonsInitialise(Bouton* b) {

    // Accès à la mémoire partagée contenant les boutons
    b->bio = acces_memoire(&(b->bshmid));

    if (b->bio == NULL) {
        printf("Erreur : pas de memoire partagee\n");
        exit(1);
    }

    // Initialisation des states des boutons
    b->bio->bouton_charge = 0;
    b->bio->bouton_stop = 0;
}

/*
 * Lecture du bouton de charge.
 */
int lireBoutonCharge(Bouton* b) {
    return b->bio->bouton_charge;
}

/*
 * Lecture du bouton stop.
 */
int lireBoutonStop(Bouton* b) {
    return b->bio->bouton_stop;
}
