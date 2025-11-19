#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "global.h"

class BaseClient {
public:
    // Constructeur par défaut avec un fichier par défaut "clients.txt".
    explicit BaseClient(const std::string& fichier_clients = "clients.txt");

    // Méthode pour authentifier un client en utilisant son numéro de carte.
    bool authentifier(int num_carte);

    // Méthode pour ajouter un nouveau client dans le système.
    bool ajouter(int num, const std::string& nom, const std::string& prenom);

private:
    std::string fichier_clients_;  // Nom du fichier contenant les informations des clients.
};

#endif // BASECLIENT_H