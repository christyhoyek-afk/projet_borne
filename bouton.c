/**
 * @file bouton.c
 * @brief Gestion des boutons de la borne de recharge
 * 
 * Ce module gère l'accès et la lecture des boutons physiques de la borne
 * (bouton de charge et bouton d'arrêt) via la mémoire partagée.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include "bouton.h"
#include <stdio.h>   // Remplace iostream
#include <stdlib.h>  // Pour exit()

/**
 * @brief Initialise la structure Bouton
 * 
 * Équivalent du constructeur C++. Initialise les champs de la structure
 * à leurs valeurs par défaut.
 * 
 * @param b Pointeur vers la structure Bouton à initialiser
 * @return void
 */
void Bouton_init(Bouton* b) {
    b->bio = NULL;
    b->bshmid = 0;
}

/**
 * @brief Initialise les boutons et l'accès à la mémoire partagée
 * 
 * Accède à la mémoire partagée contenant l'état des boutons physiques
 * et initialise leurs valeurs à 0.
 * 
 * @param b Pointeur vers la structure Bouton
 * @return void
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

/**
 * @brief Lit l'état du bouton de charge
 * 
 * @param b Pointeur vers la structure Bouton
 * @return L'état du bouton de charge (1 si enfoncé, 0 sinon)
 */
int lireBoutonCharge(Bouton* b) {
    return b->bio->bouton_charge;
}

/**
 * @brief Lit l'état du bouton d'arrêt
 * 
 * @param b Pointeur vers la structure Bouton
 * @return L'état du bouton stop (1 si enfoncé, 0 sinon)
 */
int lireBoutonStop(Bouton* b) {
    return b->bio->bouton_stop;
}
