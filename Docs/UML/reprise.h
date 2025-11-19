#ifndef REPRISE_H
#define REPRISE_H

#include <stdio.h>            // Bibliothèque standard pour les fonctions d'entrée/sortie.
#include <stdlib.h>           // Bibliothèque standard pour la gestion de la mémoire.
#include <unistd.h>           // Fonctions POSIX comme sleep.
#include "voyant.h"           // Gestion des voyants.
#include "prise.h"            // Gestion des prises.
#include "global.h"           // Définitions globales.
#include "baseclient.h"       // Authentification et gestion des clients.
#include "generateur_save.h"  // Gestion du générateur.

class Reprise {
public:
    // Constructeur par défaut
    Reprise();

    // Initialise la reprise (accès à la mémoire partagée).
    void initialiser();

    // Gère la reprise après une charge.
    void gererReprise();
    Global global;
    BaseClient base;
    Prise prise;
    Generateur generateur;
    Voyant voyant;
    // Initialise l'accès à la mémoire partagée.
    void initialiserMemoire();
private:
    
    

    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
    int numero1;          // Numéro de la carte lors de la reprise.
    int authentifie1;     // Indique si la carte est authentifiée.
};

#endif // REPRISE_H