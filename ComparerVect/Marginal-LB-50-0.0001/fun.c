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

#define BufferSize 50 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1 12.0
#define Lambda2 9.0
#define Mu1 2 // service1
#define Mu2 1 // service2
#define gamma12 0.0001  // migration 1 -> 2
#define gamma21 0.0001  // migration 2 -> 1


void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0;
}

double Probabilite(int indexevt, int *E)
{
    double p1, Delta;
    int nbServer, inservice;    
 
    Delta = Lambda1 + Lambda2  + BufferSize*(Mu1 + Mu2) + gamma12 + gamma21 ;   /* sum of the rates for  uniformisation */
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
			p1 = gamma12/Delta;
			break;
		case 6:
			p1 =  gamma21/Delta;
			break;
		case 7:
			p1 =  ((BufferSize-E[0])*Mu1 +(BufferSize-E[1])*Mu2) /Delta;
			break;
		
    }
    return(p1);
}

void Equation(int *E, int indexevt, int *F, int *R)
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
		    if (E[0]>(Min[0]+1)  && E[1]== Min[1] )
		    {
				F[0]--; F[1]++;
			}
			break;
		case 6:
			if (E[1]>(Min[1]+1)  && E[0] == Min[0] )
		    {
				F[1]--;F[0]++;
			}
			break;
		case 7:
			break;
    }
}


void InitParticuliere()
{
}
