/*-----------------------------------------------------------*/
/* Modéle Load Balancing (eb<e0), un par un, entre 2 files d'attentes, M/M/m serveurs     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : arrivee dans la file2  */
/* 3  : service file 1 */
/* 4  : service file 2 */
/* 5  : Migration de file 1 vers file2 */ 
/* 6  : Migration de file 2 vers file1 */ 
/* 7  : Uniformisation ,loop */

#define BufferSize 20 // 20 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1  20.57 // 17.5// p1 = 9/10 = 0.9 // p1 = 4/(10*0.45) = 0.9 // file 1 trop chargé
#define Lambda2  2 // 2 // p2 = 1/10 = 0.1 // p2 = 2/(10*2) = 0.1 //p2 = 5/(10*  1) = 0.5 // file 2 moyen chargé ( pas chargé)
#define Mu1 1 // service1
#define Mu2 1 // service2
//#define gamma12 30 // migration 1 -> 2
//#define gamma21 0


void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0;
}

double Probabilite(int indexevt, int *E, double gamma12, int **M)
{
    double p1, Delta, a, b;
    double gamma21 = gamma12;
    a = b = 0;
    
    Delta = Lambda1 + Lambda2  + BufferSize*(Mu1 + Mu2) + BufferSize*(gamma12 + gamma21) ;   /* sum of the rates for  uniformisation */
    switch (indexevt) {
		case 1:
			p1 = Lambda1/Delta;
			break;
		case 2:
			p1 = Lambda2/Delta;
			break;
		case 3:
			p1 = (E[0]*Mu1)/Delta;
			break;
		case 4:
			p1 = (E[1]*Mu2)/Delta;
			break;
		case 5:
		    if( M[E[0]][E[1]] == 1 && E[0]>0 && E[1]<BufferSize)
			p1 = (E[0]*gamma12)/Delta;
			break;
		case 6:
		    if( M[E[0]][E[1]] == 2 && E[1]>0 && E[0]<BufferSize)
			p1 = (E[1]*gamma21)/Delta;
			break;
		case 7:
		    if( M[E[0]][E[1]] == 1 && E[0]>0 && E[1]<BufferSize)
		        a = (BufferSize-E[0])*gamma12;
		    else
				a = BufferSize*gamma12;
				
			if( M[E[0]][E[1]] == 2 && E[1]>0 && E[0]<BufferSize)
		        b = (BufferSize-E[1])*gamma21;
		    else
				b = BufferSize*gamma21;
				
			p1 =  ((BufferSize-E[0])*Mu1 +(BufferSize-E[1])*Mu2 + a + b) /Delta;
			break;
		
    }
    return(p1);
}


void Equation(int *E, int indexevt, int *F, int *R, int **M)
{	
    F[0] = E[0]; F[1] = E[1];
     switch (indexevt) {
		case 1:
			if (E[0]<Max[0]) {F[0]++;}
			break;
		case 2:
			if (E[1]<Max[1]) { F[1]++;}
			break;
		case 3:
			if (E[0]>Min[0]) { F[0]--;}
			break;
		case 4:
			if (E[1]>Min[1]) { F[1]--;}
			break;
		case 5:
			if( M[E[0]][E[1]] == 1 && E[0]>0 && E[1]<BufferSize)//&&  E[0]>=2 && E[1] ==0 ) )
		    {	
				//printf("BRRRRRRRRRRRRRRR (%d,%d) %5d \n",E[0],E[1],M[E[0]][E[1]]);
				F[0]--; F[1]++;
			}
			break;	
		case 6:	
			if( M[E[0]][E[1]] == 2 && E[1]>0 && E[0]<BufferSize)// &&  E[0] ==0 && E[1]>=2 )//E[0]>1 && E[1]<BufferSize) )
		    {
				//printf("BRRRRRRRRRRRRRRR (%d,%d) %5d \n" ,E[0],E[1],M[E[0]][E[1]]);
				F[0]++;F[1]--;
			}
			break;	
		case 7:
			break;
    }
}


void InitParticuliere()
{
}
