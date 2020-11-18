#include "truc.h"
#include "coord.h"
#include <stdlib.h>

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv)
{
    /* on crée un truc, soit une station ou une connexion et on initialise ses champs*/
    Un_truc *nv_truc = (Un_truc *)malloc(sizeof(Un_truc));
    nv_truc->coord = coord;
    nv_truc->type = type;
    nv_truc->data = data;
    nv_truc->user_val = uv;
    return nv_truc;
}

void detruire_truc(Un_truc *truc)
{
     /* si c'est une station alors on désalloue le pointeur */

    if (truc->type == 0) 
    {
        free(truc->data.sta.nom);
        for (int i = 0; truc->data.sta.tab_con[i] != NULL; i++)
            free(truc->data.sta.tab_con[i]);
        free(truc->data.sta.tab_con); // à vérifer si nécessaire
    }
    free(truc);
}