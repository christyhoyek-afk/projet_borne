/**
 * @file timer.c
 * @brief Gestion du timer et des délais
 * 
 * Ce module fournit des fonctionnalits de temporisation en utilisant
 * la mémoire partagée pour accéder au timer du simulateur.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include<stdio.h>
#include<stdlib.h>
#include "donnees_borne.h"
#include"mem_sh.h"
#include"timer.h"

/** @brief Identifiant de la mémoire partagée du timer */
int shmidt;
/** @brief Temps de départ enregistré pour le timer */
int depart_timer;
/** @brief Pointeur vers la mémoire partagée */
entrees * iot = NULL;

/**
 * @brief Initialise l'accès au timer via la mémoire partagée
 * 
 * Accède à la zone mémoire du simulateur et enregistre
 * le temps de départ initial.
 * 
 * @return void
 */
void timer_initialisation(void)
{
	iot = acces_memoire(&shmidt);
	if(iot == NULL){
		printf("acces par le timer refuse\n");
		exit(1);
	}
	else
		depart_timer = iot->timer_sec;
		
		
}

/**
 * @brief Réinitialise le timer
 * 
 * Enregistre le temps actuel comme nouveau temps de départ.
 * Utilisé typiquement lors de l'insertion d'une carte.
 * 
 * @return void
 */
void timer_raze(void)
{
	depart_timer = iot->timer_sec;/* enregestrer le temps d'insertion*/
}

/**
 * @brief Retourne le temps écoulé depuis le dernier timer_raze
 * 
 * Calcule et retourne la différence entre le temps actuel
 * et le temps de départ enregistré.
 * 
 * @return Temps écoulé en secondes
 */
int timer_valeur(void)
{
	int temps_present;
	temps_present = iot->timer_sec;
	return (temps_present - depart_timer);
}

/**
 * @brief Crée un délai bloquant
 * 
 * Bloque l'exécution pendant le nombre de secondes spécifié.
 * 
 * @param t Durée du délai en secondes
 * @return void
 */
void delay (int t)
{
	int fin_delay = iot->timer_sec + t;/* temps actuel + delay (s)*/
	//printf("t = %d\t fin = %d\n",iot->timer_sec,fin_delay);
	while (fin_delay>(iot->timer_sec)){
	  //printf("\n");
	}
	printf("fin de delay de %ds\n",t);
}









