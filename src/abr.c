#include "arbr_type.h"
#include "aqrtopo.h"
#include "liste.h"
#include "truc.h"
#include "station.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Un_nabr *creer_nabr(Un_truc *truc)
{
    /* on cree un noeud */
    Un_nabr *noeud = (Un_nabr *)malloc(sizeof(Un_nabr));
    noeud->truc = truc;
    noeud->g = NULL;
    noeud->d = NULL;
    return noeud;
}

Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *node)
{
    /* on insere un noeud a sa place dans un ABR */
    /* on considere que notre ABR n'est composé que de stations, on ne traite pas le cas où il ya des connexions */

    if(abr == NULL)
    {
        abr = creer_nabr(node);
        return abr;
    }
    
    if(node->truc->data.sta.nom == abr->truc->data.sta.nom)
    {
        /* si c'est egal alors c'est la racine */
        return abr;
    }
    
    if(strcmp(abr->truc->data.sta.nom , node->truc->data.sta.nom) > 0)
    {
        /* si c'est plus grand alors on place a droite */
        abr->d = inserer_abr(abr->d,node);
    }
    
    else
    {
        /* si c'est plus petit alors on place a gauche */
        abr->g = inserer_abr(abr->g,node);
    }
        
    return abr;   
}

Un_nabr *construire_abr(Un_elem *liste_sta)
{
    Un_elem *ptr = liste_sta;
    Un_elem *root = liste_sta;
    Un_elem *head = NULL;
    Un_elem *node;

    /* pour chaque element de la liste_sta, on crée un noeud que l'on insere dans la tete de l'arbre */

    while(ptr != NULL)
    {
        node = creer_nabr(ptr->truc);
        head = inserer_abr(root,node);
        ptr = ptr->suiv;
    }

    return root;

}

void detruire_abr(Un_nabr *abr)
{
    /* on crée une fonction recursive qui utilise d'autres fonctions intermédiaires */
    if(abr != NULL)
    {
        detruire_branches(abr,abr->g);
        detruire_branches(abr,abr->d);
    }
}

void detruire_branches(Un_nabr *abr, Un_nabr *node)
{
    if(node->g)
    {
        detruire_branches(abr,abr->g);
    }

    if(node->d)
    {
        detruire_branches(abr,abr->d);
    }

    detruire_noeud(node);
}

void detruire_noeud(Un_nabr *node)
{

    if(!node)
    {
        return;
    }

    if(node->g)
    {
        detruire_noeud(node->g);
    }

    if(node->d)
    {
        detruire_noeud(node->d);
    }

    free(node);
    node = NULL;
}

Un_truc *chercher_station(Un_nabr *abr, char *nom)
{
    /* si l'arbre est vide, on retourne NULL */
    if(!abr)
    {
        return NULL;
    }

    if(strcmp(abr->truc->data.sta.nom , nom) > 0)
    {
        /* on cherche au niveau du fils droit */
        return chercher_station(abr->d,nom);
    }

    else if (strcmp(abr->truc->data.sta.nom , nom) < 0)
    {
        /* on cherche au niveau du fils gauche */
        return chercher_station(abr->g,nom);
    }

    else
    {
        /* dans ce cas, le noeud recherché est simplement la racine */
        return abr;
    }
}

