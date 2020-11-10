#include "liste.h"
#include "station.h"
#include "truc.h"
#include <stdlib.h>
#include <stdio.h>


Un_elem *inserer_liste_trie(Un_elem *head, Un_truc *truc)
{
    /* on veut inserer le truc dans la liste de maniere croissante*/

    Un_elem *current = head;

    Un_elem *element;
    element->truc = truc;

    /* si la liste est nulle ou si l'element a inserer a un user_val plus grand que la tete de liste, on ajoute au debut*/

    if((head == NULL) || (truc->user_val > head->truc->user_val))
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

Un_elem* inserer_ded_liste(Un_elem* liste, Un_truc* truc)
{
  
    Un_elem * nouv = (Un_elem *)malloc(sizeof(Un_elem));
    nouv -> truc = truc ;
    nouv -> suiv = liste;
    return (nouv);
}
//fonction à tester ! pas encore testé

