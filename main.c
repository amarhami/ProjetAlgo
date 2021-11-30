#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define NB_MAX 50

// "Nom";"Courage";"Loyauté";"Sagesse";"Malice";"Maison"

typedef struct Sorcier
{
    char nom[15];
    int c;
    int l;
    int s;
    int m;
}Point;

Point liste_sorciers[NB_MAX];

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


int alea_centre2(int k){
    srand(time(NULL));

    int alea[k];

    for (int i=0; i<k; i++){
        alea[i] = rand()%NB_MAX;
        printf("%d\n", alea[i]);
    }
    
    while() 
        if(alea[i] == alea[i+1] || alea[i] == alea[] )    
}

int alea_centre(int k){
   srand(time(NULL));
   int i =0;
   int alea[k];
   int s ;
     alea[i] = rand()%(NB_MAX);
    for ( i=1; i<k ;i++)
    {
          alea[i] = rand()%(NB_MAX);
        
         for (s=0;s=i-1;i++)
         {if (alea[i]== alea[s])
         {
              alea[i] = rand()%(NB_MAX);
              //alea_centre(k);
         }
    
         }
          printf("%d\n", alea[i]);
    }

  return 0;

 }

   


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

    
    printf("%s\n",liste_sorciers[5].nom);
    printf("%d\n",liste_sorciers[5].c);


   fclose(fp);

    int alea2 = alea_centre2(5);
   
   return(0);
}

