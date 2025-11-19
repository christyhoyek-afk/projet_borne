#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>         // Gestion des fonctions liées au temps.
#include <stddef.h>           // Définitions standard comme NULL.
#include <stdlib.h>           // Bibliothèque standard pour la gestion de la mémoire.
#include <stdio.h>            // Bibliothèque standard pour les fonctions d'entrée/sortie.
#include "global.h"           // Définitions globales.

// Structure représentant un intervalle de temps (début et fin).
typedef struct {
    int start; // Début de l'intervalle.
    int end;   // Fin de l'intervalle.
} temps;

class Timer {
public:
    // Constructeur par défaut
    Timer();

    // Initialise le timer (accès à la mémoire partagée).
    void initialiser();

    // Réinitialise un timer en remettant sa valeur de départ à l'heure actuelle.
    void raz(temps* timer);

    // Vérifie si un délai donné est écoulé.
    // Renvoie true si le délai est écoulé, sinon false.
    bool valeur(temps* timer, int delai);

private:
    entrees* io;  // Pointeur vers la mémoire partagée.
    int shmid;            // Identifiant de la mémoire partagée.
};

#endif // TIMER_H