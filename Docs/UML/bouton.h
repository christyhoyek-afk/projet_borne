#ifndef BOUTON_H
#define BOUTON_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

class Bouton {
public:
    // Constructeur par défaut
    Bouton();

    // Retourne l'état du bouton de charge.
    int lireBoutonCharge();

    // Retourne l'état du bouton d'arrêt.
    int lireBoutonStop() ;
    // Initialise les boutons.
    void boutonsInitialise();
private:
    entrees* bio;  // Pointeur vers une structure partagée représentant les entrées (probablement des boutons physiques).
    int bshmid;    // Identifiant de la mémoire partagée pour accéder aux entrées.
};

#endif // BOUTON_H