/* Minimal shared types used by voyants/prises.
   If you have a canonical 'global' header, prefer that instead.
*/
#ifndef TYPES_H
#define TYPES_H

/* If the shared 'donnees_borne.h' header is available it defines COMMUN_H
   and the 'led' type; only define a local minimal enum when that is not
   present to avoid redefinition conflicts. */
#ifndef COMMUN_H
typedef enum {
    OFF = 0,
    VERT = 1,
    ROUGE = 2
} led;
#endif /* COMMUN_H */

#endif /* TYPES_H */
