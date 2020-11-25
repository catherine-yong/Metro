#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_LIGNES 100

#include "ligne.h"

//fonction pour afficher la liste;

//fonction pour afficher la liste;
void afficher_lignes(Une_ligne *head)
{
    /* on souhaite afficher la liste */

    while (head)
    {
        printf("code :%s", head->code);
        printf("\n vitesse : %.2f", head->vitesse);
        printf("\n intervalle : %.2f", head->intervalle);
        printf("\n couleur : %s \n\n", head->color);
        head = head -> suiv;
    }

}

//fonction pour désallouer la mémoire;

void detruire_lignes(Une_ligne* head)
{
    /* on souhaite désallouer la mémoire  */

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
    /* on souhaite lire les lignes du fichier passé en paramètre */

    FILE* fichier ;
    Une_ligne *head = (Une_ligne*) malloc (sizeof(Une_ligne));

    //on ouvre le fichier csv

    fichier = fopen(nom_fichier, "r") ;
    
    // on teste si on peut bien ouvrir le fichier

    if (!fichier)
    {
        printf("\n L'ouverture du fichier est impossible \n");
        fclose(fichier);
        exit(1);
    }

    char* ptr_ligne = NULL;
    size_t size = 0;    // l'utilisation de getline requiert un type size_t, que l'on initialise à 0
    char* line = NULL;
    Une_ligne* phead = head;
    Une_ligne* pphead = head;

    /* nous procédons de la manière suivante : on parcourt le fichier avec un pointeur line et ptr_ligne qui est de type char.
        nous souhaitons parcourir de token en token pour insérer les token dans le champ correspondant à la liste chainee.

        pour le code et la couleur, il suffit simplement de recopier la valeur du pointeur dans le champ de la liste.
        cependant, pour l'intervalle et la vitesse, qui sont des float, il est nécessaire de les convertir en char, 
        d'où l'utilisation de atof */


    while(getline(&ptr_ligne, &size, fichier) >= 0)
    {
        pphead = head ;
        
        //pour code ;
        line = strtok(ptr_ligne, ";");  // on initialise line pour lui indiquer qu'on parcourt le fichier 
        
        head->code = NULL;
        head->code = (char*) malloc((strlen(line)+1)*sizeof(char));
        
        // on vérifie que le champ n'est pas vide
        if (head->code == NULL)
        {
            printf("\nIl y a un problème dans le fichier. Allocation impossible \n");
            fclose(fichier);
            exit(1);
        }
        strcpy (head->code, line);
            
        line = strtok(NULL, ";");   // on passe au token suivant

        //pour vitesse ;

        head ->vitesse = (float) atof(line);  

        // on vérifie que le champ est valide
        if(head->vitesse <= 0)
        {
            printf("Il y a un problème dans le fichier\n");
            fclose(fichier);
            exit(1);
        }
        
        line = strtok(NULL, ";");  // on passe au token suivant

        //pour intervalle;

        head ->intervalle = (float) atof(line);

        // on vérifie que le champ est valide
        if(head->intervalle <= 0)
        {
            printf("Il y a un problème dans le fichier\n");
            fclose(fichier);
            exit(1);
        }
        
        line = strtok(NULL, ";");  // on passe au token suivant

        //pour color ;
        head->color = NULL;
        head->color = (char*) malloc((strlen(line)+1)*sizeof(char));
        
        // on vérifie que le champ n'est pas vide
        if (!head->color)
        {
            printf("\n Il y a un problème dans le fichier. Allocation impossible. \n");
            fclose(fichier);
            exit(1);
            
        }

        strcpy (head->color, line);
        
        // pour passer sur le suivant : on alloue la mémoire nécessaire puis on passe sur le suivent; 

        head->suiv = NULL;
        head->suiv = (Une_ligne*) malloc (sizeof (Une_ligne));
        
        if (!head -> suiv)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            fclose(fichier);
            exit(1);
        }

        head = head->suiv; 

    }
    pphead->suiv = NULL;    // pour ne pas avoir un autre maillon en plus

    //fermeture du fichier
    fclose(fichier);
    afficher_lignes(phead);
    return phead;
}

Une_ligne* chercher_ligne(Une_ligne *head, char *code)
{
 
    while ((strcmp(head->code, code) != 0) && head->suiv != NULL)
    {
        head = head -> suiv;
    }

    if(strcmp(head->code , code) == 0)
    {
        printf("La ligne est bien présente\n");
        return head;
    }

    else
    {
    printf("La ligne n'est pas présente\n");
    return NULL;
    }
    
}

int main()
{
    Une_ligne *ligne;
    ligne = lire_ligne("../lignes_metro.csv");
    char *numero_metro = "M9";
    chercher_ligne(ligne,numero_metro);
    return 0;
}
