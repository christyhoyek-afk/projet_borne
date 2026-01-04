/**
 * @file voyant.c
 * @brief Gestion des voyants LED de la borne
 * 
 * Ce module gère tous les voyants (LEDs) de la borne de recharge :
 * voyant de charge, disponibilité, défaut, prise rangée et trappe.
 * Il fournit aussi des fonctions de clignotement.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <unistd.h> /* pour usleep */
#include "voyant.h"

/** @brief Identifiant de la mémoire partagée */
int shmid;
/** @brief Pointeur vers la structure de l'interface borne */
entrees *io = NULL; /* accès à la structure de l'interface borne */

/**
 * @brief Initialise l'accès aux voyants
 * 
 * Récupère l'adresse mémoire de la borne et initialise tous
 * les voyants à leur état par défaut.
 * 
 * @return 1 si l'initialisation réussit, 0 en cas d'erreur
 */
int voyant_initialisation()
{
	io = acces_memoire(&shmid); /* récupération de l'adresse mémoire de la borne */
	if (io == NULL) {
		printf("acces par les voyants refuse\n");
		return 0;
	}

	/* Éteindre / mettre à l'état initial toutes les LED */
	voyant_setcharge(OFF);
	voyant_setdisponible(VERT);
	voyant_setdefaut(OFF);
	voyant_setpriseR(OFF);

	return 1;
}

/**
 * @brief Change l'état du voyant de charge
 * 
 * @param led_charge Nouvel état du voyant (VERT, ROUGE, OFF)
 * @return void
 */
void voyant_setcharge(led led_charge)
{
	io->led_charge = led_charge;
}

/**
 * @brief Change l'état du voyant de disponibilité
 * 
 * @param led_dispo Nouvel état du voyant (VERT, ROUGE, OFF)
 * @return void
 */
void voyant_setdisponible(led led_dispo)
{
	io->led_dispo = led_dispo;
}

/**
 * @brief Change l'état du voyant de défaut
 * 
 * @param led_defaut Nouvel état du voyant (VERT, ROUGE, OFF)
 * @return void
 */
void voyant_setdefaut(led led_defaut)
{
	io->led_defaut = led_defaut;
}

/**
 * @brief Change l'état du voyant de prise rangée
 * 
 * @param led_PR Nouvel état du voyant (VERT, ROUGE, OFF)
 * @return void
 */
void voyant_setpriseR(led led_PR)
{
	io->led_prise = led_PR;
}

/**
 * @brief Change l'état du voyant de trappe
 * 
 * @param led_trappe Nouvel état du voyant (VERT, ROUGE, OFF)
 * @return void
 */
void voyant_settrappe(led led_trappe)
{
	io->led_trappe = led_trappe;
}

/**
 * @brief Fait clignoter le voyant de charge
 * 
 * Allume et éteint le voyant de charge 8 fois avec un intervalle
 * de 0,5 seconde.
 * 
 * @return void
 */
void voyant_toggle_charge(void)
{
	int i;
	for (i = 0; i < 8; i++) {
		voyant_setcharge(VERT);
		usleep(500000); /* delay 0.5s */
		voyant_setcharge(OFF);
		usleep(500000);
	}
}

/**
 * @brief Fait clignoter le voyant de défaut
 * 
 * Allume et éteint le voyant de défaut 8 fois avec un intervalle
 * de 0,5 seconde.
 * 
 * @return void
 */
void voyant_toggle_Defaut(void)
{
	int i;
	for (i = 0; i < 8; i++) {
		voyant_setdefaut(ROUGE);
		usleep(500000); /* delay 0.5s */
		voyant_setdefaut(OFF);
		usleep(500000);
	}
}


