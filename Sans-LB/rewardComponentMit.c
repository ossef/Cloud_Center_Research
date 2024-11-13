// fichier rewardComponent.c pour modele de Mitrani

/* 
 calcul des recompenses a partir de la matrice,
 des probabilites stationnaires, du codage des etats des composantes
 
 V2.0 le 04/05/16
 
 Hypotheses  de fonctionnement : 
 l'argument est le nom du modele : filename 
 la taille est dans le fichiez filename.sz
 le codage dans filename.cd, 
 et la distribution dans filename.pi
 */

#include <stdio.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


/* 
 inclusions des constantes, types et variables particulieres a chaque modele
 */

#include "const.h"

/* Variables Up et Down */
	double e0,e1;

/* Variables donnant l'etendue de chaque variable isolee */ 
int Min[NEt],Max[NEt]; 
typedef int Etat[NEt];

/* Le nombre d'etats atteignables et de transitions */ 

int ReachableStates, NArcs;

/* la distribution stationnaire et la marginale en cours */ 

double *pi; 
long double *marginale;
int *et;


FILE *pf1; 


//#include "fun.c" 
#include "funRewardMit.c"


void usage() { 
    printf("usage : RewardComponent -f filename e0 e1  \n");
    printf("filename.pi, filename.sz and filename.cd must exist before \n");
    exit(1); 
}

void ProblemeMemoire() { printf("Sorry, not enougth memory \n"); exit(1); }


int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
    int i,j, k, plusieur, nb ; 
    int comp; 
    int maxcompsize; 
    long double Mean, Deviate; 
    char s1[20]; 
    char s2[20]; 
    char s3[20]; 
    char s4[20];
    char s5[20];
    
    /* On recupere le nom du modele et on verifie que les fichiers existent */

    if (argc!=5) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            /* on ajoute .sz, .pi et .cd */ 
            strcpy(s2,s1);
            strcpy(s3,s1); 
            strcpy(s4,s1); 
            strcpy(s5,s1); 
            strcat(s1,".sz"); 
            strcat(s2,".pi");
            strcat(s3,".cd"); 
            //strcat(s4,".rwdC"); 
            strcat(s5,".resultat"); 
            /* on verifie si ils existent */ 
            
            e0 = atof(*(++argv));
			e1 =atof (*(++argv));
	
			//printf("Reward : UP = %d et DOWN = %d\n",UP,DOWN);
			
            if ((pf1=fopen(s1,"r"))==NULL) usage(); 
            if ((pf1=fopen(s2,"r"))==NULL) usage(); 
            if ((pf1=fopen(s3,"r"))==NULL) usage(); 
            
            break; 
        } 
        default : usage(); 
    } 
    
    /* On recupere les tailles dans le fichier filename.sz */
    pf1=fopen(s1,"r"); 
    fscanf(pf1,"%12d\n", &NArcs);  // elements non nul
    fscanf(pf1,"%12d\n",&ReachableStates); // nombre d'etats
    /*printf("%12d\n", NArcs); 
    printf("%12d\n",ReachableStates); */
    fclose(pf1); 

  
    
    if (!(pi=(double*)malloc(ReachableStates*sizeof(double)))) ProblemeMemoire(); 
    if (!(et=(int*)malloc(ReachableStates*NEt*sizeof(int)))) ProblemeMemoire();
    
    
    /* Lecture de la matrice de codage dans le fichier filename.cd */
    pf1=fopen(s3,"r"); 
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%d", &j);
        for (i = 0; i < NEt; i++) {
            fscanf(pf1,"%d",&nb);
            et[i+NEt*j] = nb; 
        } /*et[j][i] */ 
        getc(pf1);
    }
    fclose(pf1);
    
    /*   Lecture du vecteur pi dans le fichier filename.pi */
    pf1=fopen(s2,"r");
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%lf \n", &pi[k]); 
    }
    fclose(pf1);
    
    /* Calcul de la probabilité de perte de clients dans le systéme */
    
    //double perte = proba_perte(et,pi,ReachableStates); // incluse dans "funRewardMit.c"
    
    /* Calcul de la consomation d'energie par les serveurs */
    
    double Consenergie =  energie(et,pi,ReachableStates,e0,e1); // incluse dans "funRewardMit.c"
    
    /* Calcul du nombre moyen de client en attente dans la file  */
    
    //double NombreMoyn = NombreMoyen(et,pi,ReachableStates); 
    
    /* Calcul du temps moyen d'attente des clients dans la file */
    
    //double TimeAttente = TempAttente(NombreMoyn);
    
    double eb =0;
    pf1=fopen(s5,"a");
   
    fprintf(pf1,"%.12lf  ", e1);
    fprintf(pf1,"%.12lf  ", e0);
    //fprintf(pf1,"%.12f	 ", eb);
    //fprintf(pf1,"%.12lf  ", log10(perte));
    fprintf(pf1,"%.12lf  ", Consenergie);
    //fprintf(pf1,"%.12lf  ", NombreMoyn);
    //fprintf(pf1,"%.12lf  ", TimeAttente);
    
    fprintf(pf1,"\n");
    
    fclose(pf1);
    //printf("Done RewardComponent\n");
    exit(0); 
}
