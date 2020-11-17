#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "lignes.h"

#define NB_LIGNES 100

//fonction pour ajouter une valeur au debut ;

Une_ligne *ajouter_debut(Une_ligne * head, char* code, char* color, float intervalle, float vitesse)
{
   // printf("fct ajouter debut : %s \n", code);
    Une_ligne * nouv = (Une_ligne *) malloc (sizeof(Une_ligne));
    nouv -> code = code;
    nouv -> color = color;
    nouv -> intervalle = intervalle;
    nouv -> vitesse = vitesse;
    nouv -> suiv = head; /*suiv pointe sur tete*/
    

    return (nouv);
}

//fonction pour ajouter une valeur à la fin ;

Une_ligne * ajouter_fin(Une_ligne* head, char* code, char* color, float intervalle, float vitesse)
{
    if (!head)
    {
        head = ajouter_debut(head, code, color, intervalle, vitesse);
        //printf("fct ajouter fin le IF : %s \n", code);
    }
    else
    {
        Une_ligne *nouv = (Une_ligne *) malloc (sizeof (Une_ligne));
        nouv -> code = code;
        nouv -> color = color;
        nouv -> intervalle = intervalle;
        nouv -> vitesse = vitesse;
        nouv -> suiv = NULL;/*car c'est le dernier il n'y a pas de suivant*/
        
        Une_ligne* temp = head;
        while (temp->suiv)
        {
            temp = temp->suiv;
        }
        temp->suiv = nouv;
      //printf("fct ajouter debut ELSE : %s \n", code);
    }
    return (head); 
}

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

//fonction lire lignes;

Une_ligne* lire_lign(char* nom_fichier)
{
    FILE* fichier ;
    
    //on ouvre le fichier csv
    fichier = fopen( "lignes_met.csv", "r") ;
       
    if (fichier == NULL)
    {
        printf("Ouverture du fichier impossible");
        exit(0);
    }
    
    char ligne[NB_LIGNES];
    char* ptr_chaine = fgets(ligne, NB_LIGNES, fichier);
    Une_ligne* head = malloc (sizeof(Une_ligne));
    Une_ligne* phead = head;
    int i=0;
    int j=0;
    
    char* ptr_code;
    ptr_code =  malloc (10 * sizeof (char));
    char* ptr_color;
    ptr_color = malloc (10 * sizeof (char));


    while(ligne[i]!=';')
    {
        ptr_code[j]=ligne[i];
        i++;
        j++;
    }
    
    ptr_code[j]='\0';
    i++;
    head -> code = malloc (10 * sizeof(char));
    strcpy(head -> code, ptr_code);
    head -> vitesse = strtof(ligne+i, NULL);
    
    while (ligne[i] != ';')
    {
        i++;
    }
    
    i++;
    head -> intervalle = strtof(ligne+i, NULL);
    while(ligne[i] != ';')
    {
        i++;
    }
    i++;
    j=0;
    
    while (ligne[i] != '\0')
    {
        ptr_color[j]= ligne[i];
        i++;
        j++;
    }
    head -> color = malloc (10*sizeof (char));
    strcpy(head -> color, ptr_color);
    ptr_chaine = fgets(ligne, NB_LIGNES, fichier);
    while(ptr_chaine != NULL)
    {
        i=0;
        j=0;
        Une_ligne* ptr_ligne = malloc (sizeof (Une_ligne));
        while (ligne[i] != ';')
        {
            ptr_code[j]= ligne[i];
            i++;
            j++;
        }
        i++;
        ptr_ligne -> code = malloc (10*sizeof(char));
        strcpy(ptr_ligne -> code, ptr_code);
        ptr_code[2] = '\0';
        ptr_ligne-> vitesse = strtof(ligne+i, NULL);
        while (ligne[i] != ';')
        {
            i++;
        }
        i++;
        ptr_ligne -> intervalle = strtof(ligne+i, NULL);
        while(ligne[i] != ';')
        {
            i++;
        }
        i++;
        j = 0;
        while (ligne[i] != '\0')
        {
            ptr_color[j]= ligne[i];
            i++;
            j++;
        }
        i++;
        ptr_ligne -> code = malloc (10*sizeof(char));
        strcpy(ptr_ligne->code, ptr_code);
        ptr_code[2] = '\0';
        ptr_ligne -> vitesse = strtof(ligne+i, NULL);
        while (ligne[i] != ';')
        {
            i++;
        }
        i++;
        ptr_ligne -> intervalle = strtof(ligne+i, NULL);
        while(ligne[i] != ';')
        {
            i++;
        }
        i++; 
        j=0;
        while(ligne[i] != '\0')
        {
            ptr_color[j] = ligne[i];
            i++;
            j++;
        }
        ptr_ligne->color = malloc (10*sizeof(char));
        strcpy(ptr_ligne->color, ptr_color);
        phead -> suiv = ptr_ligne;
        ptr_chaine = fgets(ligne, NB_LIGNES,fichier);
        phead = phead -> suiv;
    }
    fclose (fichier);
    afficher_lignes(head);
    return (head);
}


    
    
    // on lit le fichier ligne par ligne
    
  /* while (fgets( ligne, NB_LIGNES, fichier) != NULL)
   {
         
        // on appelle la fonction strtok et on initialise ptr_chaine

        ptr_chaine = strtok (ligne, ";");

        // code métro

        if (sscanf(ptr_chaine,"%s",code) != 1)
        {
            puts("\n Problème lors de la lecture");
            code[0] = 19;
        }
        ptr_chaine = strtok (NULL, ";");
        
        // vitesse

        if (sscanf(ptr_chaine,"%2f", &vitesse) != 1)
        {
            puts("\n Problème lors de la lecture");
            vitesse = -1.0;
        }
        ptr_chaine = strtok (NULL, ";");

        // intervalle
        
        if (sscanf(ptr_chaine,"%2f", &intervalle) != 1)
        {
            puts("\n Problème lors de la lecture");
            intervalle = -1.0;
        }
        ptr_chaine = strtok (NULL, ";");
        
        // couleur

        if (sscanf(ptr_chaine,"%s", color) != 1)
        {
            puts("\n Problème lors de la lecture");
            color[0] = 0;
        }
        ptr_chaine = strtok (NULL, ";");
    
       head = ajouter_fin(head,code,color,intervalle,vitesse);
    }

    //fermeture du fichier
    fclose(fichier);
    
    return head;
}*/

//fonction pour chercher une ligne en fct de son code;

Une_ligne* chercher_ligne(Une_ligne* lligne,char* code1 )
{
    Une_ligne* head = lligne;
    
    // tant que la liste n'est pas finie
    while (head != NULL)
    {

        if (strcmp(code1, head->code) == 0)
        {
            return head;
        }
        head = head->suiv;
    }
    return NULL;

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


int main(int argc, char **argv)
{
    
    Une_ligne* ligne;
    ligne = lire_lign("../lignes_met.csv");
    
    afficher_lignes(ligne);
    
    
    return 0;
}
