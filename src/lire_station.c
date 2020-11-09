#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

Un_elem* lire_station()
{
   /*-- ouverture du fichier --*/
   
   FILE* fichier;
   fichier = fopen ("station_metro.csv", "rt");
   
   if(fichier == NULL)
   {
       printf("ouverture impossible du fichier \n");
       return 0;
   }
   
   
           /*-- lecture du fichier --*/
   
   char ligne[200]; /* 200 est le nombre de caractère maximal d'une ligne */
   const char* separator = ";";
   char* ptr_chaine;/* on définit un pointeur pour récuperer le "token"*/
   

   while(fgets(ligne,200,fichier) != NULL)
   {
       ptr_chaine = strtok (ligne, separator);
       while (ptr_chaine != NULL)
       {
           printf ("%s \t", ptr_chaine);
           ptr_chaine = strtok (NULL, separator);
       }
       printf("\n");
   }
   fclose(fichier);
   
    return 0;
}


