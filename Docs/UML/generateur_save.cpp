#include "generateur_save.h"
#include <iostream>
#include <cstdlib>  // Pour exit()

using namespace std;




    // Constructeur par défaut
    Generateur::Generateur() : io(nullptr), shmid(0) {}

    // Initialise le générateur en accédant à la mémoire partagée.
    void Generateur::initialiser() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.
        
        if (io == nullptr) {  // Vérification de l'accès réussi à la mémoire partagée.
            cerr << "Erreur lors de l'accès à la mémoire partagée" << endl;  // Affichage d'une erreur si l'accès échoue.
            exit(1);  // Quitte le programme avec un code d'erreur.
        }
    }

    // Modifie la PWM (Pulse Width Modulation) en fonction de la tension demandée.
    void Generateur::genererPWM(pwm tension) {
        switch (tension) {
            case STOP:
                io->gene_pwm = STOP;  // Désactive le générateur.
                break;
            case DC:
                io->gene_pwm = DC;  // Génère une tension DC (courant continu).
                break;
            case AC_1K:
                io->gene_pwm = AC_1K;  // Génère une tension AC à 1 kHz.
                break;
            case AC_CL:
                io->gene_pwm = AC_CL;  // Génère une tension AC pour charge lente.
                break;
            default:
                cerr << "Erreur lors de la modification de la tension du générateur" << endl;  // Message en cas de valeur inconnue.
        }
    }

    // Ouvre le contacteur pour déconnecter l'AC.
    void Generateur::ouvrirAC() {
        io->contacteur_AC = 0;  // Met le contacteur AC à l'état ouvert.
    }

    // Ferme le contacteur pour connecter l'AC.
    void Generateur::fermerAC() {
        io->contacteur_AC = 1;  // Met le contacteur AC à l'état fermé.
    }
int Generateur::lireTension(){
    return io->gene_u;
}