#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "truc.h"
#include "coord.h"
#include "liste.h"
#include "station.h"
#include "abr.h"
#include "aqrtopo.h"

int main(void)
{
    // Exercice 1 : 
    Un_elem* stations; 
    stations = lire_stations("csv/stations_metro.csv");
     
    Une_coord *limite_no = (Une_coord*)malloc(sizeof(Une_coord));
    if(!limite_no)
    {
        printf("probleme allocation mémoire\n");
        return 1;
    }
    limite_no->lon = 2000; 
    limite_no->lat = -1000;                                           
    Une_coord *limite_se = (Une_coord*)malloc(sizeof(Une_coord));
    if(!limite_se)
    {
        printf("probleme allocation mémoire\n");
        return 1;
    }
    limite_no->lon = -2000; 
    limite_no->lat = 1000;
    limites_zone(stations, limite_no, limite_se);                                           

    //Exercice 2 :
    Un_nabr* abr_sta = (Un_nabr*)malloc(sizeof(Un_nabr));
    abr_sta = construire_abr(stations);
                                                                 
    // Exercice 3 :                                 
    Une_ligne* liste_ligne; 
    liste_ligne = lire_ligne("csv/lignes_metro.csv");                                  
                                      
    // Exercice 4 :
    Un_elem* connexions; 
    connexions = lire_connexions("csv/connexions.csv",liste_ligne , abr_sta);
    // int compt = 0; //initialisation du compteur à 0                                  
    // Un_elem* head = stations; 
    // while (!head)
    // {   
    //     char* nom = head->truc>data.sta.nom; 
    //     Un_truc* new = checher_station(arbre, nom);
    //     head->truc= new; 
    //     head = head->suiv; 
    //     compt++; 
    // }
                                                                       
    // // Exercice 6 : 
    // int c; 
    // char* sta_dep; 
    // sta_dep = (char*)malloc(sizeof(char));  
    // printf("\n Veuillez entrer votre station de départ :\n");   
    // gets(sta_dep); 
    // while((c = getchar()) != '\n' && c != EOF);
    // Un_truc* truc_sta_dep = chercher_station(arbre, sta_dep);
                                                                   
    // char* sta_arr; 
    // sta_arr = (char*)malloc(sizeof(char));  
    // printf("\n Veuillez entrer votre station d'arrivée :\n");   
    // gets(sta_arr); 
    // while((c = getchar()) != '\n' && c != EOF);
    // Un_truc* truc_sta_arr = chercher_station(arbre, sta_arr);      

    // int chemin_voulu; 
    // printf("Veuillez entrer si vous préférez le choix le plus court (1) ou le plus rapide (0) :\n");                                 
    // scanf("%d", chemin_voulu); 
                                      
    // printf("\n Le trajet pour aller de %s à %s est :\n", sta_dep, sta_arr);
    // dijkstra(stations,truc_sta_dep,connexions,chemin_voulu); 
    // Un_elem* chemin = cherche_chemin(truc_sta_arr);
    // ecrire_chemin(chemin, connexions, chemin_voulu); 
                                      
    // // Désallocation de la mémoire : 
    // free(limite_no); 
    // free(limite_se);                                  
    // free(sta_dep); 
    // free(sta_arr); 
    // detruire_liste_et_truc(connexions);
    // detruire_lignes(liste_ligne); 
    // detruire_truc(truc_sta_dep);                                  
    // detruire_truc(truc_sta_arr); 
    // detruire_abr(arbre);                                 
                                      
   return 0;
    
}