/**
 * @file baseclient.c
 * @brief Gestion de la base de données des clients
 * 
 * Ce module gère l'authentification, l'enregistrement, la modification
 * et la suppression des clients dans un fichier texte.
 * Le format du fichier est: <numero_carte> <nom> <prenom>
 * 
 * @author Christian HOYEK et Julian DUBOSCLARD
 * @date 2026
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"baseclient.h"

/**
 * @brief Demande à l'utilisateur de retirer sa carte
 * 
 * Affiche un message demandant le retrait de la carte,
 * attend que la carte soit retirée, puis confirme le retrait.
 * 
 * @return void
 */
static void baseclient_demander_retrait(void)
{
	printf("Veuillez retirer votre carte.\n");
	attente_retrait_carte();
	printf("Carte retirée.\n");
}

/**
 * @brief Authentifie un client en recherchant son numéro de carte
 * 
 * Recherche si une carte existe dans la base de données.
 * Le fichier stocke des lignes au format : <numero> <nom> <prenom>\n
 * 
 * @param numcarte Le numéro de carte à rechercher
 * @return 1 si la carte est trouvée, 0 sinon
 */
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

/**
 * @brief Enregistre un nouveau client dans la base de données
 * 
 * Ajoute un nouveau client dans le fichier baseclient.txt.
 * Vérifie qu'il n'existe pas déjà avant l'ajout.
 * 
 * @param numcarte Le numéro de carte du client
 * @param nom Le nom du client (peut être NULL)
 * @param prenom Le prénom du client (peut être NULL)
 * @return 1 en cas de succès, 0 si le client existe déjà ou en cas d'erreur
 */
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

/**
 * @brief Enregistre un nouveau client de manière interactive
 * 
 * Demande le nom et le prénom à l'utilisateur via stdin,
 * puis enregistre le client dans la base.
 * Gère les cas d'erreur et demande le retrait de la carte.
 * 
 * @param numcarte Le numéro de carte du client à enregistrer
 * @return 1 si l'enregistrement est effectué, 0 sinon
 */
int baseclient_interactive_enregistrer(int numcarte)
{
	/* Vérifier si la carte existe déjà */
	if (baseclient_authentifier(numcarte)) {
		printf("Client existe déjà dans la base. Veuillez retirer votre carte.\n");
		baseclient_demander_retrait();
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

/**
 * @brief Supprime un client de la base de données
 * 
 * Recherche et supprime le client correspondant au numéro de carte.
 * Utilise un fichier temporaire pour la réécriture.
 * 
 * @param numcarte Le numéro de carte du client à supprimer
 * @return 1 si le client est supprimé, 0 s'il n'est pas trouvé ou en cas d'erreur
 */
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

/**
 * @brief Modifie les informations d'un client existant
 * 
 * Recherche le client par son numéro de carte et met à jour
 * son nom et prénom. Utilise un fichier temporaire pour la modification.
 * 
 * @param numcarte Le numéro de carte du client à modifier
 * @param nom Le nouveau nom du client
 * @param prenom Le nouveau prénom du client
 * @return 1 si la modification est effectuée, 0 si le client n'est pas trouvé ou en cas d'erreur
 */
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

/**
 * @brief Supprime un client de manière interactive
 * 
 * Demande confirmation à l'utilisateur avant de supprimer
 * le client de la base de données.
 * 
 * @param numcarte Le numéro de carte du client à supprimer
 * @return 1 si la suppression est effectuée, 0 sinon
 */
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

/**
 * @brief Modifie un client de manière interactive
 * 
 * Demande le nouveau nom et prénom à l'utilisateur via stdin,
 * puis modifie les informations du client dans la base.
 * 
 * @param numcarte Le numéro de carte du client à modifier
 * @return 1 si la modification est effectuée, 0 si le client n'est pas trouvé ou en cas d'erreur
 */
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
