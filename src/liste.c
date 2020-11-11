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

