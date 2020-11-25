#include "abr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

Un_elem *lire_stations(char *nom_fichier)
{
    FILE *fichier;
    char *line = NULL;
    char *ptr_ligne;
    const char *separator = ";";
    size_t size = 0;
    
    Un_elem *head = NULL;
    head = (Un_elem*) malloc(sizeof(Un_elem));
    Un_elem *phead = head;
    Un_elem *pptemp = head;
    head->truc = NULL;
    head->truc = (Un_truc*) malloc(sizeof(Un_truc));

    /* on ouvre le fichier et on vérifie sa validité */
    fichier = fopen(nom_fichier,"r");

    if(!fichier)
    {
        printf("impossible d'ouvir le fichier\n");
        return NULL;
    }

    /* on verifie l'allocation mémoire pour head et son truc */
    if(!head)
    {
        printf("probleme allocation memoire\n");
        fclose(fichier);
        return NULL;
    }

    if(!head->truc)
    {
        fclose(fichier);
        return NULL;
    }

    // initialisation des valeurs à nul
    head -> truc -> type = 0;
    head -> truc -> user_val = 0.0;
    ((head -> truc -> data).sta).nb_con = 0;
    ((head -> truc -> data).sta).tab_con = NULL;
    ((head -> truc -> data).sta).nom = NULL;
    ((head -> truc -> data).sta).con_pcc = NULL;

    // on parcourt le fichier et on insère dans la liste les éléments que l'on trouve
    while (getline(&line, &size, fichier) != -1){

        pptemp = head;

        ptr_ligne = NULL;
        ptr_ligne = strtok(line,separator);

        /* nom de la station : on initialise le nom à null puis on copie la cellule du fichier csv dans notre liste */
        ((head->truc->data).sta).nom = NULL;
        ((head->truc->data).sta).nom = (char*) malloc((strlen(ptr_ligne) + 1)*sizeof(char));
        if(((head->truc->data).sta).nom == NULL)
        {
            fclose(fichier);
            return NULL;
        }

        strcpy(((head -> truc -> data).sta).nom , ptr_ligne);

        ptr_ligne = strtok(NULL , separator);
        
        /* latitude : on convertit ptr_ligne en float pour ensuite l'insérer dans la liste */
        (head -> truc -> coord).lat = (float) atof(ptr_ligne);

        ptr_ligne = strtok(NULL , separator);

        /* longitude : idem */
        (head -> truc -> coord).lon = (float) atof(ptr_ligne);

        /* on passe au suivant en faisant attention à bien allouer la mémoire pour tous les champs */
        head -> suiv = NULL;
        head -> suiv = (Un_elem*) malloc(sizeof(Un_elem));
        if(!head->suiv)
        {
            fclose(fichier);
            return NULL;
        }

        head -> suiv -> truc = NULL;
        head -> suiv -> truc = (Un_truc*) malloc(sizeof(Un_truc));
        if(head -> suiv -> truc == NULL)
        {
            fclose(fichier);
            return NULL;
        }

        /*affichage 
        printf("\n nom de la station : %s\n",((head->truc->data).sta).nom);
        printf("longitude : %f\n",(head->truc->coord).lon);
        printf("latitude : %F\n", (head->truc->coord).lat)
        */

        // on passe au suivant et on met à jour ses champs comme si c'était le premier élément
        head = head -> suiv;
        head -> truc -> type = 0;
        head -> truc -> user_val = 0.0;
        ((head -> truc -> data).sta).nb_con = 0;
        ((head -> truc -> data).sta).tab_con = NULL;
        ((head -> truc -> data).sta).nom = NULL;
        ((head -> truc -> data).sta).con_pcc = NULL;
        
    }

    phead->suiv = NULL;
    fclose(fichier);
    return phead;
}

Un_elem *inserer_liste_trie(Un_elem *head, Un_truc *truc)
{
    /* on veut inserer le truc dans la liste de maniere croissante*/

    // si truc est vide on ne fait rien 
    if(!truc)
    {
        printf("rien à insérer\n");
        return head;
    }

    // si la tete est vide alors on la met a jour
    if(!head)
    {
        head = (Un_elem *) malloc(sizeof(Un_elem));
        if(!head)
        {
            printf("\nprobleme allocation memoire\n");
            return NULL;
        }
        head->truc = truc;
        head->suiv = NULL;
        return head;
    }

    Un_elem *current = head; // pointeur qui parcourt la liste

    Un_elem *nouv_element = NULL;
    nouv_element = (Un_elem *) malloc(sizeof(Un_elem));
    if(!nouv_element)
    {
        printf("probleme allocation\n");
        return NULL;
    }
    nouv_element->truc = NULL;
    nouv_element->truc = (Un_truc *) malloc(sizeof(Un_truc));
    if(!nouv_element->truc)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }
    nouv_element->truc = truc;
    nouv_element->suiv = NULL;
    
    /* si l'element a inserer a un user_val plus grand que la tete de liste, on ajoute au debut*/

    if(truc->user_val > head->truc->user_val)
    {
        nouv_element->suiv = head;
        head = nouv_element;
    }
    
    /* si l'element a inserer est au milieu de la liste ou a la fin, alors on parcourt jusqu'au bon rand de user_valur 
    c'est a dire une fois que user_value de l'element est plus petit que user_valeur du pointeur sur la liste, ou quand on est a la fin de la liste */

    nouv_element->suiv = (Un_elem *) malloc(sizeof(Un_elem));
    if(!nouv_element->suiv)
    {
        return NULL;
    }

    
    while (current->suiv != NULL && current->suiv->truc->user_val <= truc->user_val)
    {
        current = current->suiv;
    } 
    nouv_element->suiv = current->suiv;
    current->suiv = nouv_element;
    
    return head;
}

void ecrire_liste(FILE *flux, Un_elem *head)
{
    /* on veut afficher les trucs correspondants a des stations */
    
    while (head->suiv != NULL) {
        if (head->truc->type == 0) {
            printf("%s\n", head->truc->data.sta.nom);
        }
        head = head->suiv;
    }
}

void detruire_liste(Un_elem *head)
{
    /* on veut detruire une liste chainee de trucs */
    Un_elem *temp;
    Un_elem *ptr = head;
    while(ptr)
    {
        temp = ptr->suiv;
        free(ptr);
        ptr = temp;
    }
}

void detruire_liste_et_truc(Un_elem *head)
{
    /* pour chaque maillon de la liste, on detruit son contenu */
    /* on prend un element temporaire qui stocke la case d'apres pour ensuite detruire le contenu de la case courante */
    Un_elem *temp;
    while(head)
    {
        temp = head->suiv;
        detruire_truc(head->truc);
        free(head);
        head = temp;
    }
}

Un_elem *inserer_deb_liste(Un_elem *head, Un_truc *truc)
{
    /* si truc passé en paramètre est NULL, alors on sort de la fonction */

    if(!truc)
    {
        return head;
    }

    /* on crée un nouvel élément que l'on insèrera en début de liste */
    /* on alloue la mémoire nécessaire pour l'élément et son champ truc */

    Un_elem *new_head = NULL;
    new_head = (Un_elem *) malloc(sizeof(Un_elem));

    if(!new_head)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }
    
    new_head->truc = NULL;
    new_head->truc = (Un_truc *) malloc(sizeof(Un_truc));

    if(!new_head->truc)
    {
        printf("probleme allocation mémoire\n");
        return NULL;
    }

    /* ici, truc passé en paramètre n'est pas NULL, donc on ajoute truc à new_head et on fait pointer new_head sur la liste head */
    
    new_head->truc = truc;
    new_head->suiv = head;

    return new_head;
}   


void limites_zone(Un_elem *head, Une_coord *limite_no, Une_coord *limite_se)
{
    Un_elem *phead = head->suiv;

    /* on intialise les valeurs des 2 coordonnées aux valeurs maximales de leur type */

    float longitude_min = ((head->truc)->coord).lon;
    float longitude_max = ((head->truc)->coord).lon;
    float latitude_min = ((head->truc)->coord).lat;
    float latitude_max = ((head->truc)->coord).lat;

    /*tant que le pointeur sur liste n'est pas null, on compare avec les composantes des 2 coordonnées */
    /* si on trouve un élément plus petit (resp. grand) que le minimum définit (resp. maximum) alors on procède à un échange */
    
    while(phead)
    {   
        /* on compare avec la longitude minimale */
        if(phead->truc->coord.lon < longitude_min)
        {
            longitude_min = phead->truc->coord.lon;
        }

        /* on compare avec la longitude maximale */
        if(phead->truc->coord.lon > longitude_max)
        {
            longitude_max = phead->truc->coord.lon;
        }

        /* on compare avec la latitude minimale */
        if(phead->truc->coord.lon < latitude_min)
        {
            latitude_min = phead->truc->coord.lat;
        }

        /* on compare avec la latitude maximale */
        if(phead->truc->coord.lon > latitude_max)
        {
            latitude_max = phead->truc->coord.lat;
        }

        /* on avance dans la liste */
        phead = phead->suiv;

    }

    /*on a fini de parcourir la liste, on change donc les coordonnées de limite_no et limite_se comme selon l'énoncé*/
    
    if(!limite_se) // if limite_se == NULL
    {
        limite_se = (Une_coord *) malloc(sizeof(Une_coord));
    }

    if(!limite_no) // if limite_no == NULL
    {
        limite_no = (Une_coord *) malloc(sizeof(Une_coord));
    }

    if((!limite_se) || (!limite_no))
    {
        exit(1);
    }

    limite_se->lon = longitude_max;
    limite_se->lat = latitude_min;

    limite_no->lon = longitude_min;
    limite_se->lat = latitude_max;

}

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta)
{

    FILE* fichier;      
    char *csv = "../connexions.csv";  
    char *ptr_chaine ; 
    int num_ligne = 1; 

    // Initialisation des données que l'on veut récupérer à chaque ligne

    char *code_ligne; 
    char *nom_station_dep; 
    char *nom_station_arr; 
    float intervalle;        

    //Ouverture du fichier de données csv
    fichier = fopen( csv, "r") ; // Ouverture du fichier en lecture seule
    if (fichier ==NULL)
    {
            printf("\nERREUR : Ouverture du fichier impossible\n");
            return NULL;
    }

    char* ptr_ligne = NULL;
    size_t size = 0;    
    char* line = NULL;

    Une_ligne *head_con = NULL;
    Un_elem* phead = head_con;
    Un_elem* pphead = head_con;

    // Lecture du fichier de données csv
    while(getline(&ptr_ligne, &size, fichier) >= 0) // Lecture des lignes l'un après l'autre jusqu'à la fin du fichier
    {
        pphead = head_con ;
        num_ligne++ ;
        
        // ligne de metro
        ptr_chaine = strtok (ptr_ligne, ";"); 
        code_ligne = (char *)malloc((strlen(ptr_chaine)+1)*sizeof(char));

        if(!code_ligne)
        {
            printf("probleme allocation mémoire\n");
            fclose(csv);
        }

        strcpy(code_ligne , ptr_chaine);

        // station de depart 
        ptr_chaine = strtok (NULL, ";");
        nom_station_dep = (char *)malloc((strlen(ptr_chaine)+1)*sizeof(char));

        if(!nom_station_dep)
        {
            printf("probleme allocation mémoire\n");
            fclose(csv);
        }

        strcpy(nom_station_dep , ptr_chaine);

        // station d'arrivee        
        ptr_chaine = strtok (NULL, ";");
        nom_station_arr = (char *)malloc((strlen(ptr_chaine)+1)*sizeof(char));
        if(!nom_station_arr)
        {
            printf("probleme allocation mémoire\n");
            fclose(csv);
        }

        strcpy(nom_station_arr , ptr_chaine);

        // intervalle de temps entre les deux
        ptr_chaine = strtok (NULL, ";");
        intervalle = (float) atof(ptr_chaine);

        // Création d'un truc aller

        // On récupère les informations en les cherchant soit dans liste_ligne soit dans abr_sta (car on cherche à avoir des pointeurs)
        Une_ligne* ligne = chercher_ligne(liste_ligne,code_ligne);
        Un_truc* station_depart = chercher_station(abr_sta,nom_station_dep);
        Un_truc* station_arrivee = chercher_station(abr_sta,nom_station_arr);

        Un_truc* truc_aller=(Un_truc*)malloc(sizeof(Un_truc));
        if(truc_aller == NULL)
        {
            printf("\nErreur dans l'allocation mémoire\n");
            return NULL;
        }
        truc_aller->data.con.sta_dep = station_depart;
        truc_aller->data.con.sta_arr = station_arrivee;
        truc_aller->data.con.ligne = ligne;
        truc_aller->user_val = intervalle;

        truc_aller->data.con.sta_dep->data.sta.nb_con += 1;
        truc_aller->data.con.sta_dep->data.sta.tab_con = realloc(truc_aller->data.con.sta_dep->data.sta.tab_con, ((truc_aller->data.con.sta_dep->data.sta.nb_con+1)*sizeof(Une_connexion*)));    // Avec realloc, on modifie la taille du tableau des connexions
        truc_aller->data.con.sta_dep->data.sta.tab_con[truc_aller->data.con.sta_dep->data.sta.nb_con] = station_arrivee;

        truc_aller->data.con.sta_arr->data.sta.nb_con += 1;
        truc_aller->data.con.sta_arr->data.sta.tab_con = realloc( truc_aller->data.con.sta_arr->data.sta.tab_con, (( truc_aller->data.con.sta_arr->data.sta.nb_con+1)*sizeof(Une_connexion*)));    // Avec realloc, on modifie la taille du tableau des connexions
        truc_aller->data.con.sta_arr->data.sta.tab_con[ truc_aller->data.con.sta_arr->data.sta.nb_con] = station_depart;
        
        // on ajoute le truc a la liste 

        inserer_liste_trie(head_con,truc_aller);

        // on fait le retour
        Un_truc* truc_retour = (Un_truc*)malloc(sizeof(Un_truc));
        if(truc_retour == NULL)
        {
            printf("\nErreur dans l'allocation mémoire\n");
            return NULL;
        }
        truc_retour->data.con.sta_dep = station_arrivee;
        truc_retour->data.con.sta_arr = station_depart;
        truc_retour->data.con.ligne = ligne;
        truc_retour->user_val = intervalle;

        truc_retour->data.con.sta_dep->data.sta.nb_con += 1;
        truc_retour->data.con.sta_dep->data.sta.tab_con = realloc(truc_retour->data.con.sta_dep->data.sta.tab_con, ((truc_retour->data.con.sta_dep->data.sta.nb_con+1)*sizeof(Une_connexion*)));    // Avec realloc, on modifie la taille du tableau des connexions
        truc_retour->data.con.sta_dep->data.sta.tab_con[truc_retour->data.con.sta_dep->data.sta.nb_con] = station_arrivee;

        truc_retour->data.con.sta_arr->data.sta.nb_con += 1;
        truc_retour->data.con.sta_arr->data.sta.tab_con = realloc( truc_retour->data.con.sta_arr->data.sta.tab_con, (( truc_retour->data.con.sta_arr->data.sta.nb_con+1)*sizeof(Une_connexion*)));    // Avec realloc, on modifie la taille du tableau des connexions
        truc_retour->data.con.sta_arr->data.sta.tab_con[ truc_retour->data.con.sta_arr->data.sta.nb_con] = station_depart;

        // on ajoute le truc a la liste 

        inserer_liste_trie(head_con,truc_retour);
        

    }
    pphead->suiv = NULL;
    fclose(fichier);
    return phead;
}
