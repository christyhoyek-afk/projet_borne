#include "Timer.h"
#include <iostream>
#include <cstdlib>

using namespace std;



    // Constructeur par défaut
    Timer::Timer() : io(nullptr), shmid(0) {}

    // Méthode pour initialiser le timer (accès à la mémoire partagée).
    void Timer::initialiser() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.

        // Vérification de la validité de l'accès à la mémoire partagée.
        if (io == nullptr) {
            cerr << "Erreur lors de l'accès à la mémoire partagée" << endl;
            exit(1);  // Termine le programme en cas de problème critique.
        }
    }

    // Méthode pour réinitialiser un timer.
    // Prend en entrée un pointeur vers une structure `temps` représentant un timer.
    void Timer::raz(temps* timer) {
        timer->start = io->timer_sec;  // Stocke la valeur actuelle du compteur global (en secondes) dans `start`.
    }

    // Méthode pour vérifier si un certain délai est écoulé.
    // Prend en entrée un pointeur vers un timer (`temps`) et un délai (en secondes).
    // Renvoie true si le délai est écoulé, sinon renvoie false.
    bool Timer::valeur(temps* timer, int delai) {
        int diff = io->timer_sec - timer->start;  // Calcule la différence entre le compteur actuel et le début du timer.

        return diff >= delai;  // Retourne true si le délai est écoulé, sinon false.
    }
