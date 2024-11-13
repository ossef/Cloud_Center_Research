/*-----------------------------------------------------------*/
/* Modéle Load Balancing (eb<e0), un par un, entre 2 files d'attentes, M/M/m serveurs     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : arrivee dans la file2  */
/* 3  : arrivee dans la file3  */
/* 4  : service file 1 */
/* 5  : service file 2 */
/* 6  : service file 3 */
/* 7  : Migration de file 1 vers file2 */ 
/* 8  : Migration de file 1 vers file3 */ 
/* 9  : Migration de file 2 vers file1 */ 
/* 10  : Migration de file 2 vers file3 */ 
/* 11  : Migration de file 3 vers file1 */ 
/* 12  : Migration de file 3 vers file2 */ 
/* 13  : Uniformisation ,loop */

#define BufferSize 20 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1 17.5  // p1 = 5/(10*0.55) = 0.9 // file 1 trop chargé
#define Lambda2 2  // p2 = 5/(10*1) = 0.5
#define Lambda3 1  // p3 = 5/(10*5) = 0.1 //p2 = 5/(10*  1) = 0.5 // file 2 moyen chargé ( pas chargé)
#define Mu1 1 // service1
#define Mu2 1 // service2
#define Mu3 1
//#define gamma12 30 // migration 1 -> 2
//#define gamma21 0

void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = BufferSize;
    Min[2] = 0;  Max[2] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0; E[2] = 0;
}

double Probabilite(int indexevt, int *E, double gamma12, int ***M)
{
    double p1, Delta; 
    double gamma21, gamma31 , gamma13 , gamma23 , gamma32;
    gamma21 = gamma31 = gamma13 = gamma23 = gamma32 = gamma12 ;
    double a, b, c, d, e, f;
    a = b = c = d = e = f = 0;

    Delta = Lambda1 + Lambda2 + Lambda3  + BufferSize*(Mu1 + Mu2 + Mu3) + BufferSize*(gamma12 + gamma13 + gamma21 + gamma23 + gamma31 + gamma32);   /* sum of the rates for  uniformisation */
    switch (indexevt) {
		case 1:
			p1 = Lambda1/Delta;
			break;
		case 2:
			p1 = Lambda2/Delta;
			break;
		case 3:
			p1 = Lambda3/Delta;
			break;
		case 4:
			p1 = (E[0]*Mu1)/Delta;
			break;
		case 5:
			p1 = (E[1]*Mu2)/Delta;
			break;
		case 6:
			p1 = (E[2]*Mu3)/Delta;
			break;
		case 7:
			if( M[E[0]][E[1]][E[2]] == 1 && E[0]>0 && E[1]<BufferSize)
			p1 = (E[0]*gamma12)/Delta;
			break;
		case 8:
			if (M[E[0]][E[1]][E[2]] == 2 && E[0]>0 && E[2]<BufferSize )
			p1 =  (E[0]*gamma13)/Delta;
			break;
		case 9:
			if (M[E[0]][E[1]][E[2]] == 3 && E[1]>0 && E[0]<BufferSize)
			p1 = (E[1]*gamma21)/Delta;
			break;
		case 10:
			if (M[E[0]][E[1]][E[2]] == 4 && E[1]>0 && E[2]<BufferSize)
			p1 = (E[1]*gamma23)/Delta;
			break;
		case 11:
			if (M[E[0]][E[1]][E[2]] == 5 && E[2]>0 && E[0]<BufferSize )
			p1 = (E[2]*gamma31)/Delta;
			break;
		case 12:
			if ( M[E[0]][E[1]][E[2]] == 6 && E[2]>0 && E[1]<BufferSize)
			p1 =  (E[2]*gamma32)/Delta;
			break;
		case 13:
			if( M[E[0]][E[1]][E[2]] == 1 && E[0]>0 && E[1]<BufferSize) //7
			     a = (BufferSize-E[0])*gamma12;
		    else
				 a = BufferSize*gamma12;
				 
			if (M[E[0]][E[1]][E[2]] == 2 && E[0]>0 && E[2]<BufferSize ) //8
			     b = (BufferSize-E[0])*gamma13;
		    else
				 b = BufferSize*gamma13;
			
			if (M[E[0]][E[1]][E[2]] == 3 && E[1]>0 && E[0]<BufferSize) //9
			     c = (BufferSize-E[1])*gamma21;
		    else
				 c = BufferSize*gamma21;
				 
			if (M[E[0]][E[1]][E[2]] == 4 && E[1]>0 && E[2]<BufferSize) //10
			     d = (BufferSize-E[1])*gamma23;
		    else
				 d = BufferSize*gamma23;
				 
			if (M[E[0]][E[1]][E[2]] == 5 && E[2]>0 && E[0]<BufferSize ) //11
			     e = (BufferSize-E[2])*gamma31;
		    else
				 e = BufferSize*gamma31;
				 
			if ( M[E[0]][E[1]][E[2]] == 6 && E[2]>0 && E[1]<BufferSize) //12
			     f = (BufferSize-E[2])*gamma32;
		    else
				 f = BufferSize*gamma32;
				
				
			p1 =  ((BufferSize-E[0])*Mu1 +(BufferSize-E[1])*Mu2 + (BufferSize-E[2])*Mu3 + a + b + c + d + e + f)  /Delta;
			break;
		
    }
    return(p1);
}

void Equation(int *E, int indexevt, int *F, int *R, int ***M)
{
    F[0] = E[0]; F[1] = E[1]; F[2] = E[2];
     switch (indexevt) {
		case 1:
			if (E[0]<Max[0]) {F[0]++;}
			break;
		case 2:
			if (E[1]<Max[1]) { F[1]++;}
			break;
		case 3:
			if (E[2]<Max[2]) { F[2]++;}
			break;
		case 4:
			if (E[0]>Min[0]) { F[0]--;}
			break;
		case 5:
			if (E[1]>Min[1]) { F[1]--;}
			break;
		case 6:
			if (E[2]>Min[2]) { F[2]--;}
			break;
		case 7:
		    if( M[E[0]][E[1]][E[2]] == 1 && E[0]>0 && E[1]<BufferSize)
		    {
				F[0]--; F[1]++;
			}
			break;
		case 8:
		    if (M[E[0]][E[1]][E[2]] == 2 && E[0]>0 && E[2]<BufferSize )
		    {
				F[0]--; F[2]++;
			}
			break;
		case 9:
		    if (M[E[0]][E[1]][E[2]] == 3 && E[1]>0 && E[0]<BufferSize)
		    {
				F[1]--; F[0]++;
			}
			break;
		case 10:
		    if (M[E[0]][E[1]][E[2]] == 4 && E[1]>0 && E[2]<BufferSize)
		    {
				F[1]--; F[2]++;
			}
			break;
		case 11:
		    if (M[E[0]][E[1]][E[2]] == 5 && E[2]>0 && E[0]<BufferSize )
		    {
				F[2]--; F[0]++;
			}
			break;
		case 12:
		    if ( M[E[0]][E[1]][E[2]] == 6 && E[2]>0 && E[1]<BufferSize)
		    {
				F[2]--; F[1]++;
			}
			break;
		case 13:
			break;
    }
}


void InitParticuliere()
{
}
