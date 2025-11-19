#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "baseclient.h"
using namespace std;


    // Constructeur par défaut
    BaseClient::BaseClient(const string& fichier_clients) : fichier_clients_(fichier_clients) {}

    // Méthode pour authentifier un client à partir de son numéro de carte.
    bool BaseClient::authentifier(int num_carte) {
        ifstream fichier(fichier_clients_);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier " << fichier_clients_ << endl;
            return false;
        }

        string ligne;
        while (getline(fichier, ligne)) {
            istringstream iss(ligne);
            int num;
            string nom, prenom;

            if (iss >> num >> nom >> prenom) {
                if (num == num_carte) {
                    cout << "Client authentifié : " << nom << " " << prenom << endl;
                    fichier.close();
                    return true;
                }
            }
        }

        cout << "Client non authentifié" << endl;
        fichier.close();
        return false;
    }

    // Méthode pour ajouter un nouveau client.
    bool BaseClient::ajouter(int num, const string& nom, const string& prenom) {
        fstream fichier(fichier_clients_, ios::in | ios::out | ios::app);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier " << fichier_clients_ << endl;
            return false;
        }

        fichier << num << " " << nom << " " << prenom << endl;
        cout << "Client ajouté avec succès." << endl;
        fichier.close();
        return true;
    }
    string fichier_clients_;  // Nom du fichier contenant les informations des clients.
