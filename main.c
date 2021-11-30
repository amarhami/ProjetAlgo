#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

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


int nombres_alea(int k){
	srand(time(NULL));

    int alea[k];

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

    return 0;
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

    int alea2 = nombres_alea(5);
   
   return(0);
}

