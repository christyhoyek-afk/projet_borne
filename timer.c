#include<stdio.h>
#include<stdlib.h>
#include "donnees_borne.h"
#include"mem_sh.h"
#include"timer.h"
int shmidt;
int depart_timer;
entrees * iot = NULL;

/* acces a la zone memoire de simulateur*/
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

/* declancher le timer une fois la carte est inseree*/ 
void timer_raze(void)
{
	depart_timer = iot->timer_sec;/* enregestrer le temps d'insertion*/
}

/* renvoie la valeur du temps ecouler depuis l'insertion*/
int timer_valeur(void)
{
	int temps_present;
	temps_present = iot->timer_sec;
	return (temps_present - depart_timer);
}

/* delay en t seconds*/
void delay (int t)
{
	int fin_delay = iot->timer_sec + t;/* temps actuel + delay (s)*/
	//printf("t = %d\t fin = %d\n",iot->timer_sec,fin_delay);
	while (fin_delay>(iot->timer_sec)){
	  //printf("\n");
	}
	printf("fin de delay de %ds\n",t);
}









