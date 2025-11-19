#ifndef PRISE_H
#define PRISE_H

#include <sys/time.h>         // Gestion des fonctions liées au temps.
#include <stddef.h>           // Définitions standard comme NULL.
#include <stdlib.h>           // Bibliothèque standard pour la gestion de la mémoire.
#include "global.h"           // Définitions globales.
#include <donnees_borne.h>    // Définitions liées aux données de la borne.
#include <mem_sh.h>           // Gestion de la mémoire partagée.

class Prise {
public:
    // Constructeur par défaut
    Prise();

    // Initialise la prise électrique et les composants associés.
    void initialiser();

    // Définit l'état de la LED de la prise (ON, OFF, etc.).
    void setPrise(led etat);

    // Déverrouille la trappe associée à la prise.
    void deverrouillerTrappe();

    // Verrouille la trappe associée à la prise.
    void verrouillerTrappe();

private:
    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
};

#endif // PRISE_H