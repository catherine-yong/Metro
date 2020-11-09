#include "arbr_type.h"
#include "aqrtopo.h"
#include <stdio.h>
#include <stdlib.h>

Un_nabr *creer_nabr(Un_truc *truc)
{
    /* on cree un noeud */
    Un_nabr *noeud = (Un_nabr *)malloc(sizeof(Un_nabr));
    noeud->truc = truc;
    noeud->g = NULL;
    noeud->d = NULL;
    return noeud;
}
/* 

typedef struct _un_nabr { 
    Un_truc *truc; /*La station*/
    struct _un_nabr *g; /*Fils gauche strictement inferieur*/ 
    struct _un_nabr *d; /*Fils droit*/ */

typedef struct _un_truc { 
    Une_coord coord;
    Ttype type;
    Tdata data;
    float user_val; /*Distance pour plus court chemin*/
} Un_truc;



Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *noeud)
{
    /* on insere un noeud a sa place dans un ABR */

    Un_nabr *ptr = abr;
    if(noeud->truc->type == 0) /* si c'est une station */
    {
        if(noeud->truc->data.sta.nom )
    }

}