#include <unistd.h>
#include "lecteurcarte.h"
#include <stdio.h>
#include "lcarte.h"

void lecteurcarte_initialiser()
{

}

void lecteurcarte_lire_carte()
{
    attente_insertion_carte();
    printf("Votre numéro de carte : %d\n", lecture_numero_carte());
}

