#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>           // Bibliothèque pour la gestion des cartes.
#include <iostream>           // Bibliothèque standard pour les entrées/sorties.
#include <sys/time.h>         // Gestion des fonctions liées au temps.
#include "voyant.h"           // Gestion des voyants.
#include "bouton.h"           // Gestion des boutons.
#include "Timer.h"            // Gestion des minuteries.
#include <cstddef>            // Définitions standard comme nullptr.
#include "baseclient.h"       // Authentification et gestion des clients.
#include "generateur_save.h"  // Gestion du générateur.
#include "global.h"           // Définitions globales.

class LecteurCarte {
public:
    // Constructeur par défaut
    LecteurCarte();

    // Initialise le lecteur de carte (ports et mémoire partagée).
    void initialiser();

    // Lit une carte insérée et gère le processus de recharge.
    int lireCarte();

private:
    // Initialise la mémoire partagée pour le lecteur de carte.
    void initialiserMemoire();

    int numero;           // Numéro de la carte lue.
    int authentifie;      // Indique si le client est authentifié (1 pour oui, 0 pour non).
    temps start;          // Variable pour gérer le temps écoulé dans les interactions.
    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
};

#endif // LECTEURCARTE_H