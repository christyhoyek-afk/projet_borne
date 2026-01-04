/**
 * @file baseclient.h
 * @brief Interface de gestion de la base de données des clients
 * 
 * Ce fichier définit les fonctions pour gérer l'authentification,
 * l'enregistrement, la modification et la suppression des clients.
 * 
 * @author Projet Borne
 * @date 2026
 */

#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <lcarte.h>

/**
 * @brief Authentifie un client en recherchant son numéro de carte
 * 
 * @param numcarte Le numéro de carte à rechercher
 * @return 1 si la carte est trouvée, 0 sinon
 */
int baseclient_authentifier(int numcarte);

/**
 * @brief Enregistre un nouveau client dans la base de données
 * 
 * @param numcarte Le numéro de carte du client
 * @param nom Le nom du client (peut être NULL)
 * @param prenom Le prénom du client (peut être NULL)
 * @return 1 en cas de succès, 0 si le client existe déjà ou en cas d'erreur
 */
int baseclient_enregistrer(int numcarte, const char *nom, const char *prenom);

/**
 * @brief Enregistre un nouveau client de manière interactive
 * 
 * @param numcarte Le numéro de carte du client à enregistrer
 * @return 1 si l'enregistrement est effectué, 0 sinon
 */
int baseclient_interactive_enregistrer(int numcarte);

/**
 * @brief Supprime un client de la base de données
 * 
 * @param numcarte Le numéro de carte du client à supprimer
 * @return 1 si le client est supprimé, 0 s'il n'est pas trouvé ou en cas d'erreur
 */
int baseclient_supprimer(int numcarte);

/**
 * @brief Modifie les informations d'un client existant
 * 
 * @param numcarte Le numéro de carte du client à modifier
 * @param nom Le nouveau nom du client
 * @param prenom Le nouveau prénom du client
 * @return 1 si la modification est effectuée, 0 si le client n'est pas trouvé ou en cas d'erreur
 */
int baseclient_modifier(int numcarte, const char *nom, const char *prenom);

/**
 * @brief Supprime un client de manière interactive
 * 
 * @param numcarte Le numéro de carte du client à supprimer
 * @return 1 si la suppression est effectuée, 0 sinon
 */
int baseclient_interactive_supprimer(int numcarte);

/**
 * @brief Modifie un client de manière interactive
 * 
 * @param numcarte Le numéro de carte du client à modifier
 * @return 1 si la modification est effectuée, 0 si le client n'est pas trouvé ou en cas d'erreur
 */
int baseclient_interactive_modifier(int numcarte);

#endif
