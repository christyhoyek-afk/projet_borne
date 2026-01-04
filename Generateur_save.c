/**
 * @file Generateur_save.c
 * @brief Gestion du générateur de tension et du processus de charge
 * 
 * Ce module gère le chargement des véhicules électriques en contrôlant
 * les tensions (DC, AC), le contacteur AC, et en implémentant une machine
 * à états pour le processus de charge complet.
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h> /*pour utiliser usleep*/
#include "voyant.h"
#include "Generateur_save.h"
#include "prise.h"

/** @brief Pointeur vers la mémoire partagée des entrées/sorties */
entrees * iog = NULL;
/** @brief Identifiant de la mémoire partagée */
int shmidg ;
/** @brief Flag indiquant si la prise est branchée (1) ou non (0) */
int etat_prise =0;/*flag mit a 1 si la prise est branchee sinon 0*/

/**
 * @brief Initialise le générateur et l'accès à la mémoire partagée
 * 
 * Initialise la prise, accède à la mémoire partagée et réinitialise
 * le bouton d'arrêt à 0.
 * 
 * @return void
 */
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

/**
 * @brief Gère le processus complet de chargement du véhicule
 * 
 * Implémente une machine à états pour gérer le chargement :
 * - État 1 : Attente de branchement de la prise
 * - État 2 : Prise branchée, S2 non fermé
 * - État 3 : Attente de fermeture de S2
 * - État 4 : Chargement de la batterie
 * - État 5 : Fin de chargement ou arrêt
 * 
 * @return void
 */
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

/**
 * @brief Gère la récupération du véhicule après la charge
 * 
 * Déverrouille la trappe et attend que la prise soit débranchée,
 * puis verrouille la trappe et éteint les voyants.
 * 
 * @return void
 */
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

/**
 * @brief Génère une tension spécifique
 * 
 * Configure le générateur pour produire la tension demandée
 * (DC, AC_1K, AC_CL, STOP).
 * 
 * @param tension Type de tension à générer (type pwm)
 * @return void
 */
void Generateur_save_Gentension(pwm tension)
{
	iog->gene_pwm = tension;

}

/**
 * @brief Mesure la tension actuelle du générateur
 * 
 * Lit et retourne la valeur de tension mesurée par le générateur.
 * 
 * @return Valeur de la tension mesurée en unités arbitraires
 */
int Generateur_save_Valtension(void)
{
	return iog->gene_u ;
}

/**
 * @brief Contrôle l'état du contacteur AC
 * 
 * Ouvre ou ferme le contacteur AC.
 * 
 * @param etat État du contacteur (0 = ouvert/On, 1 = fermé/off)
 * @return void
 */
void Generateur_save_ACEtat(int etat)
{	
	iog->contacteur_AC = etat;
}
