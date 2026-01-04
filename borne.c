/**
 * @file borne.c
 * @brief Programme principal de la borne de recharge
 * 
 * Ce module contient le point d'entrée principal du système de borne de recharge.
 * Il gère deux modes de fonctionnement :
 * - Mode 1 : Gestion de la base de données clients (ajout, suppression, modification)
 * - Mode 2 : Mode charge (lecture de carte et recharge)
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

#include "lecteurcarte.h"
#include "voyant.h"
#include "Generateur_save.h"
#include "baseclient.h"
#include "prise.h"
#include "mode.h"
#include <stdlib.h>

/** @brief Mode de fonctionnement actuel de la borne (1=gestion, 2=charge) */
int current_mode = 2; /* default: charge mode */

/**
 * @brief Point d'entrée principal de l'application borne
 * 
 * Initialise tous les composants de la borne (lecteur de carte, générateur, prise)
 * puis entre dans une boucle infinie qui :
 * - Affiche le menu principal permettant de choisir entre mode gestion et mode charge
 * - En mode charge (2) : lit la carte et procède à la recharge si le client existe
 * - En mode gestion (1) : affiche un sous-menu pour ajouter, supprimer ou modifier des clients
 * 
 * @return 0 en cas de sortie normale (jamais atteint dans la boucle infinie)
 */
int main()
{
	/* Initialisation des composants */
	lecteurcarte_initialiser();
	Generateur_save_initialisation();
	Prise_initialisation();

	while (1)
	{
		/* Menu principal : choisir le mode */
		printf("\n--- Menu ---\n1 - Gérer la base client\n2 - Charger\nChoix : ");
		char buf[16] = {0};
		if (fgets(buf, sizeof(buf), stdin) == NULL) continue;
		int choix = atoi(buf);
		if (choix == 1 || choix == 2) current_mode = choix;
		else {
			printf("Choix invalide, maintien du mode actuel (%d).\n", current_mode);
		}

		if (current_mode == 2) {
			/* Mode charge : procéder à la lecture et recharge si la carte existe */
			printf("Mode charge sélectionné. Insérez la carte...\n");
			lecteurcarte_lire_carte();
		} else {
			/* Mode gestion base client : afficher sous-menu */
			int gestion_active = 1;
			while (gestion_active) {
				printf("\n-- Gestion Base Client --\n1 - Ajouter\n2 - Supprimer\n3 - Modifier\n4 - Exit\nChoix : ");
				char b2[16] = {0};
				if (fgets(b2, sizeof(b2), stdin) == NULL) break;
				int s = atoi(b2);
				if (s == 4) { gestion_active = 0; break; }
				if (s < 1 || s > 4) { printf("Choix invalide.\n"); continue; }

				/* Lire le numero depuis le lecteur de carte (insertion physique) */
				printf("Insérez la carte pour l'opération...\n");
				int num = lecteurcarte_obtenir_numero();
				if (num <= 0) { printf("Lecture invalide ou annulee.\n"); continue; }

				if (s == 1) {
					/* Ajouter */
					baseclient_interactive_enregistrer(num);
				} else if (s == 2) {
					/* Supprimer */
					baseclient_interactive_supprimer(num);
				} else if (s == 3) {
					/* Modifier */
					baseclient_interactive_modifier(num);
				}
			}
		}
	}

	return 0;
}
