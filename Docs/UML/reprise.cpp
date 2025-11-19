#include "reprise.h"  // Inclusion du fichier d'en-tête pour la gestion de la reprise après charge.
#include <iostream>
#include <cstdlib>

using namespace std;


    int numero1;          // Numéro de la carte lors de la reprise.
    int authentifie1;     // Indique si la carte est authentifiée.

    // Initialise l'accès à la mémoire partagée.
    void Reprise::initialiserMemoire() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.
        if (io == nullptr) {  // Vérifie si l'accès échoue.
            cerr << "Erreur lors de l'accès à la mémoire partagée" << endl;
            exit(1);  // Quitte le programme en cas d'erreur critique.
        }
    }


    // Constructeur par défaut
    Reprise::Reprise() : io(nullptr), shmid(0), numero1(0), authentifie1(0) {}

    // Initialise la reprise (accès à la mémoire partagée).
    void Reprise::initialiser() {
        initialiserMemoire();
    }

    // Gère la reprise après une charge.
    void Reprise::gererReprise() {
        cout << "\nFin de charge\n";
        do {
            cout << "Insérez votre carte \n";  // Demande à l'utilisateur d'insérer sa carte.
            
            global.attenteInsertionCarte();  // Attend l'insertion d'une carte.

            numero1 = global.lectureNumeroCarte();  // Lecture du numéro de la carte insérée.
            cout << "Numéro de carte lu : " << numero1 << endl;

            // Vérifie si une carte est insérée.
            if (global.carteInseree()) {
                
                authentifie1 = base.authentifier(numero1);  // Authentifie la carte insérée.

                if (authentifie1 == 1) {  // Si la carte est authentifiée :
                    cout << "Carte authentifiée\n";
                    
                    prise.deverrouillerTrappe();  // Déverrouille la trappe pour permettre le retrait de la prise.
                    cout << "Retirez votre carte\n";
                    global.attenteRetraitCarte();  // Attend que la carte soit retirée.
                    cout << "Retirez la prise\n\n\n\n\n";
                    
                    // Attend que la tension revienne à un état sûr (valeur 12 dans ce cas).
                    do {

                    } while (generateur.lireTension()!= 12);

                    prise.verrouillerTrappe();  // Verrouille la trappe après le retrait de la prise.
                    prise.setPrise(OFF);             // Éteint la LED de la prise pour indiquer que tout est terminé.
                    voyant.setDispo(VERT);            // Réactive la disponibilité de la borne pour d'autres utilisateurs.
                }
            } else if (authentifie1 == 0) {  // Si la carte n'est pas authentifiée :
                cout << "Carte non authentifiée\n";
                voyant.blinkDefaut();  // Clignote pour signaler une erreur.
            }
        } while (authentifie1 != 1);  // Répète jusqu'à ce qu'une carte authentifiée soit utilisée.
    }
