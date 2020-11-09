#include "liste.h"
#include "station.h"
#include "truc.h"
#include <stdlib.h>
#include <stdio.h>


Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc)
{
    /* on veut inserer le truc dans la liste de maniere croissante*/

    Un_elem *current = liste;

    Un_elem *element;
    element->truc = truc;

    /* si la liste est nulle ou si l'element a inserer a un user_val plus grand que la tete de liste, on ajoute au debut*/

    if((liste == NULL) || (truc->user_val > liste->truc->user_val))
    {
        element->suiv = liste;
        liste = element;
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
    return liste;
}

void ecrire_liste(FILE *flux, Un_elem *liste)
{
    /* on veut afficher les trucs correspondants a des stations */
    

}

