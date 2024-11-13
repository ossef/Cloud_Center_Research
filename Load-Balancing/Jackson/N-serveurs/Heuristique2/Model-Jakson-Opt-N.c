
/*Programme de calcul de l'energie , ca du LB dans chaque état : Model Jackson multiserveur (infini)*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-10
#define EPSILON2 0

/*---------------- Parametres du modèles-------------------*/
#define Mu1 1
#define Mu2 1

#define C 10   //nombre de serveurs

#define N 4 // N nombre de files d'attentes


#define CPU 1.0/C
#define gamma12 0.0

/*--------------- Parametres de l'energie------------------*/
#define gama 95 // idle
//#define beta 23 // dynamique
//#define alpha 100 // surcout dynamique


long double Lambda[N] = {9,8,7,6};
//long double Lambda[N] = {9.5,9.5,9.5,5,1,0.1,0.1};
//long double Lambda[N] = {9.5,9.5,5,2,1};
long double Eng[N];
long double Bool[N];
long double R[N]; //charge Initiale, qui change
int type[N]; // 0 = Non defini pour l'instant,
			//  1 : Emetteur, 
		   //   2 : recepteur 

long double SomeRhoD;
long double SomeRhoF;

void  usage()
{
	printf("usage : ./Model-Jakson  Alpha Em \n");
	printf("==> <Alpha>   : Energie 'Quadratique' \n");
	printf("==> <Em>      : Energie de migration \n");
	
	exit(1);
}

long double rau1;  // rau1 Opt
long double rau2; // rau2 Opt
long double gamma21; // gamma21 Opt
long double Eb;
int alpha;
long double some1;
FILE *f;

void Init_tabs()
{
	printf("Lambdas : [ ");
	SomeRhoD = 0; 
	for (int i = 0; i < N; i++)
	{
		Eng[i] = 0;
		Bool[i] = 0;
		type[i] = 0;
		R[i] = Lambda[i]/(C*1.0);
		SomeRhoD += R[i];
		printf(" %Lf - ",R[i]);
	}
	printf("]\n");
	f = fopen("Greedy_Energy.resultat","a");
	
}
unsigned long long int factorielle (unsigned short nombre) // maximum 65! , en printf on utilise %llu
{
    if (nombre == 0)
        return 1;
    else
        return nombre * factorielle(nombre - 1);
}


long double pow_log(long double x, int n) { //logarithmique complexité
	 if (n == 0) return 1;
	 if (n == 1 || x == 0)   return x; 
	 if (n < 0)  return pow(1 / x, -n); 
	 if (n % 2 == 0) return pow(x * x, n / 2);
     else return pow(x * x, n / 2) * x; 
	}


long  double f1( long double ro1)
{
	int beta = 220 - alpha - gama;	
	return gama + 1.0*ro1*beta + pow_log(ro1,2)*alpha ;
}
long  double f2( long double ro2L, long double ro2M)
{
	int beta = 220 - alpha - gama;
	return gama + 1.0*ro2L*beta + pow_log(ro2L,2)*alpha*1.0 + C*ro2M*Eb*1.0 ;
}


long double max(long double a, long double b)
{
	return a < b ? b : a ;
}



void Calcul_Sans_LB()
{
	int beta = 220 - alpha - gama;
	int i;
	long double r;
	long double some = 0;
	

	
	for(i=0; i<N ; i++)
	{
		r = Lambda[i]*1.0/(C*Mu1) ;
		//printf("r = %Lf et gama = %f  et beta = %d r*beta = %Lf et pow = %Lf \n",r,gama*1.0,beta,r*beta,pow_log(r,2)*alpha);
		Eng[i] =  gama*1.0 + r*beta + pow_log(r,2)*alpha ;
		some += Eng[i];
		
	}
	some1 = some;
	gamma21 = 0;
	fprintf(f,"%Lf		",Eb); // pour afficher gamm21 = 0
	for(i=0; i<N ; i++)
	{
		fprintf(f,"%Lf	%Lf		", R[i],Eng[i]);
	}
	fprintf(f,"%Lf		\n", some);
	
}

int Arret_Tour()
{
	int c = 0;
	
	for(int i=0; i<N ; i++)
	{
		if(Bool[i] == 0)
		c++;
	}
	
	if( c == 0 || c == 1) return 0;
	return 1;	
}

void Calcul_LB() // glouton
{
	int i,j,gr,imax,iminG,c,iter;
	long double some,max,minG,RLB;
	long double mean1,mean2,mean3;
	long double qte;
	
	some = 0;
	gr = 0;
	
	mean1 = 0;
	for(i=0; i<N ; i++)
	{
		mean1 += R[i];
	}
	mean1 = mean1/(N*1.0);
	c = 0;
	for(i=0; i<N ; i++) // condition d'arrêt
	{
		if(R[i]>mean1+EPSILON2)
		c++;
	}
		
	iter=0;	
	while( iter<c)  //>= 
	{
				qte = 0;
				for(i=0; i<N ; i++)
				{
					Bool[i] = 0;
				}
		
				for(i=0; i<N ; i++)
				{
					if( type[i] == 0 || type[i] == 1)//Bool[i] == 0 // emeteur
					{
						 max = R[i];
						 imax = i;
						 break;
					}
				}
				
				for(i=0; i<N ; i++)
				{
					if( R[i]>max && ( type[i] == 0 || type[i] == 1 ) )
					{
						max = R[i];
						imax = i;
					}
				}
				
				type[imax] = 1;
				
				
				gr = 0; 
				for(i=0; i<N ; i++)
				{
					if( R[i]<mean1-EPSILON2 && ( type[i] == 0 || type[i] == 2 ) )
					{
						type[i] = 2;
						gr++;
					}
				}
				
			    RLB = R[imax] - mean1 + gr*EPSILON2; // charge à envoyer par imax
			    
			    for(j=0; j<gr ; j++) // calcul de l'energie entre imax et chaque iming
				{
					for(i=0; i<N ; i++)
					{
						if( Bool[i] == 0 && type[i] == 2 )
						{
							minG = R[i];
							iminG = i;
						}
					}
					for(i=0; i<N ; i++)
					{
						if( R[i] < minG && type[i] == 2 && Bool[i] == 0)
						{
							minG = R[i];
							iminG = i;
						}
					}
					
					
					if( RLB > 0 && R[imax] > R[iminG] + EPSILON2 ) 
					{   
					    if( RLB >= mean1 - R[iminG] - EPSILON2 )
					    {
							RLB -= (mean1 - R[iminG] - EPSILON2);
							qte += (mean1 - R[iminG] - EPSILON2);
							R[imax] -=  (mean1 - R[iminG] - EPSILON2);
							R[iminG] = mean1 - EPSILON2;
							//printf("cond1 : R[imax] = %.2Lf et R[iminG] = %.2Lf \n",R[imax],R[iminG]);
							
							Bool[iminG] = 1;
							//Eng[imax] = f2(R[imax],mean2 - R[iminG]);
							Eng[iminG] = f1(R[iminG]);
						}
						else
						{
							R[imax] -= RLB;
							qte += RLB;
							R[iminG] += RLB;
							RLB = 0;
							//printf("cond2 : R[imax] = %.2Lf et R[iminG] = %.2Lf \n",R[imax],R[iminG]);
							
							Bool[iminG] = 1;
							//Eng[imax] = f2(R[imax],RLB);
							Eng[iminG] = f1(R[iminG]);
						}
					} 
				}
				//R[imax] -= qte;
				Eng[imax] = f2(R[imax],qte);
				
				    if( iter!= 0) some1 = some;
					some = 0;
					for(i=0; i<N ; i++)
					{
						some += Eng[i];
					}
					
					if( some < some1)
					{
						fprintf(f,"%Lf		",Eb); // pour afficher gamm21 = 0
						for(i=0; i<N ; i++)
						{
							fprintf(f,"%Lf	%Lf		", R[i],Eng[i]);
						}
						fprintf(f,"%Lf		\n", some);
					}
				
				printf("C = %d et imax = %d, max = %Lf \n",iter,imax,max);
				printf("Types : [");
				for(i=0; i<N ; i++)
				{ printf("%d - ",type[i]);} printf("]\n");
				printf("---> Charges : [");
				for(i=0; i<N ; i++)
				{ printf("%.5Lf - ",R[i]);} printf("]\n");
				
				iter++;
				//printf("compraison de min = %Lf et max = %Lf \n", Eng[imin], Eng[imax]);
		        printf("sometmp = %Lf et some = %Lf \n", some1, some);

				
		}
		
		SomeRhoF = 0;
		for(i=0; i<N ; i++)
		{ SomeRhoF += R[i]; }
		printf("Some Ri = %.5Lf et Some Rhoi = %.5Lf \n",SomeRhoD,SomeRhoF);
}

int main(argc,argv)
int argc;
char *argv[];
{
	
	if (argc!=3) usage();
	
	++argv;
    alpha= atoi(*argv);
    ++argv;
    Eb = atof(*argv);
    
    printf("Parametres : Alpha = %d ,et Eb = %Lf \n",alpha,Eb);
    
    
    Init_tabs();
    Calcul_Sans_LB();
    Calcul_LB();
    
   

fprintf(f,"\n");
fclose(f);
exit(0);
}
