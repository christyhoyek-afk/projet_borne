#ifndef BOUTON_H
#define BOUTON_H

#include "donnees_borne.h"
#include "memoire_borne.h"
#include <stdlib.h>
#include <unistd.h>

/*
 * Structure représentant un "Bouton" en C,
 * équivalent à la classe C++.
 */
typedef struct {
    entrees* bio;   // Pointeur vers les entrées partagées (boutons physiques)
    int bshmid;     // Identifiant de la mémoire partagée
} Bouton;

/*
 * Initialise la structure Bouton (équivalent du constructeur).
 */
void Bouton_init(Bouton* b);

/*
 * Retourne l'état du bouton de charge.
 */
int lireBoutonCharge(Bouton* b);

/*
 * Retourne l'état du bouton d'arrêt.
 */
int lireBoutonStop(Bouton* b);

/*
 * Initialise les boutons.
 */
void boutonsInitialise(Bouton* b);

#endif // BOUTON_H
