#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station_metro.csv"
#include "liste.h"

typedef struct
{
    char* nom;
    float* latitude;
    float* longitude;
}info_station;

un_elem* lire_station()
{
                /*--- ouverture du fichier ---*/
    FILE* fichier;
    fichier = fopen ("station_metro.csv", "r");
    if(fichier == NULL)
    {
        printf("ouverture impossible \n");
        return 0;
    }
    
                            /* --- */
    char ligne[200];
    char* ptr_chaine;/* pointeur pour récuperer le "token"*/
    int num_ligne = 1;
    char nom[100];//pour le nom de la station
    float lat; //soit la latitude
    float longi; //soit pour la longitude
    
    
    while(fgets(ligne,200,fichier) != NULL)
    {
        printf("ligne %d \n", num_ligne);
        num_ligne++;
        ptr_chaine=strtok(ligne, ";"); /* on découpe la chaine avec le séparateur ";"*/
        
        //distinction des cas car pas du même type
        if (sscanf(ptr_chaine, "%s", nom))
        {
            nom[0]=0;
        }
        ptr_chaine = strtok(NULL,";"); /* pour aller vers le "token" suivant*/
        
        if(sscanf(ptr_chaine, "%f", &lat))
        {
            printf("%s \n", ptr_chaine);
        }
        ptr_chaine = strtok(NULL, ";");
        
        if(sscanf(ptr_chaine, "%f", &longi))
        {
            printf("%s \n", ptr_chaine);
        }
        ptr_chaine = strtok(NULL, ";");

        
        printf("\n nom de la station : %s", nom);
        printf("\n latitude : %f", lat);
        printf("\n longitude : %f", longi);
    }
    fclose(fichier);
    return 0;
}

int main()
{
    lire_station();
    return 0; 
}
