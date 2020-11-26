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
    // -- Exercice 1 -- 
    Un_elem* stations; 
    printf("\n Voici la liste des stations de métro : \n");
    stations = lire_station("station_metro.csv")
    
    // question 4 : 
    Une_coord *limite_no = (Une_coord*)malloc(sizeof(Une_coord);
    limite_no->lon = 2000; 
    limite_no->lat = -1000;                                           
    Une_coord *limite_se = (Une_coord*)malloc(sizeof(Une_coord);
    limite_no->lon = -2000; 
    limite_no->lat = 1000;
    limites_zone(stations, limite_no, limite_se);                                           

    // -- Exercice 2 --
    Un_nabr* arbre = (Un_nabr*)malloc(sizeof(Un_nabr);
    arbre = construire_abr(stations);
                                                                 
    // -- Exercice 3 --                                 
    Une_ligne* liste_ligne; 
    printf("\n Voici la liste des lignes de métro : \n");                                  
    liste_ligne = lire_ligne("../lignes_metro.csv");                                  
                                      
    // -- Exercice 4 --
    Un_elem* connexions; 
    printf("\n Voici la liste des connexions des stations de métro : \n");                                  
    connexions = lire_connexion("connexions.csv")
    int compt = 0; //initialisation du compteur à 0                                  
    Un_elem* head = stations; 
    while (!head)/*tant que head n'est pas nul*/
      {   
          char* nom = head->truc>data.sta.nom; 
          Un_truc* new = checher_station(arbre, nom);
          head->truc= new; 
          head = head->suiv; 
          compt++; 
      }
                                                                       
    // -- Exercice 6 -- 
    int a; 
    char* sta_dep; 
    sta_dep = (char*)malloc(sizeof(char));  
    printf("\n Veuillez entrer votre station de départ :\n");   
    gets(sta_dep); 
    while((a = getchar()) != '\n' && a != EOF); /*condition dans le but d'attendre le scanf*/
    Un_truc* truc_sta_dep = chercher_station(arbre, sta_dep);
                                                                   
    char* sta_arr; 
    sta_arr = (char*)malloc(sizeof(char));  
    printf("\n Veuillez entrer votre station d'arrivée :\n");   
    gets(sta_arr); 
    while((a = getchar()) != '\n' && a != EOF) 
    Un_truc* truc_sta_arr = chercher_station(arbre, sta_arr);      

    int chemin_voulu; 
    printf("Veuillez entrer si vous préférez le chemin le plus court (1) ou le plus rapide (0) :\n");                                 
    scanf("%d", &d); 
                                      
    printf("\n Le trajet pour aller de la station %s à la station %s est :\n", sta_dep, sta_arr);
    dijkstra(stations,truc_sta_dep,connexions,chemin_voulu); 
    Un_elem* chemin = cherche_chemin(truc_sta_arr);
    ecrire_chemin(chemin, connexions, chemin_voulu); 
                                      
    // Désallocation de la mémoire : 
    free(limite_no); 
    free(limite_se);                                  
    free(sta_dep); 
    free(sta_arr); 
    detruire_liste_et_truc(connexions);
    detruire_lignes(liste_ligne); 
    detruire_truc(truc_sta_dep);                                  
    detruire_truc(truc_sta_arr); 
    detruire_abr(arbre);                                 
                                      
   return 0;
    
}
