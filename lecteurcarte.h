/**
 * @file lecteurcarte.h
 * @brief Interface du lecteur de carte
 * 
 * Définit les fonctions pour gérer la lecture des cartes,
 * l'authentification et le processus de charge.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H
#include <lcarte.h>

/**
 * @brief Initialise le lecteur de carte et les composants associés
 * @return void
 */
void lecteurcarte_initialiser();

/**
 * @brief Lit une carte et gère le processus complet (authentification, charge)
 * @return void
 */
void lecteurcarte_lire_carte();

/**
 * @brief Attend l'insertion d'une carte (déclarée ailleurs)
 * @return void
 */
void attente_insertion_carte();

/**
 * @brief Obtient le numéro d'une carte insérée
 * @return Le numéro de carte
 */
int lecteurcarte_obtenir_numero(void);

/**
 * @brief Attend que l'utilisateur retire sa carte
 * @return void
 */
void lecteurcarte_attendre_retrait(void);

#endif // LECTEURCARTE_H
