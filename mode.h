/**
 * @file mode.h
 * @brief Sélecteur de mode global pour la borne
 * 
 * Définit la variable globale current_mode qui détermine
 * le mode de fonctionnement de la borne :
 * - 1 = gestion base client
 * - 2 = mode charge
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#ifndef MODE_H
#define MODE_H

/** 
 * @brief Mode de fonctionnement actuel
 * @details 1 = gestion base client, 2 = charge 
 */
extern int current_mode;

#endif
