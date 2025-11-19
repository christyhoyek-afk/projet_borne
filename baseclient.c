#include<stdio.h>
#include<stdlib.h>
#include"baseclient.h"


int baseclient_authentifier(int numcarte)
{
	int i,x,flag_identification;
	i = 0;
	flag_identification = 0;// return 1 si l'authentification réussi sinon 0
	FILE * fichier = NULL;
	fichier = fopen("baseclient.txt","r");
	if(fichier == NULL){
		printf("erreur d'ouvrture du fichier\n");
		exit(1);
	  }

	else{
		while((fscanf(fichier,"%d\n",&x)) != EOF)
		{
			if(x == numcarte){
			   flag_identification = 1;
			   break;}
			i++;
		}
	     }
//printf("numero identifier est %d, la ligne %d\n",numcarte,i);
return flag_identification;
}
