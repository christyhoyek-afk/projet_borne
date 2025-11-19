#ifndef VOYANT_H
#define VOYANT_H

#include "global.h"           // Définitions globales.
#include <mem_sh.h>           // Gestion de la mémoire partagée.
#include <stdio.h>            // Bibliothèque standard pour les fonctions d'entrée/sortie.
#include <stdlib.h>           // Bibliothèque standard pour la gestion de la mémoire.
#include <unistd.h>           // Fonctions POSIX comme sleep.

class Voyant {
public:
    // Constructeur par défaut
    Voyant();

    // Initialise les voyants (configuration initiale).
    void initialiser();

    // Définit l'état du voyant de charge (allumé, éteint, ou clignotant).
    void setCharge(led etat);

    // Définit l'état du voyant de disponibilité.
    void setDispo(led etat);

    // Définit l'état du voyant de défaut.
    void setDefaut(led etat);

    // Fait clignoter le voyant de charge.
    void blinkCharge();

    // Fait clignoter le voyant de défaut.
    void blinkDefaut();

private:
    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
};

#endif // VOYANT_H