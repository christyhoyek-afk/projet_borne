#include <iostream>
#include <limits>
#include "voyant.h"
#include "lecteurcarte.h"
#include "Timer.h"
#include "baseclient.h"
#include "reprise.h"
#include "global.h"
#include "generateur_save.h"
#include "prise.h"

using namespace std;





    // Méthode publique pour démarrer la borne.
    int main() {
        Global global;
BaseClient base;
Prise prise;
Generateur generateur;
Voyant voyant;
Reprise reprise;
Bouton bouton;
Timer timer;
LecteurCarte lecteurcarte;
        // Initialisation des composants.
        lecteurcarte.initialiser();
       
        bouton.boutonsInitialise();
        timer.initialiser();
        voyant.initialiser();
        reprise.initialiserMemoire();
        generateur.initialiser();
        prise.initialiser();
       

        // Affichage du message de bienvenue.
        cout << "\n";
        cout << "----------------------------\n";
        cout << "BIENVENUE DANS NOTRE STATION \n";
        cout << "----------------------------\n";
        cout << "\n";

        int numero;  // Variable pour stocker le choix de l'utilisateur.

        // Boucle infinie pour gérer les interactions avec la borne.
        while (true) {
            // Affichage des options pour l'utilisateur et lecture de son choix.
            do {
                cout << "Que voulez-vous faire ?\n";
                cout << "Tappez 1 pour charger\n";
                cout << "Tappez 2 ajouter un client\n";
                while (!(cin >> numero)) {  // Assure que l'entrée est un entier.
                    cin.clear();  // Efface le flag d'erreur.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore les entrées invalides.
                    cout << "Veuillez entrer un nombre valide.\n";
                }
            } while (numero != 1 && numero != 2);  // Répète jusqu'à ce que l'utilisateur choisisse une option valide.

            if (numero == 1) {  // Option 1 : Charger
                // Code pour l'option 1 ici.
            } else if (numero == 2) {  // Option 2 : Ajouter un client
                // Code pour l'option 2 ici.
            }
        }
        return 0;
    }

