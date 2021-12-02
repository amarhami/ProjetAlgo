#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define NB_MAX 50
#define k 5

// "Nom";"Courage";"Loyauté";"Sagesse";"Malice";"Maison"

/*
  Structure Sorcier : structure principale de notre projet, qui représente chaque sorcier avec ses 5 champs :
    - Son nom;
    - Son niveau de courage;
    - Son niveau de loyauté;
    - Son niveau de sagesse;
    - Son niveau de malice.
*/
typedef struct Personnage
{
    char nom[15];
    int c;
    int l;
    int s;
    int m;
    int cluster;
}Sorcier;

Sorcier liste_sorciers[NB_MAX];


/*
  Fonction cpteLignes : permet de calculer le nombre de lignes d'un fichier donné en entrée.
*/
int cpteLignes(FILE *fp){
    int nblignes =0;
    int c;
    while((c = fgetc(fp)) != EOF)
    {
         if(c == '\n') nblignes++;
    }

    rewind(fp);
    return (nblignes-1);
}


int * nombres_alea(int k_clust){
	srand(time(NULL));

    int *alea = malloc(k_clust*sizeof(int));

    for (int i=0; i<k_clust; i++){
        alea[i] = rand()%NB_MAX;
        printf("%d\n", alea[i]);
    }

    for(int i=0; i<k_clust; i++){                 
    	for(int j=i+1; j<k_clust; j++){               
    		if(alea[i] == alea[j]){
    			printf("Deux nombres sont égaux ! On refait la regénération.\n");
    			alea[i] = rand()%NB_MAX;
    			printf("New alea[%d] = %d\n",i, alea[i]);
    			i = 0;
    			j = i+1;
    		}
 
    	}
    }

    return alea;
}

Sorcier *points_representatifs(Sorcier* tab1, int *tab)
{
	Sorcier *bary;
	bary = malloc(k*sizeof(Sorcier));

	for (int j=0; j<k; j++)
		{ bary[j]= tab1[tab[j]];
			printf(" Le barycentre num %d est %s \n" ,j, bary[j].nom);
            
		}

		return bary;
}

int manhattan_distance(Sorcier s1, Sorcier s2){
    
    return abs(s1.c - s2.c)+ abs(s1.l - s2.l)+ abs(s1.s - s2.s)+ abs(s1.m - s2.m);
}

int affect_cluster(Sorcier *bary, Sorcier p){
    int cluster= 0;
    int min;
    min= manhattan_distance(bary[0],p); 
    for (int i=0; i<k;i++)
    {
        int res = manhattan_distance(bary[i],p);
        if (res < min)
        {
            min = manhattan_distance(bary[i],p);
            cluster  = i;
        }

    }
    return cluster ;
}


void clustering(Sorcier *centres , Sorcier *points)
{

    for(int i=0; i<NB_MAX; i++)
    {
       
        points[i].cluster = affect_cluster(centres, points[i]);
        printf("Le point %s appartient au cluster n°%d\n ", points[i].nom, points[i].cluster);
   
    }
}

int *somme_partition(Sorcier *centres , Sorcier *points)
{
    int sum;
    int *somme;
    somme = malloc(k*sizeof(int));

    for(int i=0; i<k; i++){
        for(int j=0; j<NB_MAX; j++){
            if(points[j].cluster == i){
                sum += manhattan_distance(centres[i], points[j]);
                somme[i] = sum;
            }
        }
        printf("La somme du cluster n°%d est égale à %d\n", i, somme[i]);
    }

    return somme;
}



int main () {
   FILE *fp;
    int i,n;
    //int k=5;
    Sorcier *bary;
    
    Sorcier s1 = { .nom ="adrien ", .c= 12, .l =13, .s=23, .m=14 };
    Sorcier s2 = { .nom ="adriene ", .c= 16, .l =10, .s=45, .m=12};
  
   fp = fopen("choixpeauMagiqueeee.txt","r");

    n = cpteLignes(fp);
   
   if (fp ==  NULL)
   {
       printf("ERROR ! Can't open the file\n");
       exit(-1);
   }

   for(i=0; i<n; i++){
       fscanf(fp,"%s %d %d %d %d", 
            liste_sorciers[i].nom,
            &liste_sorciers[i].c,
            &liste_sorciers[i].l, 
            &liste_sorciers[i].s, 
            &liste_sorciers[i].m);

        printf("%s %d %d %d %d \n", 
            liste_sorciers[i].nom,
            liste_sorciers[i].c,
            liste_sorciers[i].l, 
            liste_sorciers[i].s, 
            liste_sorciers[i].m);
    }

    
    //printf("%s\n",liste_sorciers[5].nom);
    //printf("%d\n",liste_sorciers[5].c);


   fclose(fp);

    int *alea2;
	alea2 = nombres_alea(5);
	
	for (int i=0; i<5; i++)
		{
			printf(" Le tableau d'entiers est \n %d\n", alea2[i]);

		}

    bary = points_representatifs(liste_sorciers, alea2);

    int res = manhattan_distance(s1,s2);
    printf("La distance de manhattan est %d\n", res); 


   // int clust = affect_cluster(bary,s1);
    //printf("s1 appartient au cluster (%d)\n",  clust);

    clustering(bary, liste_sorciers);
    for(i=0; i<n; i++){
        printf("%s %d %d %d %d %d \n", 
            liste_sorciers[i].nom,
            liste_sorciers[i].c,
            liste_sorciers[i].l, 
            liste_sorciers[i].s, 
            liste_sorciers[i].m,
            liste_sorciers[i].cluster);
    }

    
    int* sum = somme_partition(bary,liste_sorciers);


	free(alea2);
    free(bary);
    free(sum);

   return(0);
}

