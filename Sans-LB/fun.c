/*-----------------------------------------------------------*/
/* Modéle de 2 files d'attentes, M/M/m serveurs (independante)     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : arrivee dans la file2  */
/* 3  : service file 1 */
/* 4  : service file 2 */
/* 5  : Uniformisation ,loop */

/*
#define BufferSize 50 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1 20.0 // p1 = 20/(50*0.45) = 0.9 // file 1 trop chargé
#define Lambda2 10.0 // p2 = 10/(50*  2) = 0.1 // file 2 pas chargé
#define Mu1 0.45 // service1
#define Mu2 2 // service2
*/

#define BufferSize 10 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1 4.0 // p1 = 20/(50*0.45) = 0.9 // file 1 trop chargé
#define Lambda2 2.0 // p2 = 10/(50*  2) = 0.1 // file 2 pas chargé
#define Mu1 0.45 // service1
#define Mu2 2 // service2



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
 
    Delta = Lambda1 + Lambda2  + BufferSize*(Mu1 + Mu2) ;   /* sum of the rates for  uniformisation */
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
			break;
    }
}


void InitParticuliere()
{
}
