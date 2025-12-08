#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H
#include <lcarte.h>

void lecteurcarte_initialiser();
void lecteurcarte_lire_carte();
void attente_insertion_carte();
int lecteurcarte_obtenir_numero(void);
void lecteurcarte_attendre_retrait(void);

#endif // LECTEURCARTE_H
