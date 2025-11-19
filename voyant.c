#include<stdio.h>
#include<stdlib.h>
#include<donnees_borne.h>
#include<memoire_borne.h>
#include<unistd.h>/*pour utiliser usleep*/
#include "voyant.h"

int shmid;
entrees * io = NULL; // acces à la structure de l'interface borne 
void voyant_initialisation()
{ 
 io = acces_memoire(&shmid);//recuperation de l'adresse memoire de la borne
 if(io == NULL)
	printf("acces par les voyants refuse\n");
 else {
	/*printf("acces avec succes\n");*/
	/*eteindre toutes les LED*/
	voyant_setcharge(OFF);
	voyant_setdisponible(ON);
	voyant_setdefaut(OFF);
	voyant_setpriseR(OFF);
	}
 }

/*changement voyant charge */
void voyant_setcharge(led led_charge)
{
 io->led_charge = led_charge;
}

/* changement voyant disponible*/
void voyant_setdisponible(led led_dispo)
{
 io->led_dispo = led_dispo;
}


/* changement voyant default*/
void voyant_setdefaut(led led_defaut)
{
 io->led_defaut = led_defaut;
}


/* changement voyant prise rangee*/
void voyant_setpriseR(led led_PR)
{
 io->led_prise = led_PR;
}


/* changement voyant trappe */
void voyant_settrappe(led led_trappe)
{
 io->led_trappe = led_trappe;
}

/*clignotement de  voyant charge  */
void voyant_toggle_charge(void)
{
  	int i;
	for(i=0;i<8;i++){
		voyant_setcharge(VERT);
		usleep(500000);/*delay de 0.5s*/
        	voyant_setcharge(OFF);
		usleep(500000);
	}	
}

/*clignotement du voyant Defaut  */
void voyant_toggle_Defaut(void)
{
  	int i;
	for(i=0;i<8;i++){
		voyant_setdefaut(ROUGE);
		usleep(500000);/*delay de 0.5s*/
        	voyant_setdefaut(OFF);
		usleep(500000);
	}	
}

