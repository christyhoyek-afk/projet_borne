/**
 * @file prise.h
 * @brief Interface de gestion de la prise
 * 
 * Définit les fonctions pour initialiser et contrôler
 * le verrouillage/déverrouillage de la trappe.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef PRISE_H
#define PRISE_H

/**
 * @brief Initialise l'accès à la structure de la prise
 * @return void
 */
void Prise_initialisation(void);

/**
 * @brief Déverrouille la trappe de la prise
 * @return void
 */
void Prise_deverouiller_trape(void);

/**
 * @brief Verrouille la trappe de la prise
 * @return void
 */
void Prise_veroiller_trape(void);

#endif
