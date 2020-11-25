#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "truc.h"
#include "coord.h"
#include "liste.h"
#include "station.h"
#include "abr.h"
#include "aqrtopo.h"

int main()
{
    Une_ligne* liste_ligne;
    printf("\n Voici la liste des lignes de métro : \n\n");
    liste_ligne = lire_ligne("../lignes_metro.csv");

    Un_truc *truc;
    Une_coord coord;
    Ttype type;
    Tdata data;
    double uv;
    truc = creer_truc(coord, type, data, uv);
    //detruire_truc(truc);
    
    Un_elem* liste = NULL;    
    liste = inserer_liste_trie(liste, truc);
    FILE* fichier;
    fichier = fopen ("../station_metro.csv", "r");
    ecrire_liste(fichier, liste);
    //detruire_liste(liste);
    //detruire_liste_et_truc(liste);
    
    Un_elem *stations;
    stations = lire_stations("../stations_metro.csv");
    /*
    Une_coord *limite_no;
    Une_coord *limite_se;
    limites_zone(liste, limite_no, limite_se);*/
    

    // Excercice 2 :
   /* Un_nabr* noeud;
    noeud = creer_nabr(truc);
    
    Un_nabr* abr;
    Un_nabr* node;
    abr = inserer_abr(abr, node);
    
    Un_elem* liste_sta;
    liste_sta = construire_abr(liste_sta);
    detruire_abr(abr);
    
    char* nom;
    printf("\n Saisir le nom de la station souhaité : \n");
    gets(nom);
    checher_station(abr, nom);


    // Exercice 3 :
    Une_ligne* liste_ligne;
    printf("\n Voici la liste des lignes de métro : \n");
    liste_ligne = lire_ligne("../ligne_metro.csv");
    detruire_lignes(liste_ligne);
    char* code;
    
    printf("\n Saisir le code de la ligne souhaité :\n");
    gets(code);
    chercher_ligne(liste_ligne, code);*/
    /*
    // Exercice 4 :
    Un_elem* new_liste;
    new_liste = inserer_deb_liste(liste, truc);
    printf("\n Voici la liste des connexions de métro : \n");
    //lire_connexion = (liste_ligne, abr_sta);
    
    
    //Exercice 5 :
    Un_noeud* aqr;
    Une_coord *limite_no = NULL;
    Une_coord *limite_se = NULL;
    aqr = inserer_aqr(aqr, *limite_no, *limite_se, truc);
    aqr = construire_aqr(liste_sta);
    detruire_aqr(aqr);

    Une_coord* coord;
    printf("\n Saisir la valeur de la coordonnée souhaitée : \n");
    scanf("%f", coord);
    chercher_aqr(aqr, coord);*/
    
   return 0;
    
}