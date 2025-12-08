#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"baseclient.h"
#include"lecteurcarte.h"

static void baseclient_demander_retrait(void)
{
	printf("Veuillez retirer votre carte.\n");
	lecteurcarte_attendre_retrait();
}

/* Recherche si une carte existe dans la base.
   Le fichier stocke des lignes au format : <numero> <nom> <prenom>\n
   Retourne 1 si trouvée, 0 sinon. */
int baseclient_authentifier(int numcarte)
{
	int numero;
	FILE *fichier = fopen("baseclient.txt", "r");
	if (fichier == NULL) {
		/* fichier introuvable -> pas d'entrées */
		return 0;
	}

	while (fscanf(fichier, "%d", &numero) == 1) {
		if (numero == numcarte) {
			fclose(fichier);
			return 1;
		}
		/* sauter le nom et prenom éventuels pour atteindre la prochaine ligne */
		int c = fgetc(fichier);
		while (c != '\n' && c != EOF) c = fgetc(fichier);
	}

	fclose(fichier);
	return 0;
}

/* Enregistre un nouveau client dans la base. Retourne 1 si succes, 0 sinon. */
int baseclient_enregistrer(int numcarte, const char *nom, const char *prenom)
{
	if (!nom) nom = "";
	if (!prenom) prenom = "";

	/* Eviter doublons : vérifier l'existence */
	if (baseclient_authentifier(numcarte)) return 0; /* deja present */

	FILE *fichier = fopen("baseclient.txt", "a");
	if (fichier == NULL) {
		perror("Erreur ouverture baseclient.txt");
		return 0;
	}

	/* Ecrire au format : numero nom prenom\n
	   Nom/prenom ne doivent pas contenir d'espaces ; on suppose valeurs simples.
	*/
	fprintf(fichier, "%d %s %s\n", numcarte, nom, prenom);
	fflush(fichier);
	fclose(fichier);
	return 1;
}

/* Fonction interactive : demande nom/prenom à l'utilisateur et enregistre.
   Retourne 1 si enregistrement effectué, 0 sinon. */
int baseclient_interactive_enregistrer(int numcarte)
{
	/* Vérifier si la carte existe déjà */
	if (baseclient_authentifier(numcarte)) {
		printf("Client existe déjà dans la base. Veuillez retirer votre carte.\n");
		return 0;
	}

	char nom[128] = {0};
	char prenom[128] = {0};

	printf("Carte non identifiée. Entrez le nom : ");
	if (fgets(nom, sizeof(nom), stdin) == NULL) return 0;
	size_t l = strlen(nom);
	if (l && nom[l-1] == '\n') nom[l-1] = '\0';

	printf("Entrez le prenom : ");
	if (fgets(prenom, sizeof(prenom), stdin) == NULL) return 0;
	l = strlen(prenom);
	if (l && prenom[l-1] == '\n') prenom[l-1] = '\0';

	if (strlen(nom) == 0 && strlen(prenom) == 0) {
		printf("Nom et prenom vides — annulation.\n");
		baseclient_demander_retrait();
		return 0;
	}

	if (baseclient_enregistrer(numcarte, nom, prenom)) {
		printf("Client enregistre : %d %s %s\n", numcarte, nom, prenom);
		baseclient_demander_retrait();
		return 1;
	} else {
		printf("Echec enregistrement (deja present ou erreur).\n");
		baseclient_demander_retrait();
		return 0;
	}
}

/* Supprimer un client par numero. Retourne 1 si supprime, 0 si non trouve ou erreur. */
int baseclient_supprimer(int numcarte)
{
	FILE *in = fopen("baseclient.txt", "r");
	if (!in) return 0;
	FILE *out = fopen("baseclient.tmp", "w");
	if (!out) { fclose(in); return 0; }

	int numero;
	char nom[256];
	char prenom[256];
	int removed = 0;
	while (fscanf(in, "%d %255s %255s", &numero, nom, prenom) == 3) {
		if (numero == numcarte) {
			removed = 1; /* skip writing */
			continue;
		}
		fprintf(out, "%d %s %s\n", numero, nom, prenom);
	}

	fclose(in);
	fclose(out);

	if (removed) {
		if (remove("baseclient.txt") != 0) {
			/* try to clean tmp */
			remove("baseclient.tmp");
			return 0;
		}
		if (rename("baseclient.tmp", "baseclient.txt") != 0) return 0;
		return 1;
	} else {
		remove("baseclient.tmp");
		return 0;
	}
}

/* Modifier un client existant. Retourne 1 si modif, 0 sinon. */
int baseclient_modifier(int numcarte, const char *nom, const char *prenom)
{
	FILE *in = fopen("baseclient.txt", "r");
	if (!in) return 0;
	FILE *out = fopen("baseclient.tmp", "w");
	if (!out) { fclose(in); return 0; }

	int numero;
	char oldnom[256];
	char oldprenom[256];
	int modified = 0;
	while (fscanf(in, "%d %255s %255s", &numero, oldnom, oldprenom) == 3) {
		if (numero == numcarte) {
			fprintf(out, "%d %s %s\n", numcarte, nom, prenom);
			modified = 1;
		} else {
			fprintf(out, "%d %s %s\n", numero, oldnom, oldprenom);
		}
	}

	fclose(in);
	fclose(out);

	if (modified) {
		if (remove("baseclient.txt") != 0) { remove("baseclient.tmp"); return 0; }
		if (rename("baseclient.tmp", "baseclient.txt") != 0) return 0;
		return 1;
	} else {
		remove("baseclient.tmp");
		return 0;
	}
}

/* Wrapper interactif pour suppression */
int baseclient_interactive_supprimer(int numcarte)
{
	char resp[16];
	printf("Supprimer la carte %d ? (o/n) : ", numcarte);
	if (fgets(resp, sizeof(resp), stdin) == NULL) return 0;
	if (resp[0] == 'o' || resp[0] == 'O' || resp[0] == 'y' || resp[0] == 'Y') {
		if (baseclient_supprimer(numcarte)) {
			printf("Carte %d supprimee.\n", numcarte);
			baseclient_demander_retrait();
			return 1;
		} else {
			printf("Carte %d introuvable ou erreur.\n", numcarte);
			baseclient_demander_retrait();
			return 0;
		}
	}
	printf("Annule.\n");
	baseclient_demander_retrait();
	return 0;
}

/* Wrapper interactif pour modification */
int baseclient_interactive_modifier(int numcarte)
{
	char nom[128] = {0};
	char prenom[128] = {0};

	printf("Entrez le nouveau nom : ");
	if (fgets(nom, sizeof(nom), stdin) == NULL) return 0;
	size_t l = strlen(nom);
	if (l && nom[l-1] == '\n') nom[l-1] = '\0';

	printf("Entrez le nouveau prenom : ");
	if (fgets(prenom, sizeof(prenom), stdin) == NULL) return 0;
	l = strlen(prenom);
	if (l && prenom[l-1] == '\n') prenom[l-1] = '\0';

	if (baseclient_modifier(numcarte, nom, prenom)) {
		printf("Carte %d modifiee en: %s %s\n", numcarte, nom, prenom);
		baseclient_demander_retrait();
		return 1;
	} else {
		printf("Carte %d introuvable ou erreur.\n", numcarte);
		baseclient_demander_retrait();
		return 0;
	}
}
