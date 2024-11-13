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

int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
int a , b;
int taille = BufferSize+1;
int MAT[taille][taille];

if (argc!=4) 
   usage1();
   
++argv;
double gamma = atof(*argv)/10; // gamma = gamma12 = gamma21
++argv;
int Alpha= atoi(*argv);
++argv;
double Eb = atof(*argv);

FILE *f1=fopen("StateReward.matrix","w");

int i,j;

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		MAT[i][j] = 0;
	}
}

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		a = b = 0;
		//printf("Etat (%d,%d) = %lf et %lf  \n",i,j,Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Eb, Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Eb);
		//if(i!=0 || j!=0 )
		//{
			if( Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Eb*gamma <0 )
			{
				a = 1;
			}
			if( Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Eb*gamma <0  )
			{ 
				 b = 1;
			}
			if( a == 1 && b == 0)
			{
					MAT[i][j] = +1;
			}	
			if( a == 0 && b == 1)
			{
					 MAT[i][j] = +2;
			}	
			if( a == 0 && b == 0)
			{
					 MAT[i][j] = -1;
			}	
			if( a == 1 && b == 1)
			{
					printf("Hmmm etat (%d,%d) = %lf et %lf  \n",i,j,Alpha*CPU*CPU *(double)(2*j - 2*i + 2) + Eb, Alpha*CPU*CPU *(double)(2*i - 2*j + 2) + Eb);
			}	
			a = b = 0;
		//}
		
	}
	
}

fprintf(f1,"%5d \n",taille);
for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		fprintf(f1,"%5d",MAT[i][j]);
	}
	fprintf(f1,"\n");
}

fclose(f1);



}
