#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "truc.h"
#include "liste.h"
#include "ligne.h"
#include "ABR.h"

void afficher_connexion(Une_connexion *head)
{
    while (head)
    {
        printf("\n station de départ : %s", head->sta_dep->data.sta.nom);
        printf("\n station d'arriver : %s", head-> sta_arr->data.sta.nom);
        printf("\n ligne : %s", head->ligne->code);
       // head = head -> suiv;
    }

}

Un_elem* lire_connexions(Une_ligne *liste_ligne, Un_nabr * abr_sta)
{
   
    //ouverture du fichier .csv
    FILE* fichier ;
    fichier = fopen("connexion.csv", "r") ;
    if (fichier == NULL)
    {
        printf("\n L'ouverture du fichier est impossible \n");
        exit(1);
    }

    //liste_ligne = (Une_ligne*) malloc (sizeof(Une_ligne));
    //abr_sta = (Un_nabr*) malloc(sizeof(Un_nabr));
    Un_elem* ptr = (Un_elem*)malloc(sizeof(Un_elem));
    char* ptr_connex = NULL;
    size_t size = 0;
    char* line = NULL;
    Un_elem* head = ptr;
    Un_elem* phead = ptr;

    liste_ligne = (Une_ligne*) malloc (sizeof(Une_ligne));
     Une_ligne* pphead = liste_ligne;
    
    //on lit ligne par ligne ;
    /*
    liste_ligne = (Une_ligne*) malloc (sizeof(Une_ligne));
    abr_sta = (Un_nabr*) malloc(sizeof(Un_nabr));
    Un_nabr* phead = abr_sta;
    Une_ligne* head = liste_ligne;
    while(getline(&ptr_connex, &size, fichier) != -1)
    {
        phead = abr_sta ;
        line = NULL;
           
        //pour sta_dep ;
        line = strtok(ptr_connex, ";");
        abr_sta -> truc = NULL;
        abr_sta -> truc = (Un_nabr*) malloc((strlen(line)+1)*sizeof(Un_nabr));
           
        if (abr_sta -> truc == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (abr_sta->truc->data.sta.nom, line);
           
        //pour sta_arr;
        line = strtok(NULL, ";");
        abr_sta -> truc = NULL;
        abr_sta -> truc = (Un_nabr*) malloc((strlen(line)+1)*sizeof(Un_nabr));
         
        if (abr_sta -> truc == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (abr_sta->truc->data.sta.nom, line);
        
        //pour ligne ;
        line = strtok(NULL, ";");
        head-> code= NULL;
        head-> code = (Une_ligne*) malloc((strlen(line)+1)*sizeof(Une_ligne));
              
        if (head->code == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (head ->code, line);
        
        
        // pour passer sur le suivant;
        phead-> truc -> data.sta.nom = NULL;
        phead->truc -> data->sta->nom ->suiv = (Une_ligne*) malloc (sizeof (Une_ligne));
           
        if (head -> suiv == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        connex->suiv = NULL;
        head->suiv = (Une_ligne*) malloc (sizeof (Une_ligne));
           
        if (head -> suiv == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
     }
     */
    
    while(getline(&ptr_connex, &size, fichier) != -1)
    {
        phead = ptr ;
        line = NULL;
       
        //pour sta_dep ;
        line = strtok(ptr_connex, ";");
        ptr -> truc = NULL;
        ptr -> truc -> data.sta.nom = (Un_elem*) malloc((strlen(line)+1)*sizeof(Un_elem));
       
        if (abr_sta -> truc == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (ptr->truc->data.sta.nom, line);
       
        //pour sta_arr;
        line = strtok(NULL, ";");
        ptr -> truc = NULL;
        ptr -> truc = (Un_nabr*) malloc((strlen(line)+1)*sizeof(Un_nabr));
     
        if (ptr -> truc == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (ptr->truc->data.sta.nom, line);
    
        //pour ligne ;
        line = strtok(NULL, ";");
        pphead -> code = NULL;
        pphead-> code = (Une_ligne*) malloc((strlen(line)+1)*sizeof(Une_ligne));
          
        if (pphead->code == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        strcpy (pphead->code, line);
    
    
        // pour passer sur le suivant;
        phead-> suiv = NULL;
        phead-> suiv= (Un_elem*) malloc (sizeof (Un_elem));
       
        if (phead -> suiv == NULL)
        {
            printf("\n L'ouverture du fichier est impossible \n");
            exit(1);
        }
        
        phead = phead->suiv = NULL;
    }


    //fermeture du fichier
    fclose(fichier);
    return head;
   
}
