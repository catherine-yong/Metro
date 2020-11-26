#include "aqrtopo.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

Un_noeud *create_node_aqr(Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    // on crée un noeud au sein du quadtree en initialisant ses valeurs
    Un_noeud *new_node_aqr = NULL;
    new_node_aqr = (Un_noeud*)malloc(sizeof(Un_noeud));
    
    if(!new_node_aqr)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }

    new_node_aqr->truc = truc;
    new_node_aqr->limite_no = limite_no;
    new_node_aqr->limite_se = limite_se;

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
    Un_elem *phead = NULL;
    Un_noeud *aqr = NULL;
    Une_coord limite_no;
    Une_coord limite_se;
    
    if(!head)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }
    
    limite_no = head->truc->coord;
    limite_se = head->truc->coord;
    phead = head->suiv;

    while(phead)
    {
        if(phead->truc->coord.lon < limite_no.lon)
        {
            limite_no.lon = phead->truc->coord.lon;
        }
        if(phead->truc->coord.lon > limite_no.lon)
        {
            limite_se.lon = phead->truc->coord.lon;
        }
        if(phead->truc->coord.lat < limite_no.lat)
        {
            limite_no.lat = phead->truc->coord.lat;
        }
        if(phead->truc->coord.lat > limite_no.lat)
        {
            limite_se.lat = phead->truc->coord.lat;
        }
        phead = phead->suiv;
    }
    
    while(head != NULL)
    {
        aqr = inserer_aqr(aqr, limite_no, limite_se, head->truc);
        head = head->suiv;
    }

    return aqr;
}

void detruire_aqr(Un_noeud *abr)
{
    /* on crée une fonction recursive qui utilise d'autres fonctions intermédiaires */
    if(!abr->truc)
    {
        detruire_aqr(abr->no);
        detruire_aqr(abr->ne);
        detruire_aqr(abr->so);
        detruire_aqr(abr->se);
    }
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord)
{
    /* on cherche l'élément de l'arbre correspondant aux coordonnées */

    Une_coord limite_no = aqr->limite_no;
    Une_coord limite_se = aqr->limite_se;
    Une_coord Coord;
    
    /* cas d'arrêt : l'arbre est vide de base */
    if(!aqr)
    {
        printf(" L'arbre est vide \n");
        return NULL;
    }
    
    if(aqr->truc != NULL)
    {
        if(coord.lon == aqr->truc->coord.lon && coord.lat == aqr->truc->coord.lat)
        {
          return aqr->truc;
        }
        else
        {
          printf("L'élément n'est pas dans l'arbre\n");
          return NULL;
        }
      }

      /* on a dépassé le seuil défini : le problème n'est plus pertinant à cette distance */
      Coord.lon=(limite_no.lon+limite_se.lon)/2;
      Coord.lat=(limite_no.lat+limite_se.lat)/2;

    
    /* d'abord, on regarde si le truc est à l'ouest ou à l'est. ensuite, on regarde s'il doit être au nord ou au sud */
      if(coord.lon >= limite_no.lon && coord.lon <= Coord.lon && coord.lat >= Coord.lat && coord.lat <= limite_no.lat)
        {
          return chercher_aqr(aqr->no, coord);
        }
      
      if(coord.lon < limite_se.lon && coord.lon > Coord.lon && coord.lat < Coord.lat && coord.lat > limite_se.lat)
        {
          return chercher_aqr(aqr->se, coord);
        }

      if(coord.lon >= limite_no.lon && coord.lon <= Coord.lon && coord.lat >= limite_se.lat && coord.lat < Coord.lat)
        {
          return chercher_aqr(aqr->so, coord);
        }
      else
        {
          return chercher_aqr(aqr->ne,coord);
        }
}


/*limite_no correspond à la longitude minimale et la latitude maximale, limite_se
correspond à la longitude maximale et à la latitude minimale.*/

Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *head, Une_coord limite_no, Une_coord limite_se)
{
    Une_coord coord;
    coord.lon = (aqr->limite_no.lon + aqr->limite_se.lon)/2;
    coord.lat = (aqr->limite_no.lat + aqr->limite_se.lat)/2;
    
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
    
    return 0;
}
