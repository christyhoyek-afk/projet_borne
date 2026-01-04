/**
 * @file voyant.h
 * @brief Interface de gestion des voyants LED
 * 
 * Définit les fonctions pour initialiser et contrôler
 * tous les voyants de la borne de recharge.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef VOYANT_H
#define VOYANT_H
/* Use the shared donnees_borne.h which defines 'led' and related types */
#include <donnees_borne.h>

/**
 * @brief Initialise l'accès aux voyants
 * @return 1 si succès, 0 en cas d'erreur
 */
int voyant_initialisation();

/**
 * @brief Change l'état du voyant de charge
 * @param led_charge Nouvel état du voyant
 * @return void
 */
void voyant_setcharge(led led_charge);

/**
 * @brief Change l'état du voyant de disponibilité
 * @param led_dispo Nouvel état du voyant
 * @return void
 */
void voyant_setdisponible(led led_dispo);

/**
 * @brief Change l'état du voyant de défaut
 * @param led_defaut Nouvel état du voyant
 * @return void
 */
void voyant_setdefaut(led led_defaut);

/**
 * @brief Change l'état du voyant de prise rangée
 * @param led_PR Nouvel état du voyant
 * @return void
 */
void voyant_setpriseR(led led_PR);

/**
 * @brief Change l'état du voyant de trappe
 * @param led_trappe Nouvel état du voyant
 * @return void
 */
void voyant_settrappe(led led_trappe);

/**
 * @brief Fait clignoter le voyant de charge
 * @return void
 */
void voyant_toggle_charge(void);

/**
 * @brief Fait clignoter le voyant de défaut
 * @return void
 */
void voyant_toggle_Defaut(void);

#endif
