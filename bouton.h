/**
 * @file bouton.h
 * @brief Interface de gestion des boutons de la borne
 * 
 * Définit la structure Bouton et les fonctions pour accéder
 * aux boutons physiques de la borne.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef BOUTON_H
#define BOUTON_H

#include "donnees_borne.h"
#include "memoire_borne.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @struct Bouton
 * @brief Structure représentant un bouton
 * 
 * Équivalent en C de la classe C++ Bouton.
 * Contient un pointeur vers les entrées partagées (boutons physiques)
 * et l'identifiant de la mémoire partagée.
 */
typedef struct {
    entrees* bio;   /**< Pointeur vers les entrées partagées (boutons physiques) */
    int bshmid;     /**< Identifiant de la mémoire partagée */
} Bouton;

/**
 * @brief Initialise la structure Bouton
 * 
 * Équivalent du constructeur.
 * 
 * @param b Pointeur vers la structure Bouton à initialiser
 * @return void
 */
void Bouton_init(Bouton* b);

/**
 * @brief Retourne l'état du bouton de charge
 * 
 * @param b Pointeur vers la structure Bouton
 * @return L'état du bouton de charge (1 si enfoncé, 0 sinon)
 */
int lireBoutonCharge(Bouton* b);

/**
 * @brief Retourne l'état du bouton d'arrêt
 * 
 * @param b Pointeur vers la structure Bouton
 * @return L'état du bouton stop (1 si enfoncé, 0 sinon)
 */
int lireBoutonStop(Bouton* b);

/**
 * @brief Initialise les boutons et l'accès à la mémoire partagée
 * 
 * @param b Pointeur vers la structure Bouton
 * @return void
 */
void boutonsInitialise(Bouton* b);

#endif // BOUTON_H
