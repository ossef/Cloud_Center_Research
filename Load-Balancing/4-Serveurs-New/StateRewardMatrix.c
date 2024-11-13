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
int a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11;
int taille = BufferSize+1;
int MAT[taille][taille][taille][taille];
double *tab = (double*) calloc (12,sizeof(double));

if (argc!=4) 
   usage1();
   
++argv;
double gamma = atof(*argv)/10; // gamma = gamma12 = gamma21
++argv;
int Alpha= atoi(*argv);
++argv;
double Em = atof(*argv);

FILE *f1=fopen("StateReward.matrix","w");

int i,j,k,t;

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
			
			for(t=0; t<taille; t=t+1){
				
				MAT[i][j][k][t] = 0;
			}
		}
	}
}

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
			
			for(t=0; t<taille; t=t+1){
		
				a0 = a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = a10 = a11 = 0;
				Init_tab(tab,12);
				
	/*------------------ Serveur1 fait du LB --------------------------------------------*/

				if( Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Em*gamma <0 )
				{
					tab[0] = Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Em*gamma;
					a0 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*k - 2*i + 2) + Em*gamma <0  )
				{ 
					 tab[1] = Alpha*CPU*CPU *(double)(2*k - 2*i + 2) + Em*gamma;
					 a1 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*t - 2*i + 2) + Em*gamma <0  )
				{ 
					 tab[2] = Alpha*CPU*CPU *(double)(2*t - 2*i + 2) + Em*gamma;
					 a2 = 1;
				}

	/*------------------ Serveur2 fait du LB --------------------------------------------*/
				
				if( Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Em*gamma <0 )
				{
					tab[3] = Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Em*gamma;
					a3 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*k - 2*j + 2) + Em*gamma <0  )
				{ 
					 tab[4] = Alpha*CPU*CPU *(double)(2*k - 2*j + 2) + Em*gamma;
					 a4 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*t - 2*j + 2) + Em*gamma <0  )
				{ 
					 tab[5] = Alpha*CPU*CPU *(double)(2*t - 2*j + 2) + Em*gamma;
					 a5 = 1;
				}

	/*------------------ Serveur3 fait du LB --------------------------------------------*/			
				
				if( Alpha*CPU*CPU *(double)(2*i - 2*k + 2) + Em*gamma <0 )
				{
					 tab[6] = Alpha*CPU*CPU *(double)(2*i - 2*k + 2) + Em*gamma;
					 a6 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*j - 2*k + 2) + Em*gamma <0  )
				{ 
					 tab[7] = Alpha*CPU*CPU *(double)(2*j - 2*k + 2) + Em*gamma;
					 a7 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*t - 2*k + 2) + Em*gamma <0  )
				{ 
					 tab[8] = Alpha*CPU*CPU *(double)(2*t - 2*k + 2) + Em*gamma;
					 a8 = 1;
				}

	/*------------------ Serveur4 fait du LB --------------------------------------------*/			
				
				if( Alpha*CPU*CPU *(double)(2*i - 2*t + 2) + Em*gamma <0 )
				{
					 tab[9] = Alpha*CPU*CPU *(double)(2*i - 2*t + 2) + Em*gamma;
					 a9 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*j - 2*t + 2) + Em*gamma <0  )
				{ 
					 tab[10] = Alpha*CPU*CPU *(double)(2*j - 2*t + 2) + Em*gamma;
					 a10 = 1;
				}
				if( Alpha*CPU*CPU *(double)(2*k - 2*t + 2) + Em*gamma <0  )
				{ 
					 tab[11] = Alpha*CPU*CPU *(double)(2*k - 2*t + 2) + Em*gamma;
					 a11 = 1;
				}
				
				
				MAT[i][j][k][t] = Min_tab(tab,12) + 1;
				
				if( a0 == 0 && a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0 && a5 == 0 && a6 == 0 && a7 == 0 && a8 == 0 && a9 == 0 && a10 == 0 && a11 == 0  )
				{
						MAT[i][j][k][t] = -1;
				}	
				if( a0 == 1 && a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1 && a5 == 1 && a6 == 1 && a7 == 1 && a8 == 1 && a9 == 1 && a10 == 1 && a11 == 1 )
				{
						printf("Hmmm Etat (%d,%d,%d,%d) PROBLEME ! \n",i,j,k,t);
				}
			//printf("(%d,%d,%d) = [%f,%f,%f,%f,%f,%f] \n",i,j,k,tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
				
			}
		}
		
	}	
}

fprintf(f1,"%5d \n",taille);
for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		for(k=0; k<taille; k=k+1){
			
			for(t=0; t<taille; t=t+1){

				fprintf(f1,"%5d %5d %5d %5d %5d \n",i,j,k,t,MAT[i][j][k][t]);
			}
		}
	}
}

printf("State Rewards Matrice Done ! \n");
fclose(f1);
exit(0);


}
