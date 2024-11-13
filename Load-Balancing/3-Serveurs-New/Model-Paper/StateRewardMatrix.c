#include <stdio.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#include "const.h"
static int Min[NEt], Max[NEt];
#include "funRewardMit.c"


void  usage1()
{
	printf("Usage : ./StateReward gamma Alpha Eb \n");
	exit(1);
}

void Init_tab(double *tab,int taille)
{
	for(int i=0; i<taille; i=i+1){	
		tab[i] = 0;
	}
}

int Min_tab(double *tab,int taille)
{
	double min = tab[0];
	int indice_min = 0;
	
	for(int i=0; i<taille; i=i+1){	
		if( tab[i]<min )
		{
		   min = tab[i];
		   indice_min = i;
	    }
	}
	return indice_min;
}

int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
int a, b, c, d, e, f;
int taille = BufferSize+1;
int MAT[taille][taille][taille];
double *tab = (double*) calloc (6,sizeof(double));

if (argc!=4) 
   usage1();
   
++argv;
double gamma = atof(*argv)/10; // gamma = gamma12 = gamma21
++argv;
int Alpha= atoi(*argv);
++argv;
double Em = atof(*argv);

FILE *f1=fopen("StateReward.matrix","w");

int i,j,k;

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
				MAT[i][j][k] = 0;
			}
	}
}

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
		
			a = b = c = d = e = f = 0;
			Init_tab(tab,6);

			if( Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Em*gamma <0 )
			{
				tab[0] = Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Em*gamma;
			    a = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*k - 2*i + 2) + Em*gamma <0  )
			{ 
				 tab[1] = Alpha*CPU*CPU *(double)(2*k - 2*i + 2) + Em*gamma;
				 b = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Em*gamma <0 )
			{
				tab[2] = Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Em*gamma;
				c = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*k - 2*j + 2) + Em*gamma <0  )
			{ 
				 tab[3] = Alpha*CPU*CPU *(double)(2*k - 2*j + 2) + Em*gamma;
				 d = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*i - 2*k + 2) + Em*gamma <0 )
			{
				 tab[4] = Alpha*CPU*CPU *(double)(2*i - 2*k + 2) + Em*gamma;
				 e = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*j - 2*k + 2) + Em*gamma <0  )
			{ 
				 tab[5] = Alpha*CPU*CPU *(double)(2*j - 2*k + 2) + Em*gamma;
				 f = 1;
			}

			MAT[i][j][k] = Min_tab(tab,6) + 1;
			
			if( a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0)
			{
					MAT[i][j][k] = -1;
			}	
			if( a == 1 && b == 1 && c == 1 && d == 1 && e == 1 && f == 1)
			{
					printf("Hmmm Etat (%d,%d,%d) PROBLEME ! \n",i,j,k);
			}
			//printf("(%d,%d,%d) = [%f,%f,%f,%f,%f,%f] \n",i,j,k,tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
				
			
	   }
		
	}
	
}

fprintf(f1,"%5d \n",taille);
for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
		
			fprintf(f1,"%5d %5d %5d %5d \n",i,j,k,MAT[i][j][k]);
		}
	}
}

printf("State Rewards Matrice Done ! \n");
fclose(f1);
exit(0);


}
