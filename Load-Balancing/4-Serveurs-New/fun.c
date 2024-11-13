/*-----------------------------------------------------------*/
/* Modéle Load Balancing (eb<e0), un par un, entre 4 files d'attentes, M/M/m serveurs     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : arrivee dans la file2  */
/* 3  : arrivee dans la file3  */
/* 4  : arrivee dans la file4  */
/* 5  : service file 1 */
/* 6  : service file 2 */
/* 7  : service file 3 */
/* 8  : service file 4 */
/* 9  : Migration de file 1 vers file2 */ 
/* 10  : Migration de file 1 vers file3 */ 
/* 11 : Migration de file 1 vers file4 */ 
/* 12 : Migration de file 2 vers file1 */ 
/* 13  : Migration de file 2 vers file3 */ 
/* 14  : Migration de file 2 vers file4 */ 
/* 15  : Migration de file 3 vers file1 */ 
/* 16  : Migration de file 3 vers file2 */ 
/* 17  : Migration de file 3 vers file4 */ 
/* 18  : Migration de file 4 vers file1 */ 
/* 19  : Migration de file 4 vers file2 */ 
/* 20  : Migration de file 4 vers file3 */ 
/* 21  : Uniformisation ,loop */

#define BufferSize 20 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure


#define Lambda1 17.5  // p1 = 5/(10*0.55) = 0.9 // file 1 trop chargé
#define Lambda2 2  // p2 = 5/(10*1) = 0.5
#define Lambda3 2  // p3 = 5/(10*5) = 0.1 //p2 = 5/(10*  1) = 0.5 // file 2 moyen chargé ( pas chargé)
#define Lambda4 1
#define Mu1 1 // service1
#define Mu2 1 // service2
#define Mu3 1
#define Mu4 1
//#define gamma12 30 // migration 1 -> 2
//#define gamma21 0

void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = BufferSize;
    Min[2] = 0;  Max[2] = BufferSize;
    Min[3] = 0;  Max[3] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0; E[2] = 0; E[3] = 0;
}

double Probabilite(int indexevt, int *E, double gamma12, int ****M)
{
    double p1, Delta; 
    double gamma13,gamma14,gamma21,gamma23,gamma24,gamma31,gamma32,gamma34,gamma41,gamma42,gamma43;
    gamma13 = gamma14 = gamma21 = gamma23 = gamma24 = gamma31 = gamma32 = gamma34 = gamma41 = gamma42 = gamma43 = gamma12 ;
    double a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12;
    a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = a10 = a11 = a12 = 0;
    
    Delta = Lambda1 + Lambda2 + Lambda3 + Lambda4 + BufferSize*(Mu1 + Mu2 + Mu3 + Mu4) + BufferSize*(gamma12 + gamma13 + gamma14 + gamma21 + gamma23 + gamma24 + gamma31 + gamma32 + gamma34 + gamma41 + gamma42 + gamma43);
       /* sum of the rates for  uniformisation */
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
			p1 = Lambda4/Delta;
			break;
		case 5:
			p1 = (E[0]*Mu1)/Delta;
			break;
		case 6:
			p1 = (E[1]*Mu2)/Delta;
			break;
		case 7:
			p1 = (E[2]*Mu3)/Delta;
			break;
		case 8:
			p1 = (E[3]*Mu4)/Delta;
			break;
		case 9:
			if( M[E[0]][E[1]][E[2]][E[3]] == 1 && E[0]>0 && E[1]<BufferSize)
			p1 = (E[0]*gamma12)/Delta;
			break;
		case 10:
			if (M[E[0]][E[1]][E[2]][E[3]] == 2 && E[0]>0 && E[2]<BufferSize)
			p1 =  (E[0]*gamma13)/Delta;
			break;
		case 11:
			if (M[E[0]][E[1]][E[2]][E[3]] == 3 && E[0]>0 && E[3]<BufferSize)
			p1 =  (E[0]*gamma14)/Delta;
			break;
		case 12:
			if (M[E[0]][E[1]][E[2]][E[3]] == 4 && E[1]>0 && E[0]<BufferSize)
			p1 = (E[1]*gamma21)/Delta;
			break;
		case 13:
			if (M[E[0]][E[1]][E[2]][E[3]] == 5 && E[1]>0 && E[2]<BufferSize)
			p1 = (E[1]*gamma23)/Delta;
			break;
		case 14:
			if (M[E[0]][E[1]][E[2]][E[3]] == 6 && E[1]>0 && E[3]<BufferSize)
			p1 = (E[1]*gamma24)/Delta;
			break;
		case 15:
			if (M[E[0]][E[1]][E[2]][E[3]] == 7 && E[2]>0 && E[0]<BufferSize)
			p1 = (E[2]*gamma31)/Delta;
			break;
		case 16:
			if ( M[E[0]][E[1]][E[2]][E[3]] == 8 && E[2]>0 && E[1]<BufferSize)
			p1 =  (E[2]*gamma32)/Delta;
			break;
		case 17:
			if ( M[E[0]][E[1]][E[2]][E[3]] == 9 && E[2]>0 && E[3]<BufferSize)
			p1 =  (E[2]*gamma34)/Delta;
			break;
		case 18:
			if (M[E[0]][E[1]][E[2]][E[3]] == 10 && E[3]>0 && E[0]<BufferSize)
			p1 = (E[3]*gamma41)/Delta;
			break;
		case 19:
			if ( M[E[0]][E[1]][E[2]][E[3]] == 11 && E[3]>0 && E[1]<BufferSize)
			p1 =  (E[3]*gamma42)/Delta;
			break;
		case 20:
			if ( M[E[0]][E[1]][E[2]][E[3]] == 12 && E[3]>0 && E[2]<BufferSize)
			p1 =  (E[3]*gamma43)/Delta;
			break;
		case 21:
			if( M[E[0]][E[1]][E[2]][E[3]] == 1 && E[0]>0 && E[1]<BufferSize) // 9
				 a1 = (BufferSize-E[0])*gamma12;
		    else
				 a1 = BufferSize*gamma12;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 2 && E[0]>0 && E[2]<BufferSize) // 10
				 a2 = (BufferSize-E[0])*gamma13;
		    else
				 a2 = BufferSize*gamma13;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 3 && E[0]>0 && E[3]<BufferSize) // 11
				 a3 = (BufferSize-E[0])*gamma14;
		    else
				 a3 = BufferSize*gamma14;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 4 && E[1]>0 && E[0]<BufferSize) // 12
				 a4 = (BufferSize-E[1])*gamma21;
		    else
				 a4 = BufferSize*gamma21;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 5 && E[1]>0 && E[2]<BufferSize) // 13
				 a5 = (BufferSize-E[1])*gamma23;
		    else
				 a5 = BufferSize*gamma23;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 6 && E[1]>0 && E[3]<BufferSize) // 14
				 a6 = (BufferSize-E[1])*gamma24;
		    else
				 a6 = BufferSize*gamma24;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 7 && E[2]>0 && E[0]<BufferSize) // 15
				 a7 = (BufferSize-E[2])*gamma31;
		    else
				 a7 = BufferSize*gamma31;
				 
			
			if ( M[E[0]][E[1]][E[2]][E[3]] == 8 && E[2]>0 && E[1]<BufferSize) // 16
				 a8 = (BufferSize-E[2])*gamma32;
		    else
				 a8 = BufferSize*gamma32;
				 
			
			if ( M[E[0]][E[1]][E[2]][E[3]] == 9 && E[2]>0 && E[3]<BufferSize) // 17
				 a9 = (BufferSize-E[2])*gamma34;
		    else
				 a9 = BufferSize*gamma34;
				 
			
			if (M[E[0]][E[1]][E[2]][E[3]] == 10 && E[3]>0 && E[0]<BufferSize) // 18
				 a10 = (BufferSize-E[3])*gamma41;
		    else
				 a10 = BufferSize*gamma41;
				 
			
			if ( M[E[0]][E[1]][E[2]][E[3]] == 11 && E[3]>0 && E[1]<BufferSize) // 19
				 a11 = (BufferSize-E[3])*gamma42;
		    else
				 a11 = BufferSize*gamma42;
				 
			
			if ( M[E[0]][E[1]][E[2]][E[3]] == 12 && E[3]>0 && E[2]<BufferSize) // 20
				 a12 = (BufferSize-E[3])*gamma43;
		    else
				 a12 = BufferSize*gamma43;
				 
			
			
			p1 =  ((BufferSize-E[0])*Mu1 +(BufferSize-E[1])*Mu2 + (BufferSize-E[2])*Mu3 + (BufferSize-E[3])*Mu4 + a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12)    /Delta;
			break;
		
    }
    return(p1);
}

void Equation(int *E, int indexevt, int *F, int *R, int ****M)
{
    F[0] = E[0]; F[1] = E[1]; F[2] = E[2]; F[3] = E[3];
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
			if (E[3]<Max[3]) { F[3]++;}
			break;
		case 5:
			if (E[0]>Min[0]) { F[0]--;}
			break;
		case 6:
			if (E[1]>Min[1]) { F[1]--;}
			break;
		case 7:
			if (E[2]>Min[2]) { F[2]--;}
			break;
		case 8:
			if (E[3]>Min[3]) { F[3]--;}
			break;
		case 9:
		    if( M[E[0]][E[1]][E[2]][E[3]] == 1 && E[0]>0 && E[1]<BufferSize)
		    {
				F[0]--; F[1]++;
			}
			break;
		case 10:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 2 && E[0]>0 && E[2]<BufferSize)
		    {
				F[0]--; F[2]++;
			}
			break;
		case 11:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 3 && E[0]>0 && E[3]<BufferSize)
		    {
				F[0]--; F[3]++;
			}
			break;
		case 12:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 4 && E[1]>0 && E[0]<BufferSize)
		    {
				F[1]--; F[0]++;
			}
			break;
		case 13:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 5 && E[1]>0 && E[2]<BufferSize)
		    {
				F[1]--; F[2]++;
			}
			break;
		case 14:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 6 && E[1]>0 && E[3]<BufferSize)
		    {
				F[1]--; F[3]++;
			}
			break;
		case 15:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 7 && E[2]>0 && E[0]<BufferSize)
		    {
				F[2]--; F[0]++;
			}
			break;
		case 16:
		    if ( M[E[0]][E[1]][E[2]][E[3]] == 8 && E[2]>0 && E[1]<BufferSize)
		    {
				F[2]--; F[1]++;
			}
			break;
		case 17:
		    if ( M[E[0]][E[1]][E[2]][E[3]] == 9 && E[2]>0 && E[3]<BufferSize)
		    {
				F[2]--; F[3]++;
			}
			break;
		case 18:
		    if (M[E[0]][E[1]][E[2]][E[3]] == 10 && E[3]>0 && E[0]<BufferSize)
		    {
				F[3]--; F[0]++;
			}
			break;
		case 19:
		    if ( M[E[0]][E[1]][E[2]][E[3]] == 11 && E[3]>0 && E[1]<BufferSize)
		    {
				F[3]--; F[1]++;
			}
			break;
		case 20:
		    if ( M[E[0]][E[1]][E[2]][E[3]] == 12 && E[3]>0 && E[2]<BufferSize)
		    {
				F[3]--; F[2]++;
			}
			break;
		case 21:
			break;
    }
}


void InitParticuliere()
{
}
