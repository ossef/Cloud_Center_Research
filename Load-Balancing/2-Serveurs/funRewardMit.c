// funreward for Model with Load-Balancing



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


double energie(int tab[],double pi[],int taille,double e0,double e1, double eb){
	
	int i,Inservice,Outservice;
	double c1,c2,c3;
	double ConsMoy = 2*e0 * pi[0];
	
	for(i=2; i<taille*2 ; i=i+2){
		
		if( tab[i] ==0 && tab[i+1]>0 )
		{
			ConsMoy += e0*pi[(int)i/2];
			
			if(tab[i+1]>=2)
			{
				ConsMoy += eb*gamma21*pi[(int)i/2];	
			}
		}
		if( tab[i]>0 && tab[i+1] ==0 )
		{
			ConsMoy += e0*pi[(int)i/2];
			
			if(tab[i]>=2)
			{
				ConsMoy += eb*gamma12*pi[(int)i/2];	
			}
		}
		
		if(tab[i]>=1)
				ConsMoy += e1*tab[i]*pi[(int)i/2];
		if(tab[i+1]>=1)
				ConsMoy += e1*tab[i+1]*pi[(int)i/2];
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

/*double TempAttente(double NbreMoyAtt){   // Temps moyen des clients en attente (loi de little : Ta = Na/Lambda et Ts = Ns/Lambda)
	return NbreMoyAtt/Lambda;
}*/


















