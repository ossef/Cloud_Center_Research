
/*Programme de calcul de l'energie , ca du LB dans chaque état : Model Jackson multiserveur (infini)*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-25

/*---------------- Parametres du modèles-------------------*/
#define Mu1 1
#define Mu2 1
#define lambda1 1.419628671 // le moins chargée
#define lambda2 0.762775717 // le plus chargée
#define C 10   //nombre de serveurs
#define N 100 // N tend vers l'infinie, taille de la file
#define CPU 1.0/C
#define gamma12 0.0

/*--------------- Parametres de l'energie------------------*/
#define gama 95 // idle
//#define beta 23 // dynamique
//#define alpha 100 // surcout dynamique
#define Ea 100


void  usage()
{
	printf("usage : ./Model-Jakson  alpha Em \n");
	printf("em      : Energie de migration \n");
	printf("gamma12 : Taux de migration \n");
	exit(1);
}

long double rau1;  // rau1 Opt
long double rau2; // rau2 Opt
long double gamma21; // gamma21 Opt
long double Eb;
long double someSLB;
int alpha;
FILE*f;


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
long  double f2( long double ro2)
{
	int beta = 220 - alpha - gama;
	long double r2 = lambda2/(1.0*C*Mu2);
	return gama + (pow_log(ro2,2)/(r2*1.0))*beta + ( pow_log(ro2,4)/(1.0*r2*r2) )*alpha ;
}
long  double f3( long double ro2)
{
	int beta = 220 - alpha - gama;
	long double r2 = lambda2/(1.0*C*Mu2);
	return C*Eb*1.0*(ro2 - (pow_log(ro2,2)/(r2*1.0)) ) ;
}
long  double f4( long double ro1, long double ro2)
{
	return f1(ro1)+f2(ro2)+f3(ro2);	
}

long double max(long double a, long double b)
{
	return a < b ? b : a ;
}
void Calcul_Opt() // Grâce à la methode de cardan 
{
	
int beta = 220 - alpha - gama;	
int signeDelta,i;
int exist = -1;

long double r2 = lambda2/(1.0*C*Mu2);
long double k = lambda1/(1.0*C*Mu1) + r2;
long double a = ((alpha*r2 - C*Eb + beta)*r2)/(1.0*2*alpha);
long double b = ((C*Eb - beta - 2*alpha*k)*r2*r2)/(1.0*4*alpha);
long double Delta = - ( 4*pow_log(a,3) + 27*pow_log(b,2) ) ;
long double tmp,tmp1,tmp2,tmp3,borne1,borne2;


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

 long double min = f4(borne2, borne1);	//première sokutiion ro2 = 0, r1 = k
 int indice_min = 0;
 
 for (i = 1; i < 4; i++) {
	 
	 if( tabDom[i] == 1 )
	 {
		 if( f4(k-tabsol[i],tabsol[i]) < min )
		 {
			 min = f4(k-tabsol[i],tabsol[i]);
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

		 long double min2 = f4(borne2,borne1);	
		 int indice_min2 = 0;
		 
		 for (i = 1; i < 5; i++) {
			 
			 if( tabDom2[i] == 1 )
			 {
				 if( f4(k-tabsol2[i],tabsol2[i]) < min2 )
				 {
					 min2 = f4(k-tabsol2[i],tabsol2[i]);
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

		 long double min3 = f4(borne2,borne1);	
		 int indice_min3 = 0;
		 
		 for (i = 1; i < 3; i++) {
			 
			 if( tabDom3[i] == 1 )
			 {
				 if( f4(k-tabsol3[i],tabsol3[i]) < min3 )
				 {
					 min3 = f4(k-tabsol3[i],tabsol3[i]);
					 indice_min3 = i;
				 } 
			 } 
		}
	 
	 rau2 = tabsol3[indice_min3];

    }
    
    
    
   rau1 = k - rau2;
   gamma21 = lambda2/(C*rau2*1.0) - Mu2;
   
   if(gamma21 <= 0 || rau2 < borne1 || rau2 > borne2 )
   {
	 rau2 = r2;   
	 rau1 = k-r2;
	 gamma21 = 0;
   }
	 
   long double s1 = f1(rau1);
   long double s2 = f2(rau2);
   long double s3 = f3(rau2);
   long double st = s1 + s2 +s3;
    
   printf("Delta = %.10Lf \n",Delta);
   printf("rau2 = %.10Lf \n",rau2); 
   fprintf(f,"%Lf %Lf %.10Lf %.10Lf %Lf %d %d %d %.10Lf %Lf %Lf %.10Lf %Lf %d %Lf\n ",Eb,gamma21,rau1, rau2,C*(rau1+rau2),gama,beta,alpha,s1,s3,s2,s2+s3,st,signeDelta, ((someSLB-st)/someSLB)*100);
   fclose(f);	
    
}

void Calcul_Sans_LB()
{
	int beta = 220 - alpha - gama;
	int i;
	long double r,Eng;
	someSLB = 0;
	
	gamma21 = 0;
	f = fopen("Fonction_Opt.resultat","a");

	fprintf(f,"%Lf %Lf ",Eb,gamma21); // pour afficher gamm21 = 0
	for(i=0; i<2 ; i++)
	{
		if( i == 0)
		r = (lambda1)/(C*Mu1*1.0) ;
		if( i == 1)
		r = (lambda2)/(C*Mu2*1.0) ;
		//printf("r = %Lf et gama = %f  et beta = %d r*beta = %Lf et pow = %Lf \n",r,gama*1.0,beta,r*beta,pow_log(r,2)*alpha);
		Eng =  gama*1.0 + r*beta + pow_log(r,2)*alpha ;
		fprintf(f,"%Lf %Lf ",r,Eng);
		someSLB += Eng;
		
	}
	fprintf(f,"%Lf \n", someSLB);
	
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
    
    
    Calcul_Sans_LB();
    Calcul_Opt();
    
    
   



exit(0);
}
