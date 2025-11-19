#ifndef GLOBAL_H
#define GLOBAL_H

#include "donnees_borne.h"   // Définitions liées aux données de la borne.
#include "memoire_borne.h"   // Gestion de la mémoire partagée.
#include <iostream>

class Global {
public:
    // Constructeur par défaut
    Global();


    // Vérifie si le bouton d'arrêt est pressé.
    // Retourne un entier indiquant l'état (1 pour pressé, 0 pour non pressé).
    int boutonsStop() ;

    // Fonction d'attente pour l'insertion de la carte (bloque jusqu'à ce qu'une carte soit insérée).
    void attenteInsertionCarte() ;

    // Fonction d'attente pour le retrait de la carte (bloque jusqu'à ce qu'une carte soit retirée).
    void attenteRetraitCarte() ;

    // Lit le numéro de la carte insérée et retourne sa valeur sous forme d'entier.
    unsigned int lectureNumeroCarte() ;

    // Vérifie si une carte est insérée.
    // Retourne 1 si une carte est insérée, 0 sinon.
    int carteInseree() const;
    
private:
    entrees* io;  // Pointeur vers les entrées/sorties de la borne.
    int shmid;    // Identifiant de la mémoire partagée.
};

#endif // GLOBAL_H