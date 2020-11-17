#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ligne.h"

#define NB_LIGNES 100


Une_ligne *create(char *code_, char *color_, float intervalle_, float vitesse_)
{
    Une_ligne *nouv = (Une_ligne *) malloc (sizeof(Une_ligne));
    nouv -> code = (char *)malloc(5*sizeof(char));
    nouv-> code = code_;
    nouv -> color = (char *)malloc(20*sizeof(char));
    nouv-> color = color_;
    nouv -> intervalle = intervalle_;
    nouv -> vitesse = vitesse_;
    nouv -> suiv = NULL; 

    return nouv;
}

Une_ligne *ajout(Une_ligne *head, char *code_, char *color_, float intervalle_, float vitesse_)
{
    /* si la tete est vide où que le code de l'élément à ajouter est plus petit que la tête on ajoute au début */
    
    Une_ligne * new = create(code_,color_,intervalle_,vitesse_);
    Une_ligne *temp = head;

    if ((!head) || (strcmp(head->code,code_) > 0))
    {
        new -> suiv = head; /*suiv pointe sur tete*/
        head = new;
    }

    else
    {
        while (temp->suiv)
        {
            temp = temp->suiv;
        }
        new->suiv = temp->suiv;
        temp->suiv = new;
    }
    return head;
}

//fonction pour afficher la liste;

void afficher_lignes(Une_ligne *head)
{
    Une_ligne *ptr = head;
    
    while(ptr != NULL)
    {
    printf("code : %s\n", ptr->code);
    printf("couleur : %s\n", ptr->color);
    printf("intervalle : %.2f\n", ptr->intervalle);
    printf("vitesse : %.2f\n\n", ptr->vitesse);
    ptr = ptr -> suiv;
    }
    
}

//fonction pour désallouer la mémoire;

void detruire_lignes(Une_ligne* head)
{
    Une_ligne *phead = head;
  
    while (phead)
    {
        head = phead;
        free(phead->code);
        free(phead->color);
        free(&(phead->intervalle));
        free(&(phead->vitesse));
        phead = head -> suiv;
    }
}// pas encore tester

//fonction lire lignes; 

Une_ligne *lire_ligne()
{
    FILE* fichier ;
    char ligne[NB_LIGNES];
    char *ptr_chaine ; 
    Une_ligne *head = NULL;

    char *code = (char *)malloc(sizeof(char)*4);
    char *couleur = (char *)malloc(sizeof(char)*20);
    double vitesse;
    double intervalle;
    
    const char *separator = ";";

    //on ouvre le fichier csv 

    fichier = fopen("lignes_metro.csv", "r") ;
    
    if (fichier == NULL)
    {
        printf("Ouverture du fichier impossible");
        exit(1);
    }

    // on lit le fichier ligne par ligne
    
    while (fgets( ligne, NB_LIGNES, fichier) != NULL)
    {
        // on appelle la fonction strtok et on initialise ptr_chaine 
        ptr_chaine = strtok (ligne, separator);
        
        //code
        strcpy(code,ptr_chaine);
    
        // vitesse
        ptr_chaine = strtok (NULL, separator);
        vitesse = atof(ptr_chaine);

        //intervalle 
        ptr_chaine = strtok (NULL, separator); 
        intervalle = atof(ptr_chaine); 

        // couleur
        ptr_chaine = strtok (NULL, separator); 
        strcpy(couleur,ptr_chaine);

        head = ajout(head,code,couleur,intervalle,vitesse);
    }

    //fermeture du fichier
    fclose(fichier);

    Une_ligne *phead = head;

    return phead;
}

//fonction pour chercher une ligne en fct de son code; 

Une_ligne* chercher_ligne(Une_ligne* head, char* code)
{
    char* c = head->code; // il faut initialiser c
    while (strcmp(c, code) && head != NULL)
    {
        head = head -> suiv;
    }
    
    if (!head)
    {
        printf("La ligne n'est pas présente\n");
        return NULL;
    }
    else
    {
        printf("La ligne est bien présente\n");
        return head;
    }
}

int main()
{
    Une_ligne *ligne;
    ligne = lire_ligne("../lignes_metro.csv");
    afficher_lignes(ligne);
    //detruire_lignes(ligne);
    return 0;
}