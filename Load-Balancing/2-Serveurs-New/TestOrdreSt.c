#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#define BufferSize 20
#define EPSILON 1e-20

void Test_Ordre_ST_1(int n, long double *PILB,long double *PISLB)
{
	
int i;
long double s1, s2;
s1 = s2 = 0;

for(i=0;i<n;i++)
 {
	 s1 += PILB[i];
	 s2 += PISLB[i];
	 
	 //printf("Normal : S2 - S1 = %.20Le \n",s2 - s1);
	 if(s2 < s1 && fabs(s2 - s1) > EPSILON  && i<n-1) // projSLB < projLB
	 {
		 printf("Dommage pas d'ordre ST :(, Voir indice %d car  PISLB < PILB et %.20Le < %.20Le et diff = %.20Le\n",i,s2,s1,s2-s1);
		 return;
	 }
 }
 
 printf("Test Ordre1 sommes : %Le et %Le \n",s1,s2);
 printf(" ==> Ordre1 ST, element par element = OK !, PI(LB) < PI(SLB) \n");	
}

void Test_Ordre_ST_2(int n, int *X1LB, int *X2LB, long double *PILB,long double *PISLB)
{

int i;
long double s1, s2;
s1 = s2 = 0;
int nproj = BufferSize+1;
long double *projLB = calloc(nproj,sizeof(long double));
long double *projSLB = calloc(nproj,sizeof(long double));

for(i=0;i<n;i++)
 {
  projLB[(int)fabs(X1LB[i]-X2LB[i])]+= PILB[i];
  projSLB[(int)fabs(X1LB[i]-X2LB[i])]+= PISLB[i];
 }
 

for(i=nproj-1;i>=0;i--)
 {
	 s1 += projLB[i];
	 s2 += projSLB[i];
	 
	 //printf("Projection : S2 - S1 = %.20Le \n",s2 - s1);
	 if(s2 < s1 && fabs(s2 - s1) > EPSILON && i>0) // projSLB < projLB
	 {
		 printf("Dommage pas d'ordre ST avec projection :(, Voir indice %d car  ProjSLB < ProjLB et %.20Le < %.20Le et diff = %.20Le\n",i,s2,s1,s2-s1);
		 return;
	 }
 }
 
 printf("Test Ordre2 sommes : %Le et %Le \n",s1,s2);
 printf(" ==> Ordre2 ST, avec projection = OK !, Proj_PI(LB) < Proj_PI(SLB) \n");	
}

int main(int argc, char *argv[])
{
  
 
 FILE *FLBpi, *FLBcd, *FLBsz, *FSLBpi, *FSLBcd, *FSLBsz;
 char szLB[100], cdLB[100], szSLB[100], cdSLB[100], piLB[100], piSLB[100];

 int *ILB, *ISLB, *X1LB, *X2LB , *X1SLB, *X2SLB;
 long double *PILB, *PISLB;
 long double proba;

 int i,n,n1,n2,n3,n4,n5,n6; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 3)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./TestOrder Model1(LB)  Model2(SLB) \n");
 	exit(1);
 }
	 
	 
	 
	 strcpy(szLB,argv[1]); 
	 strcpy(cdLB,argv[1]);
	 strcpy(piLB,argv[1]); 
	 
	 
	 strcpy(szSLB,argv[2]); 
	 strcpy(cdSLB,argv[2]);
	 strcpy(piSLB,argv[2]); 
	 
	
  	 strcat(szLB,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cdLB,".cd");
  	 strcat(piLB,".pi");
  	 
  	 strcat(szSLB,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cdSLB,".cd");
  	 strcat(piSLB,".pi");
  	 
   

 FLBsz = fopen(szLB,"r");
 if(FLBsz == NULL)
 {printf("Fichier %s n'existe pas ! \n", szLB); exit(2);}


 FSLBsz = fopen(szSLB,"r");
 if(FSLBsz == NULL)
 {printf("Fichier %s n'existe pas ! \n", szSLB); exit(2);}
 
 FLBcd = fopen(cdLB,"r");
 if(FLBcd == NULL)
 {printf("Fichier %s n'existe pas ! \n", cdLB); exit(2);}
 
 FSLBcd = fopen(cdSLB,"r");
 if(FSLBcd == NULL)
 {printf("Fichier %s n'existe pas ! \n", cdSLB); exit(2);}
 
 
 FLBpi = fopen(piLB,"r");
 if(FLBpi == NULL)
 {printf("Fichier %s n'existe pas ! \n", piLB); exit(2);}
 
 
 FSLBpi = fopen(piSLB,"r");
 if(FSLBpi == NULL)
 {printf("Fichier %s n'existe pas ! \n", piSLB); exit(2);}



/*-------------------- Lecture du fichier ".sz" et ecriture dans ".reorder.sz" --------------*/

 fscanf(FLBsz,"%d %d %d",&n1,&n2,&n3);
 fscanf(FSLBsz,"%d %d %d",&n4,&n5,&n6);
 
 if( n2 != n5 || n2 <= 0 )
 {
	 printf("Attention les tailles sont différentes, ou bien nulle !!. \nVoir vos fichiers '.sz'\n");
	 exit(2);
 }
 if( n1 <= n4)
 {
	 printf("Assurez vous qu'il y'a bien du Load Balancing, car les deux modèles ne doivent pas avoir le même nombre d'arcs n1 = %d et n4 = %d \n",n1,n4);
	 exit(2);
 }
 n = n2;
 printf("\n---------------Comparaison Ordre ST , n = %d ------------------ \n",n);

fclose(FLBsz);
fclose(FSLBsz);
 
 
/*-------------------- Lecture des fichier ".cd" -----------------*/

ILB = calloc(n,sizeof(int));
X1LB = calloc(n,sizeof(int));
X2LB = calloc(n,sizeof(int));

ISLB = calloc(n,sizeof(int));
X1SLB = calloc(n,sizeof(int));
X2SLB = calloc(n,sizeof(int));


for(i=0;i<n;i++)
 {
	fscanf(FLBcd,"%d %d %d",&ILB[i],&X1LB[i],&X2LB[i]);
	fscanf(FSLBcd,"%d %d %d",&ISLB[i],&X1SLB[i],&X2SLB[i]);
 }
 
 
fclose(FLBcd);
fclose(FSLBcd);
 

/*-------------------- Lecture des fichier ".pi" -----------------*/

PILB = calloc(n,sizeof(long double));
PISLB = calloc(n,sizeof(long double));

for(i=0;i<n;i++)
 {
	fscanf(FLBpi,"%Lf",&PILB[i]);
	fscanf(FSLBpi,"%Lf",&PISLB[i]);
 }


fclose(FLBpi);
fclose(FSLBpi);


/*-------------------- Comparaison au sens ST --------------------*/


Test_Ordre_ST_1(n, PILB, PISLB);
Test_Ordre_ST_2(n, X1LB, X2LB, PILB, PISLB);

 
	
  return 0;
}
