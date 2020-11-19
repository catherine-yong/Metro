#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "truc.h"
#include "liste.h"
#include "ligne.h"
#include "ABR.h"

typedef struct _nouv
{
    Un_nabr* sta_dep;
    Un_nabr* sta_arr;
    Une_ligne* ligne;
    struct _nouv *suiv;
} nouv;

void afficher_connexion(nouv *head)
{
    while (head)
    {
        printf("\n station de départ : %s",head->sta_dep->truc->data.sta.nom);
        printf("\n station d'arriver : %s",head->sta_arr->truc->data.sta.nom);
        printf("\n ligne : %s", head->ligne->code);
        head = head -> suiv;
    }

}

Un_elem* lire_connexions()
{
   
    //ouverture du fichier .csv;
    FILE* fichier ;
    fichier = fopen("connexion.csv", "r") ;
            //on teste si l'ouverture du fichier est possible
    if (fichier == NULL)
    {
        printf("\n L'ouverture du fichier est impossible \n");
        exit(1);
    }

    //déclaration des variables nécessaires;
    /*Un_nabr* sta_dep = (Un_nabr*) malloc(sizeof(Un_nabr));
    Un_nabr* sta_arr = (Un_nabr*) malloc(sizeof(Un_nabr));
    Une_ligne* ligne = (Une_ligne*) malloc (sizeof(Une_ligne));*/
    nouv* head = (nouv*) malloc(sizeof(nouv));
    
    //suite ;
    /*Un_nabr* ptr_sta_dep = sta_dep;
    Un_nabr* p_sta_dep = sta_dep;
    Un_nabr* ptr_sta_arr = sta_arr;
    Un_nabr* p_sta_arr = sta_arr;
    Une_ligne* ptr_ligne = ligne;
    Une_ligne* p_ligne = ligne;*/
    nouv* phead = head;
    nouv* pphead = head;
    

    //outils pour get line ;
    char* ptr = NULL;
    size_t size = 0;// l'utilisation de getline requiert un type size_t, que l'on initialise à 0
    char* line = NULL;
    
    
    //on lit ligne par ligne ;
    while(getline(&ptr, &size, fichier) != -1)
    {
        pphead = head;
        
        //pour station de départ ;
        line = strtok(ptr, ";");
        head -> sta_dep = NULL;
        head -> sta_dep = (Un_nabr*) malloc((strlen(line)+1)*sizeof(Un_nabr));
           
        if (head -> sta_dep == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (head->sta_dep->truc->data.sta.nom , line);
        
        
        //pour station d'arrivée ;
        line = strtok(NULL, ";");
        head -> sta_arr = NULL;
        head -> sta_arr = (Un_nabr*) malloc((strlen(line)+1)*sizeof(Un_nabr));
         
        if (head -> sta_arr == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            fclose(fichier); 
            exit(1);
        }
        strcpy (head->sta_arr->truc->data.sta.nom, line);
        
        //pour ligne ;
        line = strtok(NULL, ";");
        head -> ligne = NULL;
        head -> ligne = (Une_ligne*) malloc((strlen(line)+1)*sizeof(Une_ligne));
              
        if (head -> ligne == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            fclose(fichier);
            exit(1);
        }
        strcpy (head -> ligne -> code, line);
        
        
        // pour passer au suivant;
        head-> suiv = NULL;
        head-> suiv= (nouv*) malloc (sizeof (nouv));
            
        if (head -> suiv == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            fclose(fichier);
            exit(1);
        }
        head = head->suiv;
        
     }
    pphead->suiv = NULL;
    
    //fermeture du fichier
    fclose(fichier);
    afficher_connexion(phead);
    return (0);
        
}
int main()
{
    lire_connexions();

    return 0;
}
