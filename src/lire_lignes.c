#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne.h"

#define NB_LIGNES 100

//fonction pour ajouter une valeur au debut ;

Une_ligne *ajouter_debut(Une_ligne * head, char* code, char* color, float intervalle, float vitesse)
{
    Une_ligne * nouv = (Une_ligne *) malloc (sizeof(Une_ligne));
    nouv -> code = code;
    nouv -> color = color;
    nouv -> intervalle = intervalle;
    nouv -> vitesse = vitesse;
    nouv -> suiv = head; /*suiv pointe sur tete*/

    return (nouv);
}

//fonction pour ajouter une valeur à la fin ;

Une_ligne * ajouter_fin(Une_ligne *head, char *code, char *color, float intervalle, float vitesse)
{
    if (!head)
    {
        head = ajouter_debut(head, code, color, intervalle, vitesse);
    }
    else
    {
        Une_ligne *nouv = (Une_ligne *) malloc (sizeof (Une_ligne));
        nouv -> code = code;
        nouv -> color = color;
        nouv -> intervalle = intervalle;
        nouv -> vitesse = vitesse;
        nouv -> suiv = NULL;/*car c'est le dernier il n'y a pas de suivant*/
        
        Une_ligne *temp = head;
        while (temp->suiv)
        {
            temp = temp->suiv;
        }
        temp->suiv = nouv;
    }
    return (head);
}

//fonction pour afficher la liste;

void afficher_lignes(Une_ligne *head)
{
    while (head)
    {
        printf("\ncode : %s", head->code);
        printf("\ncouleur : %s", head->color);
        printf("\nintervalle : %.2f", head->intervalle);
        printf("\nvitesse : %.2f\n", head->vitesse);
        head = head -> suiv;
    }
}

//fonction pour désallouer la mémoire;

void detruire_lignes(Une_ligne* head)
{
    Une_ligne* phead = head;
    while (phead)
    {
        head = phead;
        free(phead->code);
        free(phead->color);
        free(&(phead->intervalle));
        free(&(phead->vitesse));
        phead = phead -> suiv;
    }
}// pas encore tester

//fonction lire lignes; 

Une_ligne *lire_ligne()
{
    FILE* fichier ;
    char ligne[NB_LIGNES];
    char *ptr_chaine ; 
    Une_ligne *head = NULL;
    Une_ligne *phead = NULL;

    // notre fichier lignes_metro.csv a 3 cellules : vitesse, intervalle et couleur

    char code[4];
    float vitesse;
    float intervalle;
    char color[10];

    int num_ligne = 1;
    //on ouvre le fichier csv 

    fichier = fopen( "lignes_metro.csv", "r") ;
    
    if (fichier == NULL)
    {
        printf("Ouverture du fichier impossible");
        exit(0);
    }

    // on lit le fichier ligne par ligne
    
    while (fgets( ligne, NB_LIGNES, fichier) != NULL)
    {
         
        // on appelle la fonction strtok et on initialise ptr_chaine 

        ptr_chaine = strtok (ligne, ";");

        // code metro

        if (sscanf(ptr_chaine,"%s",code) != 1)
        {
            puts("\nProblème lors de la lecture");
            code[0] = 19;
        }
        ptr_chaine = strtok (NULL, ";");

        // vitesse

        if (sscanf(ptr_chaine,"%2f", &vitesse) != 1)
        {
            puts("\nProblème lors de la lecture");
            vitesse = -1.0;
        }

        ptr_chaine = strtok (NULL, ";"); 

        // intervalle 

        if (sscanf(ptr_chaine,"%2f", &intervalle) != 1)
        {
            puts("\nProblème lors de la lecture");
            intervalle = -1.0;
        }

        ptr_chaine = strtok (NULL, ";"); 

        // couleur

        if (sscanf(ptr_chaine,"%s", color) != 1) 
        {
            puts("\nProblème lors de la lecture");
            color[0] = 0;
        }
        head = ajouter_fin(head,code,color,intervalle,vitesse);

        printf("\ncode : %s", head->code);
        printf("\ncouleur : %s", head->color);
        printf("\nintervalle : %.2f", head->intervalle);
        printf("\nvitesse : %.2f\n", head->vitesse);

        // ca donne le mauvais truc 
        
        ptr_chaine = strtok (NULL, ";");              
          
    }
    phead = head;

    //fermeture du fichier
    fclose(fichier);
    
    return phead;
}

//fonction pour chercher une ligne en fct de son code; 

Une_ligne* chercher_ligne(Une_ligne* head, char* code)
{
    char* c;
    while (strcmp(c, code) && head != NULL)
    {
        head = head -> suiv;
    }
    
    if (!head)
    {
        return NULL;
    }
    else
    {
        return head;
    }
}// pas encore tester !

int main()
{
    Une_ligne *ligne;
    ligne = lire_ligne("../lignes_metro.csv");
    return 0;
}