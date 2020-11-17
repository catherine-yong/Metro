#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "my.h"
#include "liste.h"


Un_elem *lire_stations(char *nom_fichier)
{
    FILE* fd;
    char ligne[200];
    char *ptr_chaine;/* pointeur pour récuperer le "token"*/
    const char *separators = ";";

    fd = fopen(nom_fichier, "r");
    if (fd == NULL)
        return NULL;
    while (fgets(ligne, 200, fd) != NULL) {
        ptr_chaine = strtok(ligne, separators);
        while (ptr_chaine != NULL) {
            printf("%s\n", ptr_chaine); //create_truc() + inserer_liste_trie()
            ptr_chaine = strtok(NULL, separators);
        }
    }
    return ptr_chaine;
}

int main(int argc, char **argv)
{
   char *station;

   station = lire_stations("../stations_metro.csv"); 
}
