#include "aqrtopo.h"
#include "coord.h"
#include "truc.h"

#include <stdlib.h>
#include <liste.h>

Un_noeud *create_node_aqr(Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    Un_noeud *new_node_aqr = NULL;

    new_node_aqr->truc = truc;
    new_node_aqr->limite_no = limite_no;
    new_node_aqr->limite_se = limite_se;
    new_node_aqr->no = NULL;
    new_node_aqr->so = NULL;
    new_node_aqr->ne = NULL;
    new_node_aqr->se = NULL;

    return new_node_aqr;

}

typedef struct _un_noeud { 
    Un_truc *truc; //Une station ou une connexion 
    Une_coord limite_no; // longitude min et latitude max
    Une_coord limite_se; // longitude max et latitude min
    struct _un_noeud *no; //Fils pour quart NO 
    struct _un_noeud *so; //Fils pour quart SO 
    struct _un_noeud *ne; //Fils pour quart NE 
    struct _un_noeud *se; //Fils pour quart SE 
} Un_noeud;

typedef struct _une_coord { 
    float lon;  /*Longitude decimale*/ 
    float lat; /*Latitude decimale*/
} Une_coord;


typedef struct _un_truc { 
    Une_coord coord;
    Ttype type;
    Tdata data;
    float user_val; /*Distance pour plus court chemin*/
} Un_truc;

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    /* on vérifie la comptabilité des coordonnes */

    if(limite_no.lat >= truc->coord.lat &&  limite_no.lon >= truc->coord.lon && limite_se.lat >= truc->coord.lat && limite_se.lon >= truc->coord.lon)
    {
    

        /* on crée un nouvel élément et on initialise ses valeurs */
        Un_noeud *new_node = (Un_noeud *) malloc (sizeof(Un_noeud));
        new_node->truc = truc;
        new_node->no = NULL;
        new_node->so = NULL;
        new_node->ne = NULL;
        new_node->se = NULL;

        Un_noeud *current = aqr;

        /* si le truc à insérer dans l'aqr est NULL on ne fait rien */
        if(!truc)
        {
            return NULL;
        }

        if(!aqr)
        {
            aqr = (Un_noeud *)malloc(sizeof(Un_noeud));
            aqr = new_node;
            return aqr;
        }

        /* on a dépassé le seuil défini : le problème n'est plus pertinant à cette distance */
        if (abs(current->no->limite_no.lat - current->no->limite_se.lat) <= 0.5 && abs(current->no->limite_no.lon - current->no->limite_se.lon) <= 0.5) 
        {
            /* changer les coordonnees du truc, truc->coord.lon et truc->coord.lat */
            
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
    Un_elem *phead = head;
    
    Un_noeud *aqr = NULL;
    Un_noeud *_aqr = NULL;

    while(phead)
    {
        aqr = inserer_aqr(aqr,phead->truc->coord,phead->truc->coord,phead->truc);
        phead = phead->suiv;
    }

    _aqr = aqr;

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
        /* changer les coordonnees du truc, truc->coord.lon et truc->coord.lat */
        
        return NULL; 
    } 

    /* d'abord, on regarde si le truc est à l'ouest ou à l'est. ensuite, on regarde s'il doit être au nord ou au sud */

    if((float)(ptr->no->limite_no.lat + ptr->no->limite_se.lat)/2 >= coord.lat)
    {
        /* ici, le truc est à l'ouest */
        
        if((ptr->no->limite_no.lon + ptr->no->limite_se.lon)/2 >= coord.lon)
        {
            /* ici, le truc sera placé à la branche nord ouest */
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
            /* ici, le truc sera placé à la branche sud ouest */
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
        /* ici, le truc sera placé à l'est */
        if((ptr->no->limite_no.lon + ptr->se->limite_se.lon)/2 >= coord.lon)
        {
            /* ici, le truc sera placé à la branche nord est */
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

