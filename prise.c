/**
 * @file prise.c
 * @brief Gestion de la prise et de la trappe de la borne
 * 
 * Ce module gère le verrouillage/déverrouillage de la trappe
 * et le contrôle des LEDs associées via la mémoire partagée.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include "voyant.h"
#include "prise.h"

/** @brief Pointeur vers la mémoire partagée */
entrees * iop = NULL; 
/** @brief Identifiant de la mémoire partagée */
int shmidp;

/**
 * @brief Initialise l'accès à la structure de la prise
 * 
 * Accède à la mémoire partagée pour contrôler la prise et la trappe.
 * Quitte le programme en cas d'échec d'accès.
 * 
 * @return void
 */
void Prise_initialisation(void)
{
	
        iop = acces_memoire(&shmidp);
 	if(iop == NULL){
		printf("acces a la prise refuse\n");
		exit(1);
	}
	/*else
	        printf("acces a la prise avec succes\n");*/		
	
}

/**
 * @brief Déverrouille la trappe de la prise
 * 
 * Allume la LED de la trappe en vert pour indiquer que la trappe
 * est déverrouillée.
 * 
 * @return void
 */
void Prise_deverouiller_trape(void)
{
	iop->led_trappe = VERT;
}

/**
 * @brief Verrouille la trappe de la prise
 * 
 * Éteint la LED de la trappe pour indiquer que la trappe
 * est verrouillée.
 * 
 * @return void
 */
void Prise_veroiller_trape(void)
{
	iop->led_trappe = OFF;/*trape verouillee*/

}

/**
 * @brief Contrôle la LED de la trappe
 * 
 * Cette fonction semble contrôler la LED de la prise plutôt que
 * celle de la trappe (possible erreur dans le code original).
 * 
 * @param led_trappe État de la LED à appliquer
 * @return void
 */
void prise_led_trappe(led led_trappe)
{
	iop->led_prise = VERT;
}
