
/*Programme de calcul de l'energie , ca du LB dans chaque état : Model Jackson multiserveur (infini)*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-20

/*---------------- Parametres du modèles-------------------*/
#define Mu1 1
#define Mu2 1
#define Mu3 1
#define lambda1 17
#define lambda2 2
#define lambda3 2
#define C 20   //nombre de serveurs
#define N 100 // N tend vers l'infinie, taille de la file
#define CPU 1.0/C

/*--------------- Parametres de l'energie------------------*/
#define gama 93 // idle
//#define beta 27 // dynamique
//#define alpha 100 // surcout dynamique
#define Ea 100


void  usage()
{
	printf("usage : ./Model-Jakson  gamma12 alpha Eb \n");
	printf("em      : Energie de migration \n");
	printf("gamma12 : Taux de migration \n");
	exit(1);
}

long double rau1;
long double rau2;
long double rau3;
long double Prb_Routage12;
long double Prb_Routage21;
long double Prb_Routage;
long double gamma12;
long double Eb;
int alpha;
long double PI01;
long double PI02;
long double PI03;
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
	
void Calcul_Proba_Routage() // P(1,2) = gamma12 / (gamma12+Mu1)
{
Prb_Routage= gamma12/(gamma12 + gamma12 + Mu1) ;
}	

void Calcul_Proba_Routage1() // P(1,2) = gamma12 / (gamma12+Mu1)
{
Prb_Routage12 = gamma12/(gamma12 + Mu1) ;
}	

void Calcul_Proba_Routage2() // P(2,1) = gamma21 / (gamma21+Mu2) // sachant que gamma12 = gamma21 et Mu1 = Mu2
{
Prb_Routage21 = gamma12/(gamma12 + Mu2) ;
}		

void Calcul_rau1() // Rau1 = (l1 + l2 x Prb21) / n x (Mu1 + gamma12)
{
	 rau1 = (lambda1 + lambda2*Prb_Routage21)/(Mu1+gamma12);
}

void Calcul_rau2() // Rau1 = (l2 + l1 x Prb12) / n x (Mu2 + gamma21)
{
	 rau2 =  (lambda2 + lambda1*Prb_Routage12)/(Mu2+gamma12); 
}

void Calcul_rau1_rau2_rau3() // Point fixe
{
	 int i;
	 long double raup1, raup2 , raup3;
	 rau1 = rau2 = 0;
	 raup1 = raup2 = raup3 = 0.5;
	 
	 while ( fabs(rau1 -raup1) > EPSILON || fabs(rau2 -raup2) > EPSILON || fabs(rau3 -raup3) > EPSILON) {
		 
		 raup1 = rau1;
		 raup2 = rau2;
		 raup3 = rau3;
		 
		 rau1 = (lambda1 + raup2*Prb_Routage*(gamma12+Mu2) + raup3*Prb_Routage*(gamma12+Mu3))/(Mu1+gamma12 + gamma12);
		 rau2 = (lambda2 + raup1*Prb_Routage12*(gamma12+Mu1) + raup3*Prb_Routage*(gamma12+Mu3))/(Mu2+gamma12 + gamma12);
		 rau3 = (lambda3 + raup1*Prb_Routage12*(gamma12+Mu1) + raup2*Prb_Routage*(gamma12+Mu2))/(Mu3+gamma12 + gamma12);
		 
		 printf("%.10le et %.10le %.10le \n",fabs(rau1 -raup1),fabs(rau2 -raup2), fabs(rau3 -raup3));
	 }
}

void Calule_PI01()
{

PI01 = 0;
	for (int i = 0; i < C; i++) {	
		PI01 += ( (pow_log(rau1,i)) / factorielle(i) );
	}
	PI01 += ( (pow_log(rau1,C)) / ((factorielle(C-1))*(C-rau1)) );
	PI01 = 1.0/PI01;
}

void Calule_PI02()
{

PI02 = 0;
	for (int i = 0; i < C; i++) {	
		PI02 += ( (pow_log(rau2,i)) / factorielle(i) );
	}
	PI02 += ( (pow_log(rau2,C)) / ((factorielle(C-1))*(C-rau2)) );
	PI02 = 1.0/PI02;
}

void Calule_PI03()
{

PI03 = 0;
	for (int i = 0; i < C; i++) {	
		PI03 += ( (pow_log(rau3,i)) / factorielle(i) );
	}
	PI03 += ( (pow_log(rau3,C)) / ((factorielle(C-1))*(C-rau3)) );
	PI03 = 1.0/PI03;
}

void Calcule_PI1()
{
	int i;
	
	PI1 = calloc(N+1,sizeof(long double));
	PI1[0] = PI01;
	
	for (i = 1; i < C; i++) {	
		PI1[i] = ( (pow_log(rau1,i)) / factorielle(i) )*PI01; 
	}
	
	for (i = C; i <= N; i++) {	
		PI1[i] = ( (pow_log(rau1,i)) / ( (factorielle(C)) * (pow_log(C,i-C))  ) )*PI01; 
	}	
}

void Calcule_PI2()
{
	int i;
	
	PI2 = calloc(N+1,sizeof(long double));
	PI2[0] = PI02;
	
	for (i = 1; i < C; i++) {	
		PI2[i] = ( (pow_log(rau2,i)) / factorielle(i) )*PI02; 
	}
	
	for (i = C; i <= N; i++) {	
		PI2[i] = ( (pow_log(rau2,i)) / ( (factorielle(C)) * (pow_log(C,i-C))  ) )*PI02; 
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

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma12,Nv1,Nv2,Nv1+Nv2,gama,beta,alpha,s1,s2,s3,s4,s3+s4,s1+s2+s3+s4);
fclose(f);	
	
}

void Calcule_Energie_method2() //Non Tronquée: N = infinie, methode numérique
{
int i;
int beta = 220 - alpha - gama;
long double s1 ,s2 , s3, s4, s5, s6, s7, st3, st5;
long double Nv1, Nv11, Nv2, Nv22, Nv3, Nv33;

long double *tab1 = calloc(C,sizeof(long double));
long double *tab2 = calloc(C,sizeof(long double));
long double *tab3 = calloc(C,sizeof(long double));

s1 = s2 = s3 = s4 = s5 = s6 =  Nv1 = Nv2 = Nv11 = Nv22 = st3 = st5 = Nv3 = Nv33 = s7 = 0;

	
	tab1[0] = PI01;
	for (i = 1; i < C; i++) {	
		tab1[i] = ( (pow_log(rau1,i)) / factorielle(i) )*PI01; 
	}
	
	tab2[0] = PI02;
	for (i = 1; i < C; i++) {	
		tab2[i] = ( (pow_log(rau2,i)) / factorielle(i) )*PI02; 
	}
	
	tab3[0] = PI03;
	for (i = 1; i < C; i++) {	
		tab3[i] = ( (pow_log(rau3,i)) / factorielle(i) )*PI03; 
	}


for (i = 0; i < C; i++) {
	
	Nv1 += (i*tab1[i]);	
	Nv11 += (i*i*tab1[i]);	
	s5 += tab1[i];
	
	Nv2 += (i*tab2[i]);	
	Nv22 += (i*i*tab2[i]);	
	s6 += tab2[i];
	
	Nv3 += (i*tab3[i]);	
	Nv33 += (i*i*tab3[i]);	
	s7 += tab3[i];
	
}
	
	Nv1 += (C*(1 - s5));	
	Nv11 += (C*C*(1 - s5));	
	
	Nv2 += (C*(1 - s6));	
	Nv22 += (C*C*(1 - s6));	
	
	Nv3 += (C*(1 - s7));	
	Nv33 += (C*C*(1 - s7));	
	
			
	

s3 += Eb*gamma12*(1-PI01);
s4 += Eb*gamma12*(1-PI02);		
st5 += Eb*gamma12*(1-PI03);	

FILE *f = fopen("Jackson.resultat","a");

s1 = gama + Nv1*CPU*beta + (Nv11*CPU*CPU)*alpha ;
s2 = gama + Nv2*CPU*beta + (Nv22*CPU*CPU)*alpha ;
st3 = gama + Nv3*CPU*beta + (Nv33*CPU*CPU)*alpha ;

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma12,Nv1,Nv2,Nv3,Nv1+Nv2+Nv3,Nv11,Nv22,Nv33,Nv11+Nv22+Nv33,gama,beta,alpha,s1,s2,st3,s3,s4,st5,s3+s4+st5,s1+s2+st3+s3+s4+st5);
fclose(f);	
printf("--------JAKSON NUMERIQUE DONE !------------");
	
}

void Calcule_Energie_method3() //Non Tronquée: N = infinie, E(n^2) et E(n) analytique.
{

int i;
int beta = 220 - alpha - gama;
long double s1 ,s2 , s3, s4, s5, s6;
long double Nv1, Nv11, Nv2, Nv22, Nv3, Nv33, phi1, phi2, phi3;

long double *tab1 = calloc(C,sizeof(long double));
long double *tab2 = calloc(C,sizeof(long double));

s1 = s2 = s3 = s4 = s5 = s6 =  Nv1 = Nv2 = Nv3 = Nv11 = Nv22 = Nv33 = 0;

Nv1 = rau1;
Nv2 = rau2;
Nv3 = rau3;

phi1 = (1/(C-rau1)) * ( ( PI01 * pow_log(rau1,C) ) / factorielle(C-1) );
phi2 = (1/(C-rau2)) * ( ( PI02 * pow_log(rau2,C) ) / factorielle(C-1) );
phi3 = (1/(C-rau3)) * ( ( PI03 * pow_log(rau3,C) ) / factorielle(C-1) );

Nv11 = pow_log(rau1,2) + rau1 * ( 1 - phi1);
Nv22 = pow_log(rau2,2) + rau2 * ( 1 - phi2);
Nv33 = pow_log(rau3,2) + rau3 * ( 1 - phi3);

s4 += Eb*gamma12*(1-PI01);
s5 += Eb*gamma12*(1-PI02);		
s6 += Eb*gamma12*(1-PI03);
	
FILE *f = fopen("Jackson.resultat","a");

s1 = gama + Nv1*CPU*beta + (Nv11*CPU*CPU)*alpha ;
s2 = gama + Nv2*CPU*beta + (Nv22*CPU*CPU)*alpha ;
s3 = gama + Nv3*CPU*beta + (Nv33*CPU*CPU)*alpha ;

fprintf(f,"%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %d %d %d %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf\n ",Eb,gamma12,Nv1,Nv2,Nv3,Nv1+Nv2+Nv3,Nv11,Nv22,Nv33, Nv11+Nv22+Nv33,gama,beta,alpha,s1,s2,s3,s4,s5,s6,s4+s5+s6,s1+s2+s3+s4+s5+s6);
fclose(f);	
printf("--------JAKSON ANALYTIQUE DONE !------------");
	
}



int main(argc,argv)
int argc;
char *argv[];
{
	
	if (argc!=4) usage();
	
	++argv;
    gamma12 = atof(*argv)/10;	
	++argv;
    alpha= atoi(*argv);
    ++argv;
    Eb = atof(*argv);
    
    printf("Parametres : gamm12 = %Lf, et Alpha = %d ,et Eb = %Lf \n",gamma12,alpha,Eb);
    
    Calcul_Proba_Routage1();
    Calcul_Proba_Routage2();
    Calcul_Proba_Routage();
    Calcul_rau1_rau2_rau3();
    Calule_PI01();
    Calule_PI02();
    Calule_PI03();
    /*Calcule_PI1();
    Calcule_PI2();*/
    
    
    printf("Proba Routage = %Lf \n",Prb_Routage);
    printf("Calcule rau1 = %Lf \n",rau1);
    printf("Calcule rau2 = %Lf \n",rau2);
    printf("Calcule rau3 = %Lf \n",rau3);
    printf("Calcule PI01 = %.10Le \n",PI01);
    printf("Calcule PI02 = %.10Le \n",PI02);
    printf("Calcule PI03 = %.10Le \n",PI03);
    
    /*long double som1 = 0;
    printf("PI1 = [ ");
    for (int i = 0; i <= N; i++) { som1 += PI1[i]; printf("%.10Le, ",PI1[i]);}
    printf("] \nSOMME1 = %.10Le \n", som1);
    
    long double som2 = 0;
    printf("PI2 = [ ");
    for (int i = 0; i <= N; i++) { som2 += PI2[i]; printf("%.10Le, ",PI2[i]);}
    printf("] \nSOMME2 = %.10Le \n", som2);*/
    
    Calcule_Energie_method3();
    
    
    
   



exit(0);
}
