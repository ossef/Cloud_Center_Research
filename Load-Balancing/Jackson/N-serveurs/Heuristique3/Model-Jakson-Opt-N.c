
/*Programme de calcul de l'energie , ca du LB dans chaque état : Model Jackson multiserveur (infini)*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-10
//#define EPSILON2 1e-2

/*---------------- Parametres du modèles-------------------*/
#define Mu1 1
#define Mu2 1

#define C 10   //nombre de serveurs

#define N 7 // N nombre de files d'attentes


#define CPU 1.0/C
#define gamma12 0.0

/*--------------- Parametres de l'energie------------------*/
#define gama 95 // idle
//#define beta 23 // dynamique
//#define alpha 100 // surcout dynamique


long double Lambda[N] = {9.5,9.5,9.5,5,1,0.1,0.1};
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
long  double f2( long double ro2L, long double ro2M) // en conaissant exactement la qté en locale/migration
{
	int beta = 220 - alpha - gama;
	return gama + 1.0*ro2L*beta + pow_log(ro2L,2)*alpha*1.0 + C*ro2M*Eb*1.0 ;
}


long  double ff2( long double ro2, int indice2) // en connaissant le taux gamma21
{
	int beta = 220 - alpha - gama;
	if (ro2 == 0) return gama;
	long double r2 = R[indice2]; //Lambda[indice2]/(1.0*C*Mu2);
	if(gamma21 == 0) return gama + 1.0*ro2*beta + pow_log(ro2,2)*alpha ;
	return gama + (pow_log(ro2,2)/(r2*1.0))*beta + ( pow_log(ro2,4)/(1.0*r2*r2) )*alpha ;
}
long  double ff3( long double ro2, int indice2 )
{
	int beta = 220 - alpha - gama;
	if (ro2 == 0) return 0;
	long double r2 = R[indice2]; //Lambda[indice2]/(1.0*C*Mu2);
	if(gamma21 == 0) return 0;
	return C*Eb*(ro2 - (pow_log(ro2,2)/(r2*1.0)) ) ;
}
long  double f4( long double ro1, long double ro2, int indice2)
{
	return f1(ro1)+ff2(ro2,indice2)+ff3(ro2,indice2);	
}


long double max(long double a, long double b)
{
	return a < b ? b : a ;
}

int IMax_Groupe()
{
	
int i,imax;
long double max;
	
	for(i=0; i<N ; i++)
	{
		if( type[i] == 2)//Bool[i] == 0 // emeteur
		{
			max = R[i];
			imax = i;
			break;
		}
	}
				
	for(i=0; i<N ; i++)
	{
		if( R[i]>max && type[i] == 2 )
		{
			max = R[i];
			imax = i;
		}
	}

return imax;	
}

int IMin_Groupe()
{
	
int i,imin;
long double min;
	
	for(i=0; i<N ; i++)
	{
		if( type[i] == 2)//Bool[i] == 0 // emeteur
		{
			min = R[i];
			imin = i;
			break;
		}
	}
				
	for(i=0; i<N ; i++)
	{
		if( R[i]<min && type[i] == 2 )
		{
			min = R[i];
			imin = i;
		}
	}

return imin;	
}

long double IMean_Groupe()
{
long double s;
int c = 0;

	s = 0;
	for(int i=0; i<N ; i++)
	{
		if(type[i] == 2 )
		{
			s += R[i];
			c++;
		}
	}
	
return s/(c*1.0);	
}

void Calcul_Opt(long double r1, int indice2) // Grâce à la methode de cardan 
{
	
int beta = 220 - alpha - gama;	
int signeDelta,i;
int exist = -1;

long double r2 = R[indice2];//Lambda[indice2]/(1.0*C*Mu2);
long double k = r1 + r2; //R[indice1] + r2; // k = r1 + r2
long double a = ((alpha*r2 - C*Eb + beta)*r2)/(1.0*2*alpha);
long double b = ((C*Eb - beta - 2*alpha*k)*r2*r2)/(1.0*4*alpha);
long double Delta = - ( 4*pow_log(a,3) + 27*pow_log(b,2) ) ;
long double tmp,tmp1,tmp2,tmp3;
long double borne1,borne2;

FILE *f = fopen("Fonction_Opt.resultat","a");

if( k<=1)
{
	borne1 = 0;
	borne2 = k;
}
else
{
	borne1 = k-1;
	borne2 = 1;
}

if(Delta == 0)
{
 signeDelta = 0;
 long double tabsol[4];
 int tabDom[4];


 tabsol[0] = borne1; // pour comparer au bornes
 tabsol[1] = (3.0*b)/a;
 tabsol[2] = (-3.0*b)/(2*a);
 tabsol[3] = borne2;

 
 for (i = 0; i < 4; i++) { // On verifie quelles solutions sont dans le Domaine D = [0,k]
	 if( tabsol[i] < borne1 || tabsol[i] >borne2)
		tabDom[i] = -1;
	 else
		tabDom[i] = 1;
	}

 long double min = f4(borne2, borne1, indice2);	//première sokutiion ro2 = 0, r1 = k
 int indice_min = 0;
 
 for (i = 1; i < 4; i++) {
	 
	 if( tabDom[i] == 1 )
	 {
		 if( f4(k-tabsol[i],tabsol[i],indice2) < min )
		 {
			 min = f4(k-tabsol[i],tabsol[i],indice2);
			 indice_min = i;
		 } 
	 } 
 }
 
 /*if(indice_min >=1 && indice_min <= 2)
   exist = 1;*/
 
 rau2 = tabsol[indice_min];

}


if(Delta >0)
    {
		signeDelta = 1;
		long double tabsol2[5];
        int tabDom2[5];
		
		tabsol2[0] = borne1; // pour comparer au bornes
        tabsol2[1] = 2*pow(-a/3.0,1/2.0)*cos( (1/3.0)*acos( (3*b/(2*a*1.0))*pow(3.0/-a,1/2.0) ) ) ;
        tabsol2[2] = 2*pow(-a/3.0,1/2.0)*cos( (1/3.0)*acos( (3*b/(2*a*1.0))*pow(3.0/-a,1/2.0) ) + (2*M_PI)/3.0 ) ; 
        tabsol2[3] = 2*pow(-a/3.0,1/2.0)*cos( (1/3.0)*acos( (3*b/(2*a*1.0))*pow(3.0/-a,1/2.0) ) + (4*M_PI)/3.0 ) ; 
        tabsol2[4] = borne2;
        
        
         for (i = 0; i < 5; i++) {
			 if( tabsol2[i] < borne1 || tabsol2[i] >borne2)
				tabDom2[i] = -1;
			 else
				tabDom2[i] = 1;
			}

		 long double min2 = f4(borne2,borne1,indice2);	
		 int indice_min2 = 0;
		 
		 for (i = 1; i < 5; i++) {
			 
			 if( tabDom2[i] == 1 )
			 {
				 if( f4(k-tabsol2[i],tabsol2[i],indice2) < min2 )
				 {
					 min2 = f4(k-tabsol2[i],tabsol2[i],indice2);
					 indice_min2 = i;
				 } 
			 } 
		}
		
		/*if(indice_min2 >=1 && indice_min2 <= 3)
			exist = 1;*/
        
		
		printf("a = %Lf \nb = %Lf\n",a,b);
		printf("Sol1 = %Lf \n", tabsol2[1]);
		printf("Sol2 = %Lf \n", tabsol2[2]);
		printf("Sol3 = %Lf \n", tabsol2[3]);
		
		rau2 = tabsol2[indice_min2];
	}
	
if(Delta < 0)
	{
	 signeDelta = -1;
	 long double tabsol3[3];
     int tabDom3[3];
     
     tabsol3[0] = borne1; // pour comparer au bornes
     tabsol3[2] = borne2;
     
     tmp = pow(-Delta/27.0, 1/(2.0) );
     tmp1 = -b + tmp;
     tmp2 = -b - tmp;
     if( tmp1 < 0 && tmp2 < 0 ) 
       tabsol3[1] = -pow( -tmp1/2.0 , 1/(3.0) ) - pow( -tmp2/2.0 , 1/(3.0) );
     if( tmp1 < 0 && tmp2 > 0 ) 
       tabsol3[1] = -pow( -tmp1/2.0 , 1/(3.0) ) + pow( tmp2/2.0 , 1/(3.0) );
     if( tmp1 > 0 && tmp2 < 0 ) 
       tabsol3[1] = pow( tmp1/2.0 , 1/(3.0) ) - pow( -tmp2/2.0 , 1/(3.0) );
     if( tmp1 > 0 && tmp2 > 0 ) 
	    tabsol3[1] = pow( tmp1/2.0 , 1/(3.0) ) + pow( tmp2/2.0 , 1/(3.0) );
	    
	 
	 for (i = 0; i < 3; i++) {
			 if( tabsol3[i] < borne1 || tabsol3[i] >borne2)
				tabDom3[i] = -1;
			 else
				tabDom3[i] = 1;
			}

		 long double min3 = f4(borne2,borne1,indice2);	
		 int indice_min3 = 0;
		 
		 for (i = 1; i < 3; i++) {
			 
			 if( tabDom3[i] == 1 )
			 {
				 if( f4(k-tabsol3[i],tabsol3[i],indice2) < min3 )
				 {
					 min3 = f4(k-tabsol3[i],tabsol3[i],indice2);
					 indice_min3 = i;
				 } 
			 } 
		}
	 
	 rau2 = tabsol3[indice_min3];

    }
    
   gamma21 = (R[indice2]*C*Mu1*1.0)/(C*rau2*1.0) - Mu2*1.0;//Lambda[indice2]/(C*rau2*1.0) - Mu2; 
   
   //gamma21 = R[indice2]/(C*rau2*1.0) - Mu2;
   
   if(gamma21 <= 0 || rau2 < borne1 || rau2 > borne2 )
   {
	 rau2 = R[indice2];   
	 gamma21 = 0;
   }
    
     rau1 = k - rau2; 
	 //rau2Ut = rau2*(Mu2/((Mu2+gamma21)*1.0));
     long double rau2Ut = (rau2*rau2)/R[indice2]; //(Mu2/((Mu2+gamma21)*1.0));
   
   	 
   long double s1 = f1(rau1);
   long double s2 = ff2(rau2,indice2);
   long double s3 = ff3(rau2,indice2);
   long double st = s1 + s2 +s3;
   
   //R[indice1] = rau1;
   R[indice2] = rau2Ut ;
   
   //Eng[indice1] = s1;
   Eng[indice2] = s2 + s3;

     
   //fprintf(f,"%Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %d %d %Lf\n ",Eb,gamma21,C*rau2, C*rau1,C*(rau1+rau2),gama,beta,alpha,s3,s2,s2+s3,s1,st,signeDelta,exist, ((287-st)/287.0)*100);
	
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

void Diffusion_Charge(long double RLB, int gr)
{
int i,imin1,imin2,c;
long double min1,min2;
int tab[100];
int taille;

while(RLB > 0)
{
	min1 = 1;
	min2 = 1;

	for(i=0; i<N ; i++)
	{
	  if(R[i]<min1 && type[i] == 2)
	  { 
		min1 = R[i];  
		imin1 = i;
	  }	
	}
	c = 0;
	for(i=0; i<N ; i++)
	{
	  if(min1 == R[i] && type[i] == 2)
	  { 
		tab[c++] = i;  
	  }	
	}
	for(i=0; i<N ; i++)
	{
	  if(R[i]<min2 && R[i] != min1  && type[i] == 2 )
	  {
		  min2 = R[i];
		  imin2 = i;
	  }
	}

	if( c == 1 )
	{
		if(RLB >= min2 - min1)
		{
			RLB -= (min2 - min1);
			R[imin1] += (min2 - min1); 
			Eng[imin1] = f1(R[imin1]);
		}
		else
		{
			R[imin1] += RLB; 
			Eng[imin1] = f1(R[imin1]);
			RLB = 0;
		}	
	}
	if( c > 1 )
	{
		if( RLB >= c*(min2 - min1) )
		{
			for(i=0; i<c ; i++)
			{
				R[tab[i]] += (min2 - min1);
				RLB -= 	(min2 - min1);
				Eng[tab[i]] = f1(R[tab[i]]);
			}
		}
		else
		{
			for(i=0; i<c ; i++)
			{
				R[tab[i]] += RLB/(c*1.0);
				Eng[tab[i]] = f1(R[tab[i]]);
			}
			RLB = 0;
		}
	}
}	
}

void Calcul_LB() // glouton
{
	int i,j,gr,imax,iminG,c,iter;
	long double some,max,minG,RLB;
	long double mean1,mean2,mean3;
	long double qte,Ravant;
	
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
		if(R[i]>mean1)
		c++;
	}
	
	gr = 0;
	for(i=0; i<N ; i++)
	{
		if( R[i]<mean1 && ( type[i] == 0 || type[i] == 2 ) )
		{
			type[i] = 2;
			gr++;
		}
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
				
				
				iminG = IMin_Groupe();
				printf("R[Groupe] = %Lf \n",R[iminG]);
				//minG = IMean_Groupe()/(gr*1.0); // pour la moyenne
				minG = R[iminG]/(gr*1.0);  // charge virtuelle : R/N
				Ravant = R[imax];
				printf("Je migre entre R[imax] = %Lf et R[iminG]/N = %Lf et imin = %d \n",R[imax],R[iminG]/(gr*1.0),iminG);
				if(iminG != imax && (R[iminG]/(gr*1.0)) < R[imax]) // à mettre en commentaire pour le calcul du min/max
				Calcul_Opt(minG,imax);
				
			    RLB = Ravant - R[imax]; // charge à envoyer par imax
			    printf("RLB = %.5Lf \n",RLB);
			    Diffusion_Charge(RLB,gr);
			    
				
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
