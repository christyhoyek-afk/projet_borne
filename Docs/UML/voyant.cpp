#include "voyant.h"  // Inclusion du fichier d'en-tête pour la gestion des voyants.
#include "global.h"  // Inclusion du fichier global pour les définitions partagées.
#include <iostream>
#include <cstdlib>

using namespace std;


   

    // Constructeur par défaut
    Voyant::Voyant() : io(nullptr), shmid(0) {}

    // Méthode pour initialiser les voyants.
    void  Voyant::initialiser() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.

        // Vérifie si l'accès à la mémoire partagée a réussi.
        if (io == nullptr) {
            cerr << "Erreur lors de l'accès à la mémoire partagée" << endl;
            exit(1);  // Quitte le programme en cas d'erreur critique.
        }
    }

    // Méthode pour définir l'état du voyant de charge.
    void  Voyant::setCharge(led etat) {
        switch (etat) {
            case VERT:
                io->led_charge = VERT;  // Allume le voyant de charge en vert.
                break;
            case ROUGE:
                io->led_charge = ROUGE;  // Allume le voyant de charge en rouge.
                break;
            case OFF:
                io->led_charge = OFF;  // Éteint le voyant de charge.
                break;
            default:
                cerr << "Erreur lors de la modification de l'état de la LED charge" << endl;
        }
    }

    // Méthode pour définir l'état du voyant de disponibilité.
    void  Voyant::setDispo(led etat) {
        switch (etat) {
            case VERT:
                io->led_dispo = VERT;  // Allume le voyant de disponibilité en vert.
                break;
            case ROUGE:
                io->led_dispo = ROUGE;  // Allume le voyant de disponibilité en rouge.
                break;
            case OFF:
                io->led_dispo = OFF;  // Éteint le voyant de disponibilité.
                break;
            default:
                cerr << "Erreur lors de la modification de l'état de la LED disponibilité" << endl;
        }
    }
