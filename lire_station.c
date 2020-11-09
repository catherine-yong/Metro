#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    FILE* fichier;
    fichier = fopen ("station_metro.csv", "rt");
    if(fichier == NULL)
    {
        printf("ouverture impossible \n");
        return 0;
    }
    /*------*/
    char ligne[200];
    char* ptr_chaine;/* pointeur pour récuperer le "token"*/
    const char * separators = ";";

    
    while(fgets(ligne,200,fichier) != NULL)
    {
        ptr_chaine = strtok (ligne, separators );
        while ( ptr_chaine != NULL )
        {
            printf ( "%s\n", ptr_chaine );
            ptr_chaine = strtok ( NULL, separators );
        }
    }
    return 0;
}

