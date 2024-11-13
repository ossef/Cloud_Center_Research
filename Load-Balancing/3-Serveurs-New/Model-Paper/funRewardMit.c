// funreward for Model with Load-Balancing

#define gama 93 // idle
//#define beta 27 // dynamique
//#define alpha 100 // surcout dynamique
#define CPU 1.0/BufferSize  // 1/BufferSize
//#define Eb 5
#define Ea 200

#include "fun.c" 

double proba_perte(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i,indice1,indice2;
indice1=-1;
indice2=-1;	

for(i=0; i<taille*NEt ; i=i+NEt){
        if(tab[i] == BufferSize & tab[i+1] == 1)
        indice1 =  (int)i/2;
        if(tab[i] == BufferSize & tab[i+1] == 2)  
        indice2 = (int)i/2;
    }   
return pi[indice1]+pi[indice2]; 		
}


/*double energie1(int tab[],double pi[],int taille,double e0,double e1, double eb){ // Calcule energie Basique
	
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
*/

void energie2(int tab[],double pi[],int taille, char ch[50],double gamma12, int alpha, double Eb, int ***M){ // Calcule Energie Nvelle formule en comptant le LB
	
	int i,Inservice,Outservice;
	double  s1 , s2 ,s3 ,s4, s5, s6, s7, s8, s9, st;
	double *tab1 = calloc(BufferSize+1,sizeof(double));
	double *tab2 = calloc(BufferSize+1,sizeof(double));
	double *tab3 = calloc(BufferSize+1,sizeof(double));
	
	int beta = 220 - alpha - gama;
	
	FILE *f1=fopen(ch,"a");

		st = s1 = s2 = s3 = s4 = s5 = s6 = s7 = s9 = 0;
		for(i=0; i<taille*NEt ; i=i+NEt){
			
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 1)  //tab[i] ==0 && tab[i+1]>=2 )
			{	
					s4 += Eb*gamma12*pi[(int)i/NEt];
					//s5 += pi[(int)i/NEt];
			}
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 2)  //tab[i] ==0 && tab[i+2]>=2 )
			{	
					s5 += Eb*gamma12*pi[(int)i/NEt];
					//s5 += pi[(int)i/NEt];
			}
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 3) //  tab[i+1] ==0 && tab[i]>=2 )
			{
					s6 += Eb*gamma12*pi[(int)i/NEt];	
					//s5 += pi[(int)i/NEt];
			}
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 4) //  tab[i+1] ==0 && tab[i+2]>=2 )
			{
					s7 += Eb*gamma12*pi[(int)i/NEt];	
					//s5 += pi[(int)i/NEt];
			}
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 5)  // tab[i+2] ==0 && tab[i]>=2 )
			{
					s8 += Eb*gamma12*pi[(int)i/NEt];	
					//s5 += pi[(int)i/NEt];
			}
			if( M[tab[i]][tab[i+1]][tab[i+2]] == 6) // tab[i+2] ==0 && tab[i+1]>=2 )
			{
					s9 += Eb*gamma12*pi[(int)i/NEt];	
					//s5 += pi[(int)i/NEt];
			}
			
			tab1[tab[i]] += pi[(int)(i/NEt)];
			tab2[tab[i+1]] += pi[(int)(i/NEt)];
			tab3[tab[i+2]] += pi[(int)(i/NEt)];
		}  
	
    
		/*for(i=0; i<BufferSize+1 ; i++)
			printf("tab1[%d] = %.10le \n",i,tab1[i]);
			
		printf("\n");
		
		for(i=0; i<BufferSize+1 ; i++)
			printf("tab2[%d] = %.10le \n",i,tab2[i]);*/
		
		for(i=0; i<BufferSize+1 ; i++){
			s1 += i*tab1[i];
			s2 += i*tab2[i]; 
			s3 += i*tab3[i];
		} 
	
		printf("gama = %lf et s1 = %lf et s2 = %lf et s3 = %lf \n",gamma12,s1,s2,s3);
		
		fprintf(f1,"%lf %lf %lf %lf %lf %lf  %d %d %d ",Eb,gamma12,s1,s2,s3,s1+s2+s3,gama,beta,alpha);
		s1 = gama + s1*CPU*beta + (s1*CPU)*(s1*CPU)*alpha ;
		s2 = gama + s2*CPU*beta + (s2*CPU)*(s2*CPU)*alpha ;
		s3 = gama + s3*CPU*beta + (s3*CPU)*(s3*CPU)*alpha ;
		st = s1+s2+s3+s4+s5+s6+s7+s8+s9;
		fprintf(f1,"%lf %lf %lf %lf %lf %lf %lf %lf",s1,s2,s3,s4+s5,s6+s7,s8+s9,s4+s5+s6+s7+s8+s9,st);
		
		s1 = s2 = s3 = 0;
		
		for(i=0; i<taille*NEt ; i=i+NEt){
			
           if(tab[i] == BufferSize)
				s1 +=  pi[(int)i/NEt];
           if(tab[i+1] == BufferSize)  
                s2 += pi[(int)i/NEt];
           if(tab[i+2] == BufferSize)  
                s3 += pi[(int)i/NEt];
        }  
		
		fprintf(f1," %lf %lf %lf %lf %lf\n",s1,s2,s3,s1+s2+s3,st/(Lambda1+Lambda2+Lambda3 - Lambda1*s1 - Lambda2*s2 - Lambda3*s3));
		fclose(f1);
}

void energie3(int tab[],double pi[],int taille, char s5[50],int alpha){ // Calcule Energie avec re-allumage
	
	int i,Inservice,Outservice;
	double  s1 , s2 ,s3 ,s4;
	double *tab1 = calloc(BufferSize+1,sizeof(double));
	double *tab2 = calloc(BufferSize+1,sizeof(double));
	
	int beta = 220 - alpha - gama;
	
	FILE *f1=fopen(s5,"a");

		s1 = s2 = s4 = 0;
		s3 = 2*Ea*pi[0]; // l'etat (0,0) necessite deux activations
		for(i=0; i<taille*NEt ; i=i+NEt){
			
			if( tab[i] ==0 && tab[i+1]>=1 )
			{
					s3 += Ea*pi[(int)i/NEt];
			}
			if( tab[i]>=1 && tab[i+1] ==0 )
			{
					s4 += Ea*pi[(int)i/NEt];	
			}
			
			tab1[tab[i]] += pi[(int)(i/NEt)];
			tab2[tab[i+1]] += pi[(int)(i/NEt)];
		}  
	
    
		/*for(i=0; i<BufferSize+1 ; i++)
			printf("tab1[%d] = %.10le \n",i,tab1[i]);
			
		printf("\n");
		
		for(i=0; i<BufferSize+1 ; i++)
			printf("tab2[%d] = %.10le \n",i,tab2[i]);*/
		
		for(i=0; i<BufferSize+1 ; i++){
			s1 += i*tab1[i];
			s2 += i*tab2[i]; 
		} 
	
		printf("Ea = %d et s1 = %lf et s2 = %lf \n",Ea,s1,s2);
		
		fprintf(f1,"%d %lf %lf %d %d %d ",Ea,s1,s2,gama,beta,alpha);
		s1 = gama - gama*(s3/Ea) + s1*CPU*beta + (s1*CPU)*(s1*CPU)*alpha ;
		s2 = gama - gama*(s4/Ea) + s2*CPU*beta + (s2*CPU)*(s2*CPU)*alpha ;
		fprintf(f1,"%lf %lf %lf %lf %lf",s1,s2,s3,s4,s1+s2+s3+s4);
		fprintf(f1,"\n");
		fclose(f1);
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


















