#include "malib.h"


int main()
{
  int** dist,**temps;
  int cpt,cpt2,temp;
  FILE*  fp;
  int dep,arr;

  
  //2 tableau a double entrée qui contiennent la distance et le tps entre 2 villes
  dist=(int**)calloc(nb_ville,sizeof(int*));
  temps=(int**)calloc(nb_ville,sizeof(int*));
  for(cpt=0;cpt<nb_ville;cpt++)
  {
    dist[cpt]=(int*)calloc(nb_ville,sizeof(int));
    temps[cpt]=(int*)calloc(nb_ville,sizeof(int));
  }
  
  
  
 //on rempli ces tableau grace au fichier villes.txt
 fp=fopen("villes.txt","r");
 for(cpt=0;cpt<nb_ville;cpt++)
 {
    for(cpt2=0;cpt2<nb_ville;cpt2++)
    {
        fscanf(fp,"%d,%d;",&dist[cpt][cpt2],&temps[cpt][cpt2]);
    }
 }
 fclose(fp);
while(1)
{
 system("cls");
 
 printf("Choisissez votre ville de depart:\n");
 printf("\t1-Paris\n");
 printf("\t2-Nice\n");
 printf("\t3-Lyon\n");
 printf("\t4-Toulouse\n");
 printf("\t5-Orleans\n");
 printf("\t6-Cergy\n");
 printf("\t7-Cancun\n");
 printf("\t8-Annecy\n");
 scanf("%d",&dep);
 dep--;
 
 printf("Choisissez votre ville d'arrive:\n");
 printf("\t1-Paris\n");
 printf("\t2-Nice\n");
 printf("\t3-Lyon\n");
 printf("\t4-Toulouse\n");
 printf("\t5-Orleans\n");
 printf("\t6-Cergy\n");
 printf("\t7-Cancun\n");
 printf("\t8-Annecy\n");
 scanf("%d",&arr);
 arr--;
 
 dijkstra(dep,dist,nb_ville,arr,"km");
 dijkstra(dep,temps,nb_ville,arr,"heures");
 
  system("PAUSE");	
}
  return 0;
}

void affiche_ville(int ville)
{
    switch(ville)
    {
        case(0):printf("Paris");
                break;
        case(1):printf("Nice");
                break;
        case(2):printf("Lyon");
                break;
        case(3):printf("Toulouse");
                break;
        case(4):printf("Orleans");
                break;
        case(5):printf("Cergy");
                break;
        case(6):printf("Cancun");
                break;
        case(7):printf("Annecy");
                break;
                
    }
}

//fonction qui affiche les villes parcourues (calculé par Dijkstra)
void affiche_chemin(int dep,int arr,int P[nb_ville])
{
    if(P[arr]!=dep)
    {
        affiche_chemin(dep,P[arr],P);
        affiche_ville(P[arr]);
        printf("->");
    }
    
    
}


int appartient(S_maillon* T, int succ)
{
    int res=0;
    
    while(T->suiv!=NULL)
    {
        if(T->val==succ) res=1;
        T=T->suiv;
    }
    
    return res;
    
}

int cherche_succes( int** succes, int* ville,int nb_ville)
{
    int cpt;
    int nb_succes=0;
    
    for(cpt=0;cpt<nb_ville;cpt++)
    {
        if(ville[cpt]>0&&ville[cpt]<500) 
        {
            (*succes)[nb_succes]=cpt;
            nb_succes++;
        }
        else (*succes)[nb_succes]=-1;
    }
    return nb_succes;
}

//ALGORITHME DE DIJKSTRA
void dijkstra(int dep, int** tab, int nb_ville,int arr, char unite[3])
{
  
  S_maillon *S,*T,*tempT,*tempS;  //S=sommets parcourus  T=sommets à parcourir
  int marque[nb_ville],P[nb_ville];  //P=distance parcourue;
  int cpt, nb_T=0;
  int nb_suc,*successeur;
  
  successeur=(int*)calloc(nb_ville,sizeof(int));
  
  //initiation
  S=(S_maillon*)calloc(1,sizeof(S_maillon));
  S->val=dep;
  
  T=(S_maillon*)calloc(1,sizeof(S_maillon));
  tempT=T;
  for(cpt=0;cpt<nb_ville;cpt++)
  {
    if(cpt!=dep)
    {
        tempT->val=cpt;
        tempT->suiv=(S_maillon*)calloc(1,sizeof(S_maillon));
        tempT=tempT->suiv;
        nb_T++;
        marque[cpt]=1000;
    }
    else marque[cpt]=0;
    P[cpt]=-1;
  }

  nb_suc=cherche_succes(&successeur,tab[dep],nb_ville);
  
   
  for(cpt=0;cpt<nb_suc;cpt++)
  {
    marque[successeur[cpt]]=tab[dep][successeur[cpt]];
    P[successeur[cpt]]=dep;
  }
  
  //P=sommet precedent si marque <1000 -1 sinon
  
  //iteration
  tempS=S;
    
  while(nb_T>0)
  {
    int sommet=-1;
    
    //choisi un sommet dans T dont la marque est min
    tempT=T;
    sommet=tempT->val;
    tempT=tempT->suiv;
    for(cpt=0;cpt<nb_T-1;cpt++)
    {
         if(marque[tempT->val]<marque[sommet]) sommet=tempT->val;
         tempT=tempT->suiv;
    }
    
    //ajoute le sommet dans S
    tempS->suiv=(S_maillon*)calloc(1,sizeof(S_maillon));
    tempS=tempS->suiv;
    tempS->val=sommet;
    
    //retire le sommet de T
    tempT=T;
    if(tempT->val!=sommet)
    {
        while(tempT->suiv->val!=sommet)
        {
            tempT=tempT->suiv;
        }
        tempT->suiv=tempT->suiv->suiv;
    }
    else *tempT=*(tempT->suiv);
    nb_T--;
    
    //cherche les successeurs du sommet
    nb_suc=cherche_succes(&successeur,tab[sommet],nb_ville);
    
    //pour tous les successeurs du sommet
    for(cpt=0;cpt<nb_suc;cpt++)
    {
        //si le successeur appartient à T
        if(appartient(T,successeur[cpt]))
        {
                //si le chemin est + court
                if(marque[successeur[cpt]]>(marque[sommet]+tab[sommet][successeur[cpt]]))
                {
                    //on affecte le nouveau chemin (marque et sommet precedent)
                    marque[successeur[cpt]]=(marque[sommet]+tab[sommet][successeur[cpt]]);
                    P[successeur[cpt]]=sommet;
                }
        }
    }
    
    
  }
  
  printf("le chemin le plus court pour aller de ");
  affiche_ville(dep);
  printf(" a ");
  affiche_ville(arr);
  printf(" est de %d %s\n",marque[arr],unite);
  
  printf("le chemin est ");
  affiche_ville(dep);
  printf("->");
  affiche_chemin(dep,arr,P);
  affiche_ville(arr);
  printf("\n\n");
}


