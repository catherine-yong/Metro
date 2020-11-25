#include "abr.h"

#include <stdlib.h>
#include <liste.h>

Un_noeud *create_node_aqr(Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    // on crée un noeud au sein du quadtree en initialisant ses valeurs 
    Un_noeud *new_node_aqr = NULL;

    new_node_aqr->truc = (Un_truc *) malloc(sizeof(Un_truc));
    new_node_aqr->truc = truc;
    new_node_aqr->limite_no = limite_no;
    new_node_aqr->limite_se = limite_se;
    new_node_aqr->no = NULL;
    new_node_aqr->so = NULL;
    new_node_aqr->ne = NULL;
    new_node_aqr->se = NULL;

    return new_node_aqr;

}

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    /* on veut insérer un noeud au sein de l'aqr */

    /* on vérifie la comptabilité des coordonnes */

    if(limite_no.lat >= truc->coord.lat &&  limite_no.lon >= truc->coord.lon && limite_se.lat >= truc->coord.lat && limite_se.lon >= truc->coord.lon)
    {
    
        /* on crée un nouvel élément et on initialise ses valeurs */
        Un_noeud *new_node = NULL;
        new_node = (Un_noeud *) malloc(sizeof(Un_noeud));
        new_node = create_node_aqr(limite_no,limite_se,truc);

        Un_noeud *current = aqr;

        /* si le truc à insérer dans l'aqr est NULL on ne fait rien */
        if(!truc)
        {
            printf("Il n'y a rien à ajouter\n");
            return NULL;
        }

        /* si l'aqr est vide, alors l'aqr devient le nouveau noeud */
        if(!aqr)
        {
            aqr = (Un_noeud *)malloc(sizeof(Un_noeud));
            aqr = new_node;
            return aqr;
        }

        /* on a dépassé le seuil défini : le problème n'est plus pertinant à cette distance */
        if (abs(current->no->limite_no.lat - current->no->limite_se.lat) <= 0.5 && abs(current->no->limite_no.lon - current->no->limite_se.lon) <= 0.5) 
        {
            return NULL; 
        } 

        /* d'abord, on regarde si le truc doit être placé à l'ouest ou à l'est. ensuite, on regarde s'il doit être au nord ou au sud */
        /* pour cela, on compare par rapport au millieu de chaque segment du rectangle */
    
        if((float)(current->no->limite_no.lat + current->se->limite_se.lat)/2 >= truc->coord.lat)
        {
            /* ici, le truc sera placé à l'ouest */
            
            if((current->no->limite_no.lon + current->no->limite_se.lon)/2 >= truc->coord.lon)
            {
                /* ici, le truc sera placé à la branche nord ouest */
                if(!current->no)
                {
                    /* si le noeud est vide, on insere le nouvel élément */
                    /* on met à jour ses coordonnes */
                    new_node->limite_no.lat = limite_no.lat;
                    new_node->limite_no.lon = limite_no.lon;
                    new_node->limite_se.lat = limite_se.lat;
                    new_node->limite_se.lon = limite_se.lon;
                    /* on fait pointer le dernier élément de l'arbre sur le nouvel élément*/
                    current->so = (Un_noeud *) malloc(sizeof(Un_noeud));
                    current->no = new_node;
                    return aqr; 
                }
                /* si le noeud n'est pas vide, on met à jour les latitudes et on continue */
                limite_no.lat -= (float) (limite_no.lat)/2; 
                limite_se.lat -=(float) (limite_se.lat)/2;
                return inserer_aqr(current->no,limite_no,limite_se,truc);
            }

            else
            {
                /* ici, le truc sera placé à la branche sud ouest */
                if(!current->so)
                {
                    /* si le noeud est vide, on insere le nouvel élément */
                    /* on met à jour ses coordonnes */
                    new_node->limite_no.lat = limite_no.lat;
                    new_node->limite_no.lon = limite_no.lon;
                    new_node->limite_se.lat = limite_se.lat;
                    new_node->limite_se.lon = limite_se.lon;
                    /* on fait pointer le dernier élément de l'arbre sur le nouvel élément*/
                    current->so = (Un_noeud *) malloc(sizeof(Un_noeud));
                    current->so = new_node;
                    return aqr; 
                }
                /* si le noeud n'est pas vide, on met à jour les latitudes et on continue */
                limite_no.lat -= (float) (limite_no.lat)/2; 
                limite_se.lat -=(float) (limite_se.lat)/2;
                return inserer_aqr(aqr->so,limite_no,limite_se,truc);
            }
        }

        else
        {
            /* ici, le truc sera placé à l'est */
            if((aqr->no->limite_no.lon + aqr->no->limite_se.lon)/2 >= truc->coord.lon)
            {
                /* ici, le truc sera placé à la branche nord est */
                if(!aqr->ne)
                {
                    /* si le noeud est vide, on insere le nouvel élément */
                    /* on met à jour ses coordonnes */
                    new_node->limite_no.lat = limite_no.lat;
                    new_node->limite_no.lon = limite_no.lon;
                    new_node->limite_se.lat = limite_se.lat;
                    new_node->limite_se.lon = limite_se.lon;
                    /* on fait pointer le dernier élément de l'arbre sur le nouvel élément*/
                    current->ne = (Un_noeud *) malloc(sizeof(Un_noeud));
                    current->ne = new_node;
                    return aqr; 
                }
                /* si le noeud n'est pas vide, on met à jour les latitudes et on continue */
                limite_no.lat += (float) (limite_no.lat)/2; 
                limite_se.lat +=(float) (limite_se.lat)/2;
                return inserer_aqr(aqr->ne,limite_no,limite_se,truc);
            }

            else
            {
                /* ici, le truc sera placé à la branche sud est */
                if(!aqr->se)
                {
                    /* si le noeud est vide, on insere le nouvel élément */
                    /* on met à jour ses coordonnes */
                    new_node->limite_no.lat = limite_no.lat;
                    new_node->limite_no.lon = limite_no.lon;
                    new_node->limite_se.lat = limite_se.lat;
                    new_node->limite_se.lon = limite_se.lon;
                    /* on fait pointer le dernier élément de l'arbre sur le nouvel élément*/
                    current->se = (Un_noeud *) malloc(sizeof(Un_noeud));
                    current->se = new_node;
                    return aqr; 
                }
                /* si le noeud n'est pas vide, on met à jour les latitudes et on continue */
                limite_no.lat += (float) (limite_no.lat)/2; 
                limite_se.lat +=(float) (limite_se.lat)/2;
                return inserer_aqr(aqr->se,limite_no,limite_se,truc);
            }
        }
    }
}

Un_noeud *construire_aqr(Un_elem *head)
{
    /* on construit un aqr depuis une liste */
    Un_elem *phead = head;
    
    Un_noeud *aqr = NULL;
    aqr = (Un_noeud *) malloc(sizeof(Un_noeud));
    
    Un_noeud *_aqr = NULL;
    _aqr = (Un_noeud *) malloc(sizeof(Un_noeud));

    Une_coord limite_no;
    Une_coord limite_se;

    limites_zone(head,&limite_no,&limite_se);

    while(phead)
    {
        aqr = inserer_aqr(aqr,limite_no,limite_se,phead->truc);
        phead = phead->suiv;
    }

    _aqr = aqr; // _aqr pointe vers la tete de aqr 

    return _aqr;
}

void detruire_aqr(Un_noeud *abr)
{
    /* on crée une fonction recursive qui utilise d'autres fonctions intermédiaires */
    if(abr != NULL)
    {
        detruire_branches(abr,abr->no);
        detruire_branches(abr,abr->ne);
        detruire_branches(abr,abr->so);
        detruire_branches(abr,abr->se);
    }
}

void detruire_branches_aqr(Un_noeud *abr, Un_noeud *branch)
{
    /* on utilise une autre fonction */
    if(abr->no)
    {
        detruire_branches_aqr(abr,abr->no);
    }

    if(abr->ne)
    {
        detruire_branches_aqr(abr,abr->ne);
    }

    if(abr->so)
    {
        detruire_branches_aqr(abr,abr->so);
    }

    if(abr->se)
    {
        detruire_branches_aqr(abr,abr->se);
    }

    detruire_noeud_aqr(branch);
}

void detruire_noeud_aqr(Un_noeud *node)
{
    /* on detruir le noeud */
    if(!node)
    {
        return;
    }

    if(node->no)
    {
        detruire_noeud_aqr(node->no);
    }

    if(node->ne)
    {
        detruire_noeud_aqr(node->ne);
    }

    if(node->so)
    {
        detruire_noeud_aqr(node->so);
    }

    if(node->se)
    {
        detruire_noeud_aqr(node->se);
    }

    free(node);
    node = NULL;
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord)
{
    /* on cherche l'élément de l'arbre correspondant aux coordonnées */
    Un_noeud *ptr = aqr;

    /* cas d'arrêt : l'arbre est vide de base */

    if(!aqr)
    {
        printf("L'arbre est vide\n");
        return NULL;
    }

    /* on a dépassé le seuil défini : le problème n'est plus pertinant à cette distance */
    if (abs(ptr->no->limite_no.lat - ptr->no->limite_se.lat) <= 0.5 && abs(ptr->no->limite_no.lon - ptr->no->limite_se.lon) <= 0.5) 
    {
        return NULL; 
    } 

    /* d'abord, on regarde si le truc est à l'ouest ou à l'est. ensuite, on regarde s'il doit être au nord ou au sud */

    if((float)(ptr->no->limite_no.lat + ptr->no->limite_se.lat)/2 >= coord.lat)
    {
        /* ici, le truc est à l'ouest */
        
        if((ptr->no->limite_no.lon + ptr->no->limite_se.lon)/2 >= coord.lon)
        {
            /* ici, le truc est placé à la branche nord ouest */
            if(!ptr->no)
            {
                /* si le noeud est vide, alors l'élément n'est pas là */
                printf("L'élément n'est pas dans l'arbre\n");
                return NULL;
            }
            /* si le noeud n'est pas vide, on continue */
            return chercher_aqr(ptr->no,coord);
        }

        else
        {
            /* ici, le truc est placé à la branche sud ouest */
            if(!ptr->so)
            {
                /* si le noeud est vide, alors l'élément n'est pas là */
                printf("L'élément n'est pas dans l'arbre\n");
                return NULL;
            }
            /* si le noeud n'est pas vide, on continue */
            return chercher_aqr(ptr->so,coord);
        }
    }

    else
    {
        /* ici, le truc est placé à l'est */
        if((ptr->no->limite_no.lon + ptr->se->limite_se.lon)/2 >= coord.lon)
        {
            /* ici, le truc est placé à la branche nord est */
            if(!ptr->ne)
            {
                /* si le noeud est vide, alors l'élément n'est pas là */
                printf("L'élément n'est pas dans l'arbre\n");
                return NULL;
            }
            /* si le noeud n'est pas vide, on continue */
            return chercher_aqr(ptr->ne,coord);
        }

        else
        {
            /* ici, le truc sera placé à la branche sud est */
            if(!ptr->se)
            {
                /* si le noeud est vide, alors l'élément n'est pas là */
                printf("L'élément n'est pas dans l'arbre\n");
                return NULL;
            }
            /* si le noeud n'est pas vide, on continue */
            return chercher_aqr(ptr->se,coord);
        }
    }
}



/*limite_no correspond à la longitude minimale et la latitude maximale, limite_se
correspond à la longitude maximale et à la latitude minimale.*/

Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *head, Une_coord limite_no, Une_coord limite_se)
{
    // dans ces cas là, on passe au noeud suivant
    if((aqr->limite_no.lon < limite_no.lon) || (aqr->limite_no.lat > limite_no.lat) || (aqr->limite_se.lon > limite_se.lon) || (aqr->limite_se.lat < limite_no.lat))
    {
        chercher_zone(aqr->no,head,limite_no,limite_se);
        chercher_zone(aqr->so,head,limite_no,limite_se);
        chercher_zone(aqr->ne,head,limite_no,limite_se);
        chercher_zone(aqr->se,head,limite_no,limite_se);
    }

    // si c'est dans la zone, on ajoute à la liste le truc de l'aqr courant
    head->truc = NULL;
    head->truc = (Un_truc *) malloc(sizeof(Un_truc));
    head->truc = aqr->truc;

    // on passe au suivant
    head->suiv = NULL;
    head->suiv = (Un_elem *) malloc(sizeof(Un_elem));
    head = head->suiv;

    if(aqr->no)
    {
        chercher_zone(aqr->no,head,limite_no,limite_se);
    }

    if(aqr->so)
    {
        chercher_zone(aqr->so,head,limite_no,limite_se);
    }

    if(aqr->ne)
    {
        chercher_zone(aqr->ne,head,limite_no,limite_se);
    }

    if(aqr->se)
    {
        chercher_zone(aqr->se,head,limite_no,limite_se);
    }

    // si c'est une feuille on arrête
    if((!aqr->no) || (!aqr->ne) || (!aqr->so) || (!aqr->se))
    {
        return head;
    }
    

}
