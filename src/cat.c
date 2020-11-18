#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lignes.h"


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

//fonction pour afficher la liste;
void afficher_lignes(Une_ligne *head)
{
    while (head)
    {
        printf("\n code :%s", head->code);
        printf("\n vitesse : %.2f", head->vitesse);
        printf("\n intervalle : %.2f", head->intervalle);
        printf("\n couleur : %s \n\n", head->color);
        head = head -> suiv;
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

Une_ligne *lire_ligne(char *nom_fichier)
{
    FILE* fichier ;
    Une_ligne *head = (Une_ligne*) malloc (sizeof(Une_ligne));

    
    //on ouvre le fichier csv

    fichier = fopen("lignes_met.csv", "r") ;
    
    if (fichier == NULL)
    {
        printf("\n L'ouverture du fichier est impossible \n");
        exit(1);
    }

    char* ptr_ligne = NULL;
    size_t size = 0;
    char* line = NULL;
    Une_ligne* phead = head;
    Une_ligne* pphead = head;

    //on lit ligne par ligne ;
    while(getline(&ptr_ligne, &size, fichier) != -1)
    {

        pphead = head ;
        line = NULL;
        
        //pour code ;
        line = strtok(ptr_ligne, ";");
        head->code = NULL;
        head->code = (char*) malloc((strlen(line)+1)*sizeof(char));
        
        if (head->code == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (head->code, line);
    
        //pour vitesse ;
        line = strtok(NULL, ";");
        head ->vitesse = (float) atof(line);
        
        //pour intervalle;
        line = strtok(NULL, ";");
        head ->intervalle = (float) atof(line);
        
        //pour color ;
        line = strtok(NULL, ";");
        head->color = NULL;
        head->color = (char*) malloc((strlen(line)+1)*sizeof(char));
           
        if (head->color == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (head->color, line);
        
        // pour passer sur le suivant; 
        head->suiv = NULL;
        head->suiv = (Une_ligne*) malloc (sizeof (Une_ligne));
        
        if (head -> suiv == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        head = head->suiv;

    }
    pphead->suiv = NULL;


    //fermeture du fichier
    fclose(fichier);
    afficher_lignes(phead);
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
    ligne = lire_ligne("../lignes_met.csv");
    
    return 0;
}

