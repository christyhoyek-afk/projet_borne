
#include <stdio.h>
#include <stdlib.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <unistd.h> /* pour usleep */
#include "voyant.h"

int shmid;
entrees *io = NULL; /* accès à la structure de l'interface borne */

/* Initialise l'accès aux voyants ; retourne 1 si OK, 0 sinon. */
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

/* changement voyant charge */
void voyant_setcharge(led led_charge)
{
	io->led_charge = led_charge;
}

/* changement voyant disponible */
void voyant_setdisponible(led led_dispo)
{
	io->led_dispo = led_dispo;
}

/* changement voyant defaut */
void voyant_setdefaut(led led_defaut)
{
	io->led_defaut = led_defaut;
}

/* changement voyant prise rangee */
void voyant_setpriseR(led led_PR)
{
	io->led_prise = led_PR;
}

/* changement voyant trappe */
void voyant_settrappe(led led_trappe)
{
	io->led_trappe = led_trappe;
}

/* clignotement du voyant charge */
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

/* clignotement du voyant defaut */
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


