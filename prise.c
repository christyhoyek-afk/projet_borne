#include <stdio.h>
#include <stdlib.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include "voyant.h"
#include "Prise.h"

entrees * iop = NULL; 
int shmidp;
/* acceder a la structure*/
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

/* deverouiller la trape*/
void Prise_deverouiller_trape(void)
{
	iop->led_trappe = VERT;
}

/*veroiller la trape et allumer le voyant */
void Prise_veroiller_trape(void)
{
	iop->led_trappe = OFF;/*trape verouillee*/

}
