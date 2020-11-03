#include "truc.h"
#include "coord.h"
#include <stdlib.h>

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv)
{
    Un_truc *nv_truc = (Un_truc *)malloc(sizeof(Un_truc));
    nv_truc->coord = coord;
    nv_truc->type = type;
    nv_truc->data = data;
    nv_truc->user_val = uv;
    return nv_truc;
}


// un truc est soit une station soit une connexion