#include "prise.h"  // Inclusion du fichier d'en-tête pour la gestion des prises.
#include <iostream>
#include <cstdlib>

using namespace std;


    


    // Constructeur par défaut
    Prise::Prise() : io(nullptr), shmid(0) {}

    // Méthode pour initialiser la prise et les composants associés.
    void Prise::initialiser() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.
        
        // Vérifie si l'accès à la mémoire partagée a échoué.
        if (io == nullptr) {
            cerr << "Erreur lors de l'accès à la mémoire partagée" << endl;
            exit(1);  // Termine le programme en cas d'erreur critique.
        }
        
        // Initialisation des LED liées à la prise et à la trappe.
        io->led_prise = OFF;   // Éteint la LED de la prise (indique que la prise est inactive).
        io->led_trappe = OFF;  // Éteint la LED de la trappe (indique que la trappe est verrouillée).
    }

    // Méthode pour changer l'état de la LED de la prise.
    void Prise::setPrise(led etat) {
        io->led_prise = etat;  // Définit l'état de la LED de la prise selon la valeur passée (ON, OFF, etc.).
    }

    // Méthode pour déverrouiller la trappe.
    void Prise::deverrouillerTrappe() {
        io->led_trappe = VERT;  // Allume la LED verte pour indiquer que la trappe est déverrouillée.
    }

    // Méthode pour verrouiller la trappe.
    void Prise::verrouillerTrappe() {
        io->led_trappe = OFF;  // Éteint la LED, indiquant que la trappe est verrouillée.
    }
