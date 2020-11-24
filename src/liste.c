#include "abr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

Un_elem *lire_stations(char *nom_fichier)
{
    FILE *fichier;
    char *line = NULL;
    char *ptr_ligne;
    const char *separator = ";";
    size_t size = 0;
    
    Un_elem *head = NULL;
    head = (Un_elem*) malloc(sizeof(Un_elem));
    Un_elem *phead = head;
    Un_elem *pptemp = head;
    head->truc = NULL;
    head->truc = (Un_truc*) malloc(sizeof(Un_truc));

    fichier = fopen(nom_fichier,"r");

    if(!fichier)
    {
        printf("impossible d'ouvir le fichier\n");
        return NULL;
    }

    if(!head)
    {
        fclose(fichier);
        return NULL;
    }

    if(!head->truc)
    {
        fclose(fichier);
        return NULL;
    }

    // initialisation des valeurs
    head->truc->type = 0;
    head->truc->user_val = 0;
    ((head->truc->data).sta).nb_con = 0;
    ((head->truc->data).sta).tab_con = NULL;
    ((head->truc->data).sta).nom = NULL;
    ((head->truc->data).sta).con_pcc = NULL;

    while (getline(&line, &size, fichier) != -1){

        pptemp = head;

        ptr_ligne = NULL;

        ptr_ligne = strtok(line,separator);

        ((head->truc->data).sta).nom = NULL;
        ((head->truc->data).sta).nom = (char*) malloc((strlen(ptr_ligne) + 1)*sizeof(char));

        if(((head->truc->data).sta).nom == NULL)
        {
            fclose(fichier);
            return NULL;
        }

        strcpy(((head->truc->data).sta).nom , ptr_ligne);

        ptr_ligne = strtok(NULL,separator);

        (head->truc->coord).lat = (float) atof(ptr_ligne);

        ptr_ligne = strtok(NULL,separator);

        (head->truc->coord).lon = (float) atof(ptr_ligne);

        head->suiv = NULL;
        head->suiv = (Un_elem*) malloc(sizeof(Un_elem));
        if(!head->suiv)
        {
            fclose(fichier);
            return NULL;
        }

        head->suiv->truc = NULL;
        head->suiv->truc = (Un_truc*) malloc(sizeof(Un_truc));
        if(head->suiv->truc == NULL)
        {
            fclose(fichier);
            return NULL;
        }

        head = head->suiv;
        head->truc->type = 0;
        head->truc->user_val = 0.0;
        ((head->truc->data).sta).nb_con = 0;
        ((head->truc->data).sta).tab_con = NULL;
        ((head->truc->data).sta).nom = NULL;
        ((head->truc->data).sta).con_pcc = NULL;
    }

    //desallocation memoire
    free(line);
    free(head->truc);
    free(head);
    phead->suiv = NULL;
    fclose(fichier);
    return phead;
}

Un_elem *inserer_liste_trie(Un_elem *head, Un_truc *truc)
{
    /* on veut inserer le truc dans la liste de maniere croissante*/

    if(!truc)
    {
        printf("rien à insérer\n");
        return head;
    }

    Un_elem *current = head;

    Un_elem *nouv_element = NULL;
    nouv_element = (Un_elem *) malloc(sizeof(Un_elem));
    if(!nouv_element)
    {
        printf("probleme allocation\n");
        return NULL;
    }
    nouv_element->truc = NULL;
    nouv_element->truc = (Un_truc *) malloc(sizeof(Un_truc));

    if(!nouv_element->truc)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }

    nouv_element->truc = truc;

    /* si la liste est nulle ou si l'element a inserer a un user_val plus grand que la tete de liste, on ajoute au debut*/

    if(!head)
    {
        head = (Un_elem *) malloc(sizeof(Un_elem));
        head->truc = nouv_element->truc;
        head->suiv = NULL;
    }

    if(truc->user_val > head->truc->user_val)
    {
        nouv_element->suiv = head;
        head = nouv_element;
    }
    
    /* si l'element a inserer est au milieu de la liste ou a la fin, alors on parcourt jusqu'au bon rand de user_valur 
    c'est a dire une fois que user_value de l'element est plus petit que user_valeur du pointeur sur la liste, ou quand on est a la fin de la liste */

    else 
    {
        while (current->suiv != NULL && current->suiv->truc->user_val <= truc->user_val)
        {
            current = current->suiv;
        } 
        nouv_element->suiv = current->suiv;
        current->suiv = nouv_element;
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
    Un_elem *phead = head->suiv;

    /* on intialise les valeurs des 2 coordonnées aux valeurs maximales de leur type */

    double longitude_min = head->truc->coord.lon;
    double longitude_max = head->truc->coord.lon;
    double latitude_min = head->truc->coord.lat;
    double latitude_max = head->truc->coord.lat;

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

    if((!limite_se) || (!limite_no))
    {
        exit(1);
    }

    limite_se->lon = longitude_max;
    limite_se->lat = latitude_min;

    limite_no->lon = longitude_min;
    limite_se->lat = latitude_max;

}

int main()
{
    Un_truc *truc;
    Une_coord coord;
    Ttype type;
    Tdata data;
    double uv;
    truc = creer_truc(coord, type, data, uv);
    Un_elem *stations;
    stations = lire_stations("stations_metro.csv");
    return 0;
}