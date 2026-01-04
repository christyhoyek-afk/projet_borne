/**
 * @file Generateur_save.h
 * @brief Interface du générateur de tension
 * 
 * Déclare les fonctions pour contrôler le générateur de tension,
 * gérer le processus de charge et la récupération du véhicule.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef GENERATEUR_H
#define GENERATEUR_H

/**
 * @brief Initialise le générateur
 * @return void
 */
void Generateur_save_initialisation (void);

/**
 * @brief Gère le processus de chargement du véhicule
 * @return void
 */
void Generateur_save_chargement_VH(void);

/**
 * @brief Gère la récupération du véhicule
 * @return void
 */
void Gnenerateur_save_recuperation_VH(void);

/**
 * @brief Génère une tension spécifique
 * @param tension Type de tension à générer
 * @return void
 */
void Generateur_save_Gentension(pwm tension);

/**
 * @brief Mesure la tension actuelle
 * @return Valeur de la tension mesurée
 */
int Generateur_save_Valtension(void);

/**
 * @brief Contrôle l'état du contacteur AC
 * @param etat État du contacteur (0 = ouvert, 1 = fermé)
 * @return void
 */
void Generateur_save_ACEtat(int etat);

#endif 
// GENERATEUR_H