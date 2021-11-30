#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// "Nom";"Courage";"Loyauté";"Sagesse";"Malice";"Maison"

typedef struct Sorcier
{
    char nom[15];
    int c;
    int l;
    int s;
    int m;
}Point;

Point liste_sorciers[50];

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

    /*
    while(!feof(fp))
    {
        c = fgetc(fp);
         if(feof(fp)){
            break;
        }
        printf("%c", c);
    }*/

   fclose(fp);
   
   return(0);
}

