#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define NB_MAX 50

// "Nom";"Courage";"Loyauté";"Sagesse";"Malice";"Maison"

typedef struct Personnage
{
    char nom[15];
    int c;
    int l;
    int s;
    int m;
}Sorcier;

Sorcier liste_sorciers[NB_MAX];

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


int * nombres_alea(int k){
	srand(time(NULL));

    int *alea = malloc(k*sizeof(int));

    for (int i=0; i<k; i++){
        alea[i] = rand()%NB_MAX;
        printf("%d\n", alea[i]);
    }

    for(int i=0; i<k; i++){                 
    	for(int j=i+1; j<k; j++){               
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


int manhattan_distance(Sorcier s1, Sorcier s2)
{
return abs(s1.c - s2.c)+ abs(s1.l - s2.l)+ abs(s1.s - s2.s)+ abs(s1.m - s2.m);
}

/*int retourne_sorcier(Sorcier *tab, int k){

    int *T ;
    T = nombres_alea(k);
    for(int i=0; i<k; i++){

    }

    return 0;

}*/

int main () {
   FILE *fp;
    int i,n;
    int k=5;
    Sorcier bary[k];
    
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

for (int j=0; j<5; j++)
		{ bary[j]= liste_sorciers[alea2[j]];
			printf(" Le barycentre num %d est %s \n" ,j, bary[j].nom);
            
		}


        int res = manhattan_distance(s1,s2);
        printf("La distance de manhattan est %d\n", res); 
	free(alea2);

   return(0);
}

