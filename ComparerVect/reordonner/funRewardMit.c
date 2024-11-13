// funreward for mitrani's model


#define Energie1 1      // consommation d'un serveur allumé actif
#define Energie2 0.6   // consommation d'un serveur allumé non actif
#define EnergieOn 1.5   // consommation d'allumage d'un serveur
#include "fun.c" 



double proba_perte(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i,indice1,indice2;
indice1=-1;
indice2=-1;	

for(i=0; i<taille*2 ; i=i+2){
        if(tab[i] == BufferSize & tab[i+1] == 1)
        indice1 =  (int)i/2;
        if(tab[i] == BufferSize & tab[i+1] == 2)  
        indice2 = (int)i/2;
    }   
return pi[indice1]+pi[indice2]; 		
}


double energie(int tab[],double pi[],int taille){
	
	int i,Inservice,Outservice;
	double c1,c2,c3;
	double ConsMoy = 0;
	
	for(i=0; i<taille*2 ; i=i+2){
		
		switch (tab[i+1]) {
			
		case 0:
			Inservice = min(tab[i],AlwaysOn);
			Outservice = AlwaysOn - Inservice; 
			c1 = Inservice*Energie1 + Outservice*Energie2; 
			ConsMoy += c1*pi[(int)i/2];
			break;
				
		case 1:
			Inservice = min(tab[i],AlwaysOn);
			Outservice = AlwaysOn - Inservice; 
			c2 = Inservice*Energie1 + Outservice*Energie2 + OnAndOff*EnergieOn;
			ConsMoy += c2*pi[(int)i/2];
			break;
		
		case 2:
			Inservice = min(tab[i],AlwaysOn+OnAndOff);
			Outservice = AlwaysOn+OnAndOff - Inservice;
			c3 = Inservice*Energie1 + Outservice*Energie2;
			ConsMoy += c3*pi[(int)i/2];
			break;	
			
		default	: 
			printf("\nProbleme dans un etat") ;	
			break;
	}
    }   
	
	
	return ConsMoy;
	}


double NombreMoyen(int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
double NbreMoy = 0;	
int i;

for(i=0; i<taille*2 ; i=i+2){     
        NbreMoy += tab[i]*pi[(int)i/2];
    }   	
	
return NbreMoy;	
}

double TempAttente(double NbreMoyAtt){   // Temps moyen des clients en attente (loi de little : Ta = Na/Lambda et Ts = Ns/Lambda)
	return NbreMoyAtt/Lambda;
}

double proba_serveur_actif(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i,indice1;
indice1=-1;

double ProbaMoyenne = 0;

for(i=0; i<taille*2 ; i=i+2){
        if( tab[i+1] == 2)
        {
        indice1 =  (int)i/2;
        ProbaMoyenne += pi[indice1];
		}
    }   
return ProbaMoyenne; 		
}


















