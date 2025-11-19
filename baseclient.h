#ifndef BASECLIENT_H
#define BASECLIENT_H
int baseclient_authentifier(int numcarte);
int baseclient_enregistrer(int numcarte, const char *nom, const char *prenom);
int baseclient_interactive_enregistrer(int numcarte);
int baseclient_supprimer(int numcarte);
int baseclient_modifier(int numcarte, const char *nom, const char *prenom);
int baseclient_interactive_supprimer(int numcarte);
int baseclient_interactive_modifier(int numcarte);
#endif
