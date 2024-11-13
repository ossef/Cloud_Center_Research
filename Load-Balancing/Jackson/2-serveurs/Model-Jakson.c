
/*Programme de calcul de l'energie , ca du LB dans chaque état : Model Jackson multiserveur (infini)*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-25

/*---------------- Parametres du modèles-------------------*/
#define Mu1 1
#define Mu2 1
#define lambda1 2
#define lambda2 17
#define C 20   //nombre de serveurs
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
	printf("usage : ./Model-Jakson  gamma21 alpha Eb \n");
	printf("em      : Energie de migration \n");
	printf("gamma21 : Taux de migration \n");
	exit(1);
}

long double rau1;
long double rau2;
long double Prb_Routage12;
long double Prb_Routage21;
long double gamma21;
long double Eb;
int alpha;
long double PI01;
long double PI02;
long double *PI1;
long double *PI2;


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

void Calcul_Proba_Routage1() // P(1,2) = gamma12 / (gamma12+Mu1)
{
Prb_Routage12 = gamma12/(gamma12 + Mu1) ;
}	

void Calcul_Proba_Routage2() // P(2,1) = gamma21 / (gamma21+Mu2) // sachant que gamma12 = gamma21 et Mu1 = Mu2
{	
Prb_Routage21 = gamma21/(gamma21 + Mu2) ;
}		

void Calcul_rau1_rau2() // Point fixe
{
	 long double raup1, raup2;
	 rau1 = rau2 = 0;
	 raup1 = raup2 = 0.5;
	 
	 while ( fabs(rau1 -raup1) > EPSILON || fabs(rau2 -raup2) > EPSILON) {
		 
		 raup1 = rau1;
		 raup2 = rau2;
		 
		 rau1 = (lambda1 + C*raup2*gamma21)/(1.0*C*(Mu1+gamma12));
		 rau2 = (lambda2 + C*raup1*gamma12)/(1.0*C*(Mu2+gamma21));
		 
		 printf("%.10le et %.10le \n",fabs(rau1 -raup1),fabs(rau2 -raup2));
	 }
}

void Calule_PI01()
{

PI01 = 0;
	for (int i = 0; i < C; i++) {	
		PI01 += ( (pow_log(C*rau1,i)) / factorielle(i) );
	}
	PI01 += ( (pow_log(C*rau1,C)) / ((factorielle(C))*(1-rau1)) );
	PI01 = 1.0/PI01;
}

void Calule_PI02()
{

PI02 = 0;
	for (int i = 0; i < C; i++) {	
		PI02 += ( (pow_log(C*rau2,i)) / factorielle(i) );
	}
	PI02 += ( (pow_log(C*rau2,C)) / ((factorielle(C))*(1-rau2)) );
	PI02 = 1.0/PI02;
}


void Calcule_PI1()
{
	int i;
	
	PI1 = calloc(N+1,sizeof(long double));
	PI1[0] = PI01;
	
	for (i = 1; i < C; i++) {	
		PI1[i] = ( (pow_log(C*rau1,i)) / factorielle(i) )*PI01; 
	}
	
	for (i = C; i <= N; i++) {	
		PI1[i] = ( (pow_log(rau1,i)*(pow_log(C,C))) / (factorielle(C) ))*PI01; 
	}	
}

void Calcule_PI2()
{
	int i;
	
	PI2 = calloc(N+1,sizeof(long double));
	PI2[0] = PI02;
	
	for (i = 1; i < C; i++) {	
		PI2[i] = ( (pow_log(C*rau2,i)) / factorielle(i) )*PI02; 
	}
	
	for (i = C; i <= N; i++) {	
		PI2[i] = ( (pow_log(rau2,i)*(pow_log(C,C))) / (factorielle(C) ))*PI02; 
	}	
}

void Calcule_Energie_method1() //Tronquée à N = 100
{

int i;
int beta = 220 - alpha - gama;
long double s1 ,s2 , s3, s4;
long double Nv1, Nv11, Nv2, Nv22;

s1 = s2 = s3 = s4 = Nv1 = Nv2 = Nv11 = Nv22 = 0;


for (i = 0; i <= N; i++) {
	
	if( i<C )
	{
	Nv1 += i * PI1[i];	
	Nv11 += i * i * PI1[i];	
	
	Nv2 += i * PI2[i];	
	Nv22 += i * i * PI2[i];	
	
	}
	else
	{
	Nv1 += C * PI1[i];	
	Nv11 += C * C * PI1[i];	
	
	Nv2 += C * PI2[i];	
	Nv22 += C * C * PI2[i];			
	}
	
	if(i>0)
	{
	s3 += Eb*gamma12*PI1[i];
	s4 += Eb*gamma12*PI2[i];		
	}
}

FILE *f = fopen("Jackson.resultat","a");

s1 = gama + Nv1*CPU*beta + (Nv11*CPU*CPU)*alpha ;
s2 = gama + Nv2*CPU*beta + (Nv22*CPU*CPU)*alpha ;

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma21,Nv1,Nv2,Nv1+Nv2,gama,beta,alpha,s1,s2,s3,s4,s3+s4,s1+s2+s3+s4);
fclose(f);	
	
}

void Calcule_Energie_method2() //Non Tronquée: N = infinie, methode numérique
{
int i;
int beta = 220 - alpha - gama;
long double s1 ,s2 , s3, s4, s5, s6;
long double Nv1, Nv11, Nv2, Nv22;

long double *tab1 = calloc(C,sizeof(long double));
long double *tab2 = calloc(C,sizeof(long double));

s1 = s2 = s3 = s4 = s5 = s6 =  Nv1 = Nv2 = Nv11 = Nv22 = 0;

	
	tab1[0] = PI01;
	for (i = 1; i < C; i++) {	
		tab1[i] =  ( (pow_log(C*rau1,i)) / factorielle(i) )*PI01; 
	}
	
	tab2[0] = PI02;
	for (i = 1; i < C; i++) {	
		tab2[i] = ( (pow_log(C*rau2,i)) / factorielle(i) )*PI02; 
	}


for (i = 0; i < C; i++) {
	
	Nv1 += (i*tab1[i]);	
	Nv11 += (i*i*tab1[i]);	
	s5 += tab1[i];
	
	Nv2 += (i*tab2[i]);	
	Nv22 += (i*i*tab2[i]);	
	s6 += tab2[i];
	
}
	
	Nv1 += (C*(1 - s5));	
	Nv11 += (C*C*(1 - s5));	
	
	Nv2 += (C*(1 - s6));	
	Nv22 += (C*C*(1 - s6));			
	

s3 += Eb*gamma12*(1-PI01);
s4 += Eb*gamma12*(1-PI02);		

FILE *f = fopen("Jackson.resultat","a");

s1 = gama + Nv1*CPU*beta + (Nv11*CPU*CPU)*alpha ;
s2 = gama + Nv2*CPU*beta + (Nv22*CPU*CPU)*alpha ;

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma21,Nv1,Nv2,Nv1+Nv2,Nv11,Nv22,Nv11+Nv22,gama,beta,alpha,s1,s2,s3,s4,s3+s4,s1+s2+s3+s4);
fclose(f);	
printf("--------JAKSON NUMERIQUE DONE !------------\n");
	
}

void Calcule_Energie_method3() //Non Tronquée: N = infinie, E(n^2) et E(n) analytique.
{

int beta = 220 - alpha - gama;
long double s1 ,s2 , s3, s4;
long double Nv1, Nv11, Nv2, Nv22, phi1, phi2;

s1 = s2 = s3 = s4 =  Nv1 = Nv2 = Nv11 = Nv22 = 0;

Nv1 = C*rau1;
Nv2 = C*rau2;

phi1 = (1.0/(1-rau1)) * ( ( PI01 * pow_log(C*rau1,C) ) / factorielle(C) );
phi2 = (1.0/(1-rau2)) * ( ( PI02 * pow_log(C*rau2,C) ) / factorielle(C) );

Nv11 = pow_log(C*rau1,2) + C*rau1 * ( 1 - phi1);
Nv22 = pow_log(C*rau2,2) + C*rau2 * ( 1 - phi2);

s3 += Eb*gamma12*(1-PI01);
s4 += Eb*gamma12*(1-PI02);		

FILE *f = fopen("Jackson.resultat","a");

s1 = gama + Nv1*CPU*beta + (Nv11*CPU*CPU)*alpha ;
s2 = gama + Nv2*CPU*beta + (Nv22*CPU*CPU)*alpha ;

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma21,Nv1,Nv2,Nv1+Nv2,Nv11,Nv22,Nv11+Nv22,gama,beta,alpha,s1,s2,s3,s4,s3+s4,s1+s2+s3+s4);
fclose(f);	
printf("--------JAKSON ANALYTIQUE DONE !------------\n");
	
}

/*
void Test_Condition()
{
	
long double RoSLB1, RoSLB2;
long double RoLB1, RoLB2;
long double phiSLB1, phiSLB2;
long double phiLB1, phiLB2;
long double PI0LB1, PI0LB2;
long double PI0SLB1, PI0SLB2;
long double gamma12TMP = gamma12;
long double s1,s2;

//--------- MODEL Sans Load Balancing --------
gamma12 = 0;
Calcul_Proba_Routage1();
Calcul_Proba_Routage2();
Calcul_rau1_rau2();
Calule_PI01();
Calule_PI02();

RoSLB1 = rau1;
RoSLB2 = rau2;
PI0SLB1= PI01;
PI0SLB2= PI02;

phiSLB1 =  (1.0/(1-RoSLB1)) * ( ( PI0SLB1* pow_log(C*RoSLB1,C) ) / factorielle(C) );
phiSLB2 =  (1.0/(1-RoSLB2)) * ( ( PI0SLB2* pow_log(C*RoSLB2,C) ) / factorielle(C) );


    printf("Proba Routage 1-2 = %Lf \n",Prb_Routage12);
    printf("Proba Routage 2-1 = %Lf \n",Prb_Routage21);
    printf("Calcule RoSLB1 = %Lf \n",RoSLB1);
    printf("Calcule RoSLB2 = %Lf \n",RoSLB2);
    printf("Calcule PI01 = %.10Le \n",PI0SLB1);
    printf("Calcule PI02 = %.10Le \n",PI0SLB2);

//--------- MODEL Avec Load Balancing --------
gamma12 = gamma12TMP;
Calcul_Proba_Routage1();
Calcul_Proba_Routage2();
Calcul_rau1_rau2();
Calule_PI01();
Calule_PI02();

RoLB1 = rau1;
RoLB2 = rau2;
PI0LB1= PI01;
PI0LB2= PI02;

phiLB1 =  (1.0/(1-RoLB1)) * ( ( PI0LB1* pow_log(C*RoLB1,C) ) / factorielle(C) );
phiLB2 =  (1.0/(1-RoLB2)) * ( ( PI0LB2* pow_log(C*RoLB2,C) ) / factorielle(C) );

    printf("Proba Routage 1-2 = %Lf \n",Prb_Routage12);
    printf("Proba Routage 2-1 = %Lf \n",Prb_Routage21);
    printf("Calcule RoLB1 = %Lf \n",RoLB1);
    printf("Calcule RoLB2 = %Lf \n",RoLB2);
    printf("Calcule PI01 = %.10Le \n",PI0LB1);
    printf("Calcule PI02 = %.10Le \n",PI0LB2);

//-----------Condition de la comparaison -----------

s1 = RoSLB1*phiSLB1 + 2*C*RoSLB1*RoSLB2 + RoSLB2*phiSLB2 + Eb*gamma12*(2-PI0LB1-PI0LB2) / (C*alpha*CPU*CPU);
s2 = RoLB1*phiLB1 + 2*C*RoLB1*RoLB2 + RoLB2*phiLB2;

printf("Comparaison %.10Lf et %.10Lf \n",s1,s2);

if( s1 > s2 )
{
	printf("Condition non verifié !, Dsl avec vos parametres le LB est non efficace  \n");
	exit(0);	
}

}*/

void Fonction_gamma() //(F(gamma_{2,1} - Voir papier energie )
{
	
int beta = 220 - alpha - gama;	
Calcul_rau1_rau2();	

/*long double R2 = lambda2/(C*Mu2*1.0) ;
long double cst = 1.0*lambda2/(1.0*C*(Mu2 + gamma21)) ;
long double k = 1.0*(lambda1+lambda2)/(C*Mu2);*/

long double k = (lambda1 + lambda2)/(1.0*C*Mu2);
long double r2 = lambda2/(1.0*C*Mu2);
long double s1 = gama + 1.0*(k-rau2)*beta + ( pow_log(k-rau2,2) )*alpha ;
long double s2 = gama + (pow_log(rau2,2)/r2)*beta + ( pow_log(rau2,4)/(1.0*r2*r2) )*alpha ;
long double s3 = C*Eb*(rau2 - (pow_log(rau2,2)/r2) ) ;
long double st = s1 + s2 +s3;

//printf(" K = %Lf et r2 = %Lf et rau2 = %Lf \n",k,cst,R2 );
FILE *f = fopen("Fonction_gamma.resultat","a");
fprintf(f,"%Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma21,C*rau2, C*rau1,C*(rau1+rau2),gama,beta,alpha,s3,s2,s2+s3,s1,st);
fclose(f);		
//printf("gamma21 = %Lf et Test = %f et %Lf  \n",gamma21,(17/(20*(1+0.6025)))*20, (17/(20*(1+gamma21)))*20);
}

int main(argc,argv)
int argc;
char *argv[];
{
	
	if (argc!=4) usage();
	
	++argv;
    gamma21 = atof(*argv)/20;	
	++argv;
    alpha= atoi(*argv);
    ++argv;
    Eb = atof(*argv);
    
    printf("Parametres : gamm21 = %Lf, et Alpha = %d ,et Eb = %Lf \n",gamma21,alpha,Eb);
    
    /*Calcul_Proba_Routage1();
    Calcul_Proba_Routage2();
    Calcul_rau1_rau2();
    Calule_PI01();
    Calule_PI02();
    Calcule_PI1();
    Calcule_PI2();
    
    
    printf("Proba Routage 1-2 = %Lf \n",Prb_Routage12);
    printf("Proba Routage 2-1 = %Lf \n",Prb_Routage21);
    printf("Calcule rau1 = %Lf \n",rau1);
    printf("Calcule rau2 = %Lf \n",rau2);
    printf("Calcule PI01 = %.10Le \n",PI01);
    printf("Calcule PI02 = %.10Le \n",PI02);
    
    
    long double som1 = 0;
    printf("PI1 = [ ");
    for (int i = 0; i <= N; i++) { som1 += PI1[i]; printf("%.10Le, ",PI1[i]);}
    printf("] \nSOMME1 = %.10Le \n", som1);
    
    long double som2 = 0;
    printf("PI2 = [ ");
    for (int i = 0; i <= N; i++) { som2 += PI2[i]; printf("%.10Le, ",PI2[i]);}
    printf("] \nSOMME2 = %.10Le \n", som2);
    */
    
    //Test_Condition();
    
    /*Calcul_Proba_Routage1();
    Calcul_Proba_Routage2();
    Calcul_rau1_rau2();
    Calule_PI01();
    Calule_PI02();*/
    
    //Test_Condition();
    //Calcule_Energie_method3();
    
    Fonction_gamma();
    
    
   



exit(0);
}
