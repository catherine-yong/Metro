#include "truc.h"
#include <stdio.h>

typedef struct _un_elem { 
    Un_truc *truc; /*Une station ou une connexion */
    struct _un_elem *suiv;
} Un_elem; 

Un_truc* extraire_deb_liste(Un_elem** liste)
{
    Un_elem* L = NULL;
    if (*liste != NULL)
    {
        L = *liste;
        *liste = (*liste)->suiv;
    }
    return L;
}
