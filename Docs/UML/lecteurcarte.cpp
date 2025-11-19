#include "lecteurcarte.h"
            // Pour la fonction raz
#include "baseclient.h"        // Pour baseclient_authentifier
             // Pour blink_charge
#include "Timer.h"             // Pour valeur
#include "bouton.h"           // Pour boutons_charge
using namespace std;



    int numero;          // Numéro de la carte lue.
    int authentifie;     // Indique si la carte est authentifiée.
    entrees* io; // Pointeur vers la mémoire partagée.


    // Initialise la mémoire partagée pour le lecteur de carte.
    void LecteurCarte::initialiserMemoire() {
        io = acces_memoire(&shmid);  // Accès à la mémoire partagée.
        if (io == nullptr) {  // Vérifie si l'accès échoue.
            cerr << "Erreur : pas de mémoire partagée" << endl;
            exit(1);  // Quitte le programme avec un code d'erreur.
        }
    }


    // Constructeur par défaut
    LecteurCarte::LecteurCarte() : numero(0), authentifie(0), io(nullptr), shmid(0) {}

    // Initialise le lecteur de carte.
    void LecteurCarte::initialiser() {
        initialisations_ports();  // Initialise les ports nécessaires pour le lecteur de carte.
        initialiserMemoire();     // Initialise l'accès à la mémoire partagée.
    }

    // Lit une carte insérée et gère le processus de recharge.
    int LecteurCarte::lireCarte() {
        cout << "\nInsérez votre carte pour recharger\n";
        attente_insertion_carte();  // Attend que la carte soit insérée.
        Timer t;
        t.raz(&start);  // Réinitialise le compteur de temps pour le suivi du délai.

        // Lecture du numéro de la carte insérée.
        numero = lecture_numero_carte();  
        cout << "Numéro de carte lu : " << numero << endl;

        // Vérifie si une carte est insérée et si la borne est disponible.
        if (carte_inseree() && io->led_dispo == VERT) {
            // Authentifie le numéro de carte avec la base des clients.
            BaseClient base;
            authentifie = base.authentifier(numero);

            if (authentifie == 1) {  // Si la carte est authentifiée.
                cout << "Carte authentifiée\n";
                Voyant voyant;
                voyant.blinkCharge();  // Fait clignoter une LED pour indiquer que la carte est authentifiée.
                cout << "Appuyez sur charge\n";
                Bouton bouton;
                // Attente de l'appui sur le bouton de charge ou expiration du délai.
                do {
                    // Rien à faire dans la boucle, simplement attendre.
                } while ((!t.valeur(&start, 60)) && (bouton.lireBoutonCharge() == 0));

                if (bouton.lireBoutonCharge() == 1) {  // Si le bouton de charge est pressé.
                    cout << "Recharge en cours...\n";
                    return 1;  // Indique que la recharge a commencé.
                } else {
                    cout << "Temps écoulé. Recharge annulée.\n";
                    return 0;  // Indique que la recharge a été annulée.
                }
            } else {
                cout << "Carte non authentifiée\n";
                return -1;  // Indique que la carte n'est pas authentifiée.
            }
        } else {
            cout << "Erreur : Carte non insérée ou borne non disponible\n";
            return -2;  // Indique une erreur (carte non insérée ou borne indisponible).
        }
    }
