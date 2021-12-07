#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define NB_MAX 50   // Le nombre de Sorciers dont on dispose 
#define k 5    // Nombre de clusters de notre projet

/*
  Structure Sorcier : structure principale de notre projet, qui représente chaque sorcier avec ses 6 champs :
    - Son nom;
    - Son niveau de courage;
    - Son niveau de loyauté;
    - Son niveau de sagesse;
    - Son niveau de malice;
    - Le cluster auquel il va appartenir.
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

/*
    liste_sorciers[NB_MAX] : tableau qui va regrouper tous nos sorciers.
*/
Sorcier liste_sorciers[NB_MAX];


/*
    Fonction nombres_alea : va génerer aléatoirement des entiers qui serviront d'indices pour nos points représentatifs.
    Retourne un tableau de nos k nombres aléatoires.
*/
int *nombres_alea(int k_clust){
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

/*
    Fonction points_representatifs : va retourner les sorciers qui serviront de points représentatifs,
        à partir des indices générés aléatoirement dans la fonction nombres_alea. 
*/
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

/*
    Fonction manhattan_distance : calcule la distance de Manhattan entre deux points (sorciers).
    Retourne un entier.
*/
int manhattan_distance(Sorcier s1, Sorcier s2){
    
    return abs(s1.c - s2.c)+ abs(s1.l - s2.l)+ abs(s1.s - s2.s)+ abs(s1.m - s2.m);
}

/*
    Fonction affect_cluster : trouve le cluster auquel appartient un point(sorcier), à partir de la distance de Manhattan 
            (point représentatif le plus proche de ce sorcier en terme de distance).
    Retourne un entier.
*/
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

/*
    Fonction clustering : affecte l'ensemble de nos points(sorciers) à leur cluster correspondant.
*/

void clustering(Sorcier *centres , Sorcier *points)
{

    for(int i=0; i<NB_MAX; i++)
    {
       
        points[i].cluster = affect_cluster(centres, points[i]);
        printf("Le point %s appartient au cluster n°%d\n ", points[i].nom, points[i].cluster);
   
    }
}

/*
    Fonction somme_partition : calcule le coût de partitionnement pour chaque cluster.
    Retourne un tableau avec les sommes de chacuns de nos k clusters.
*/
int *somme_partition(Sorcier *centres , Sorcier *points)
{
    int sum = 0;
    int cmpt = 0;
    int *somme;
    somme = malloc(k*sizeof(int));

    for(int i=0; i<k; i++){
        for(int j=0; j<NB_MAX; j++){
            if(points[j].cluster == i){
                sum += manhattan_distance(centres[i], points[j]);
                somme[i] = sum;
                cmpt += 1;
            }
        }
        printf("La somme du cluster n°%d est égale à %d\n Et le nombre de sommets pour ce cluster est %d\n ", i, somme[i], cmpt);
        cmpt = 0;
    }

    return somme;
}

/*
    Fonction final_sum : Retourne la somme totale de tout le partitionnement. 
*/

int final_sum(int *somme){
    int final_sum = 0;
    for(int i=0; i<k; i++)
    {
        final_sum += somme[i];
    }
            printf("Le coût de ce partitionnement est %d\n", final_sum);
    return final_sum;

}

/*
    Fonction echange : échange un point non représentatif avec le point représentatif du cluster auquel il appartient.
    Retourne le nouveau tableau de points représentatifs. 
*/
Sorcier* echange(Sorcier *bary, Sorcier s1){
   
    Sorcier *bary_copie;
    bary_copie = malloc(k*sizeof(Sorcier));

    for(int i=0; i<k; i++){
        if(s1.cluster == i){
            bary_copie[i] = s1;
            printf("Le centre %d dans bary est %s\n", i, bary[i].nom);
            printf("Le centre %d dans bary_copie est %s\n", i, bary_copie[i].nom);
        }
        else{
            bary_copie[i] = bary[i];
        }
        printf("Pour le cluster %d, on remplace le centre %s par le point %s\n", i, bary[i].nom, bary_copie[i].nom);

    }
    return bary_copie;
}

/*
    Fonction partitionnement_final : retourne les points représentatifs les plus optimaux pour avoir
                         le meilleur partitionnement (clustering) en fonction de la distance.
*/
Sorcier *partitionnement_final(Sorcier *bary, Sorcier *liste){

    int *actual = somme_partition(bary,liste);
    int cout_actuel = final_sum(actual);

    Sorcier *nv_barycentres;
    nv_barycentres = malloc(k*sizeof(Sorcier));

    for(int i=0; i<k; i++){
        for(int j=0; j<NB_MAX; j++){
            if(liste[j].cluster == i){
                nv_barycentres = echange(bary,liste[j]);
                clustering(nv_barycentres,liste);

                int *new = somme_partition(nv_barycentres,liste);
                int cout_nouveau = final_sum(new);

                if(cout_nouveau < cout_actuel){ //Meilleur cas (amélioration)
                    bary[i] = nv_barycentres[i];
                    cout_actuel = cout_nouveau;
                }
                else { // Pas d'amélioration
                    continue;
                } 

            }
        }
    }

    return bary;
} 


int main () {
   FILE *fp;
    int i;
    Sorcier *bary;
    Sorcier *bary2;

    // Ouverture de mon fichier .txt
   fp = fopen("choixpeauMagiqueeee.txt","r");
   
   // Condition d'erreur 
   if (fp ==  NULL)
   {
       printf("ERROR ! Can't open the file\n");
       exit(-1);
   }

    // J'affiche toute ma liste de sorciers, avec tous leurs attributs
   for(i=0; i<NB_MAX; i++){
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

    // Je calcule mes indices aléatoirement ...
    int *alea2;
	alea2 = nombres_alea(k);
	
	for (int i=0; i<k; i++)
		{
			printf(" Le tableau d'entiers est \n %d\n", alea2[i]);

		}
    // ... que j'utilise ici pour calculer mes premiers points représentatifs
    bary = points_representatifs(liste_sorciers, alea2);

    // Je fais mon clustering initial, et j'affiche tous mes sorciers avec leurs clusters
    clustering(bary, liste_sorciers);
    for(i=0; i<NB_MAX; i++){
        printf("%s %d %d %d %d %d \n", 
            liste_sorciers[i].nom,
            liste_sorciers[i].c,
            liste_sorciers[i].l, 
            liste_sorciers[i].s, 
            liste_sorciers[i].m,
            liste_sorciers[i].cluster);
    }
    
    // Je calcule le cout de ce partitionnement et je l'affiche
    int* sum = somme_partition(bary,liste_sorciers);
    int somme_finale = final_sum(sum);
    printf("Le coût du partirtionnement initial est égal à %d\n", somme_finale);

    // J'appelle ma fonction partitionnement_final, pour ainsi appliquer le clustering sur chacun de mes points non représentatifs,
    //  et qu'elle me renvoie le tableau de points représentatifs optimal (le meilleur clustering). 
    bary2 = partitionnement_final(bary,liste_sorciers);
    for(i=0; i<k; i++){
        printf("\nLe centre optimal pour le cluster %d est le sorcier %s\n", i, bary[i].nom);
    } 

    // Je refais justement ce clustering pour pouvoir l'afficher correctement.
    clustering(bary2, liste_sorciers);
    for(i=0; i<NB_MAX; i++){
        printf("%s %d %d %d %d %d \n", 
            liste_sorciers[i].nom,
            liste_sorciers[i].c,
            liste_sorciers[i].l, 
            liste_sorciers[i].s, 
            liste_sorciers[i].m,
            liste_sorciers[i].cluster);
    } 
    // L'algorithme PAM a ainsi été réalisé.


    // Je ferme mon fichier et je libère toute la mémoire utilisée au cours de mon éxecution.
    fclose(fp);
	free(alea2);
    free(bary);
    free(sum);

   return(0);
}

