#include "liste.h"
#include "station.h"
#include "truc.h"

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

Un_elem *lire_stations(char *nom_fichier)
{
    FILE* fd;
    char ligne[200];
    char *ptr_chaine;/* pointeur pour récuperer le "token"*/
    const char *separators = ";";

    fd = fopen(nom_fichier, "r");
    if (fd == NULL)
        return NULL;
    while (fgets(ligne, 200, fd) != NULL) {
        ptr_chaine = strtok(ligne, separators);
        while (ptr_chaine != NULL) {
            printf("%s\n", ptr_chaine);
            ptr_chaine = strtok(NULL, separators);
        }
    }
    return ptr_chaine;
}

Un_elem *inserer_liste_trie(Un_elem *head, Un_truc *truc)
{
    /* on veut inserer le truc dans la liste de maniere croissante*/

    Un_elem *current = head;

    Un_elem *element;
    element->truc = truc;

    /* si la liste est nulle ou si l'element a inserer a un user_val plus grand que la tete de liste, on ajoute au debut*/

    if((!head) || (truc->user_val > head->truc->user_val))
    {
        element->suiv = head;
        head = element;
    }
    
    /* si l'element a inserer est au milieu de la liste ou a la fin, alors on parcourt jusqu'au bon rand de user_valur 
    c'est a dire une fois que user_value de l'element est plus petit que user_valeur du pointeur sur la liste, ou quand on est a la fin de la liste */

    else 
    {
        while (current->suiv != NULL && current->suiv->truc->user_val <= truc->user_val)
        {
            current = current->suiv;
        } 
        element->suiv = current->suiv;
        current->suiv = element;
    }
    return head;
}

void ecrire_liste(FILE *flux, Un_elem *head)
{
    /* on veut afficher les trucs correspondants a des stations */
    Un_elem *current = head;
    while (current->suiv != NULL) {
        if (current->truc->type == 0) {
            printf("%s\n", current->truc->data.sta.nom);
        }
        current = current->suiv;
    }
}

void detruire_liste(Un_elem *head)
{
    /* on veut detruire une liste chainee de trucs */
    Un_elem *temp;
    Un_elem *ptr = head;
    while(ptr)
    {
        temp = ptr->suiv;
        free(ptr);
        ptr = temp;
    }
}

void detruire_liste_et_truc(Un_elem *head)
{
    /* pour chaque maillon de la liste, on detruit son contenu */
    /* on prend un element temporaire qui stocke la case d'apres pour ensuite detruire le contenu de la case courante */
    Un_elem *temp;
    while(head)
    
    {
        temp = head->suiv;
        detruire_truc(head->truc);
        free(head);
        head = temp;
    }
}

Un_elem *inserer_deb_liste(Un_elem *head, Un_truc *truc)
{
    /* on crée un nouvel élément que l'on insèrera en début de liste */
    /* on alloue la mémoire nécessaire pour l'élément et son champ truc */

    Un_elem *new_head = NULL;
    new_head = (Un_elem *) malloc(sizeof(Un_elem));
    
    new_head->truc = NULL;
    new_head->truc = (Un_truc *) malloc(sizeof(Un_truc));

    /* si truc passé en paramètre est NULL, alors on sort de la fonction */

    if(!truc)
    {
        printf("Problème lors de l'allocation de mémoire car truc est NULL");
        exit(1);
    }

    /* ici, truc passé en paramètre n'est pas NULL, donc on ajoute truc à new_head et on fait pointer new_head sur la liste head */
    
    new_head->truc = truc;
    new_head->suiv = head;

    return new_head;
}   


void limites_zone(Un_elem *head, Une_coord *limite_no, Une_coord *limite_se)
{
    Un_elem *phead = head;

    /* on intialise les valeurs des 2 coordonnées aux valeurs maximales de leur type */

    double longitude_min = DBL_MAX;
    double longitude_max = DBL_MIN;
    double latitude_min = DBL_MAX;
    double latitude_max = DBL_MIN;

    /*tant que le pointeur sur liste n'est pas null, on compare avec les composantes des 2 coordonnées */
    /* si on trouve un élément plus petit (resp. grand) que le minimum définit (resp. maximum) alors on procède à un échange */
    
    while(phead)
    {   
        /* on compare avec la longitude minimale */
        if(phead->truc->coord.lon < longitude_min)
        {
            longitude_min = phead->truc->coord.lon;
        }

        /* on compare avec la longitude maximale */
        if(phead->truc->coord.lon > longitude_max)
        {
            longitude_max = phead->truc->coord.lon;
        }

        /* on compare avec la latitude minimale */
        if(phead->truc->coord.lon < latitude_min)
        {
            latitude_min = phead->truc->coord.lat;
        }

        /* on compare avec la latitude maximale */
        if(phead->truc->coord.lon > latitude_max)
        {
            latitude_max = phead->truc->coord.lat;
        }

        /* on avance dans la liste */
        phead = phead->suiv;

    }

    /*on a fini de parcourir la liste, on change donc les coordonnées de limite_no et limite_se comme selon l'énoncé*/
    
    if(!limite_se) // if limite_se == NULL
    {
        limite_se = (Une_coord *) malloc(sizeof(Une_coord));
    }

    if(!limite_no) // if limite_no == NULL
    {
        limite_no = (Une_coord *) malloc(sizeof(Une_coord));
    }

    limite_se->lon = longitude_max;
    limite_se->lat = latitude_min;

    limite_no->lon = longitude_min;
    limite_se->lat = latitude_max;

}