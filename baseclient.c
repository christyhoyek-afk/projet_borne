#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"baseclient.h"


int baseclient_authentifier(int numcarte)
{
	int x, flag_identification = 0; // return 1 si l'authentification réussi sinon 0
	FILE *fichier = NULL;

	/* open file for reading and appending (creates if missing) */
	fichier = fopen("baseclient.txt","a+");
	if (fichier == NULL) {
		printf("erreur d'ouverture du fichier\n");
		exit(1);
	}

	/* rewind because a+ opens at end */
	rewind(fichier);
	while (fscanf(fichier, "%d", &x) == 1) {
		if (x == numcarte) {
			flag_identification = 1;
			break;
		}
	}

	if (flag_identification) {
		fclose(fichier);
		return 1;
	}

	/* carte non reconnue : proposer d'enregistrer */
	printf("Carte %d non reconnue. Voulez-vous l'enregistrer ? (o/n) : ", numcarte);
	char resp[16];
	if (fgets(resp, sizeof(resp), stdin) != NULL) {
		/* skip leading spaces */
		int i = 0;
		while (resp[i] && isspace((unsigned char)resp[i])) i++;
		char c = resp[i];
		if (c == 'o' || c == 'O' || c == 'y' || c == 'Y') {
			/* append the card number */
			fprintf(fichier, "%d\n", numcarte);
			fflush(fichier);
			fclose(fichier);
			printf("Numero de carte enregistre: %d\n", numcarte);
			return 1;
		}
	}

	fclose(fichier);
	return 0;
}
