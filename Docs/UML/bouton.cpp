#include "bouton.h"  // Inclusion du fichier d'en-tête pour les boutons.
#include <iostream>
#include <cstdlib>  // Pour exit()

using namespace std;



    // Constructeur pour initialiser les boutons.
    Bouton::Bouton() : bio(nullptr), bshmid(0) {}

    void Bouton::boutonsInitialise() {
        // Accès à la mémoire partagée contenant l'état des boutons.
        bio = acces_memoire(&bshmid);
        if (bio == NULL) {  // Vérifie si l'accès à la mémoire partagée a échoué.
            cout << "Erreur pas de memoire partagee" << endl;
            exit(1);  // Quitte le programme avec un code d'erreur en cas de problème.
        }

        // Initialisation des états des boutons.
        bio->bouton_charge = 0;  // Le bouton de charge est désactivé au démarrage.
        bio->bouton_stop = 0;    // Le bouton d'arrêt est désactivé au démarrage.
    }

    // Méthode pour lire l'état du bouton de charge.
    int Bouton::lireBoutonCharge()  {
        return bio->bouton_charge;  // Retourne l'état actuel du bouton de charge.
    }

    // Méthode pour lire l'état du bouton d'arrêt.
    int Bouton::lireBoutonStop()  {
        return bio->bouton_stop;  // Retourne l'état actuel du bouton d'arrêt.
    }
