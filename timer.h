/**
 * @file timer.h
 * @brief Interface du timer
 * 
 * Définit les fonctions pour initialiser le timer,
 * le réinitialiser, lire sa valeur et créer des délais.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef TIMER_H 
#define TIMER_H

/**
 * @brief Initialise l'accès au timer
 * @return void
 */
void timer_initialisation(void);

/**
 * @brief Réinitialise le timer au temps actuel
 * @return void
 */
void timer_raze(void);

/**
 * @brief Retourne le temps écoulé depuis le dernier timer_raze
 * @return Temps écoulé en secondes
 */
int timer_valeur(void);

/**
 * @brief Crée un délai bloquant
 * @param t Durée du délai en secondes
 * @return void
 */
void delay (int t);

#endif