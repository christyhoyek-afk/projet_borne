#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"
#include"voyant.h"
#include "Generateur_save.h"
int main()
{

    lecteurcarte_initialiser();

    while (1)
    {
        lecteurcarte_lire_carte(VERT);
        lecture_numero_carte();
    }

}
