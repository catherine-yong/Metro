//prototype des fonctions
#ifndef OK 
#define OK 1

#include <stdio.h>

#include "truc.h"
#include "coord.h"
#include "arbr_type.h"
#include "connexion.h"
#include "ligne.h"
#include "liste.h"
#include "station.h"
#include "aqrtopo.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);
Un_elem *inserer_liste_trie(Un_elem *head, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *head);
void detruire_liste(Un_elem *head);
void detruire_liste_et_truc(Un_elem *head);
Un_elem *lire_stations(char *nom_fichier);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);
Un_nabr *creer_nabr(Un_truc *truc);
Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *node);
Un_nabr *construire_abr(Un_elem *liste_sta);
void detruire_abr(Un_nabr *abr);
void detruire_branches(Un_nabr *abr, Un_nabr *node);
void detruire_noeud(Un_nabr *node);
Un_truc *chercher_station(Un_nabr *abr, char *nom);
Un_elem *inserer_deb_liste(Un_elem *head, Un_truc *truc);
void limites_zone(Un_elem *head, Une_coord *limite_no, Une_coord *limite_se);
Un_noeud *create_node_aqr(Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *construire_aqr(Un_elem *head);
void detruire_aqr(Un_noeud *abr);
void detruire_branches_aqr(Un_noeud *abr, Un_noeud *branch);
void detruire_noeud_aqr(Un_noeud *node);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord);
Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);

void afficher_lignes(Une_ligne *head);
void detruire_lignes(Une_ligne* head);
Une_ligne *lire_ligne(char *nom_fichier);

void affiche_abr(Un_nabr *abr);


#endif



