#ifndef GENERATEUR_H
#define GENERATEUR_H

#include <iostream>
#include <cstdlib>
#include "global.h"
#include <mem_sh.h>

class Generateur {
public:
    // Constructeur par défaut
    Generateur();

    // Initialise le générateur (accès à la mémoire partagée).
    void initialiser();

    // Modifie la PWM (Pulse Width Modulation) en fonction de la tension demandée.
    void genererPWM(pwm tension);

    // Ouvre le contacteur pour déconnecter l'AC.
    void ouvrirAC();

    // Ferme le contacteur pour connecter l'AC.
    void fermerAC();

    // Retourne la tension actuelle mesurée par le générateur.
    int lireTension();

private:
    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
};

#endif // GENERATEUR_H