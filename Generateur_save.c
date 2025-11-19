#include <stdio.h>
#include <stdlib.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h> /*pour utiliser usleep*/
#include "voyant.h"
#include "Generateur_save.h"
#include "prise.h"

entrees * iog = NULL;
int shmidg ;
int etat_prise =0;/*flag mit a 1 si la prise est branchee sinon 0*/

void Generateur_save_initialisation(void)
{
	Prise_initialisation();
	iog = acces_memoire(&shmidg);
 	if(iog == NULL){
		printf("acces au bouton refuse\n");
		exit(1);
	}
	else
		iog->bouton_stop = 0;/*remise a zero du bouton*/

}

/* charger la batterie */
void Generateur_save_chargement_VH(void)
{
	int etat_S2 = 1;/*flag mit a 0 si S2 ferme sinon 1*/
	int etat = 2;/*pour le changement des etats de la machine a etat*/
	int batterie_pleine = 0;/*flag mit a 1 si la batterie est pleine sinon 0*/	
		/*etat 1 attente de prise*/
		voyant_setcharge(ROUGE);
		Generateur_save_Gentension(DC);/*12V DC*/
		Prise_deverouiller_trape();
		printf("brancher la prise pour commencer le chargement\n");
		while(!etat_prise){
			/*attente de branchement de la peise*/
			usleep(1000);/*donne le temps a la borne de mettre ajour la valeur de la tension, ne pas supprimer*/
			if(Generateur_save_Valtension() == 9){
				etat_prise = 1;
			}
		}
		while((etat_prise)&&(!(iog->bouton_stop))&&(!batterie_pleine))
		{
			switch (etat){
				case 2 : /*etat 2 prise branche S2 non ferme */
						 Prise_veroiller_trape();
						 voyant_setpriseR(VERT);
						 Generateur_save_Gentension(AC_1K);/*AC 9AC/-12V*/ 
						 etat = 3;
						 break;
						 
				case 3:/* etat 3 attente de fermeture de S2*/
						Generateur_save_ACEtat(1);/*fermer AC*/
						if(Generateur_save_Valtension() == 6)
							etat = 4;
						break;
						
				case 4 : /*etat 4 chargement de la batterie*/
						Generateur_save_Gentension(AC_CL);/*AC 6AC/-12V*/ 
						if(Generateur_save_Valtension() == 9){
							printf("batterie pleine\n");
							batterie_pleine = 1;
						}
						break;
						 
				default : printf("etat %d\n",etat);
		
			}
		}
		
		/*etat 5 fin de chargement ou appuie sur STOP*/
		iog->bouton_stop = 0;/*remise a zero du bouton*/
		Generateur_save_Gentension(DC);/*pour ouvrir S2*/
		while(etat_S2)
		{
			/*attente d'ouverture de S2*/
			usleep(1000);/*meme probleme*/
			if(Generateur_save_Valtension() == 9){
				etat_S2 = 0;
				}
		}
		
		Generateur_save_ACEtat(0);/*ouvrir AC*/
		voyant_setcharge(VERT);
		printf("fin de chargement \n\n");
}

/*recuperation de la voiture */
void Gnenerateur_save_recuperation_VH(void)
{
		Prise_deverouiller_trape();
		/*attente de debrancher la prise*/
		while(etat_prise){
			usleep(1000);/*meme probleme*/
			if(Generateur_save_Valtension() == 12){
				etat_prise = 0;
			}
		}
		Prise_veroiller_trape();
		voyant_setpriseR(OFF);
		voyant_setcharge(OFF);
		Generateur_save_Gentension(STOP);
		
	
}

/* generer les differentes tensions*/
void Generateur_save_Gentension(pwm tension)
{
	iog->gene_pwm = tension;

}

/* la mesure de la tension */
int Generateur_save_Valtension(void)
{
	return iog->gene_u ;
}

/* Contacteur AC ouvert/ferme ,0 On 1 off*/
void Generateur_save_ACEtat(int etat)
{	
	iog->contacteur_AC = etat;
}
