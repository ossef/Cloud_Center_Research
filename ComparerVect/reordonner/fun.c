/*-----------------------------------------------------------*/
/* Mitrani 2011 serveur avec bloc ON/OFF sans impatience     */
/*-----------------------------------------------------------*/

/* composants */
/* 0 : population dans la file */
/* 1 : etat du controle de puissance */
/* codage 0 : OFF */
/*        1 : allume mais pas encore operationel */
/*        2 : allume, operationnel */
/* codage des evenements */
/* 1  : arrivee dans la file  */
/* 2  : service   */
/* 3  : allumage des serveurs  */
/* 4  : uniformisation loop   */

#define BufferSize 50 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure
#define AlwaysOn 20
#define OnAndOff 7
//#define UP 10
//#define DOWN 5
#define Lambda 30.0
#define Mu 1.0
//#define Nu1 0.8
//#define Nu2 0.2
#define min(a,b) (a<=b?a:b)

void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = 2;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0;
}

double Probabilite(int indexevt, int *E, double Nu1, double Nu2)
{
    double p1, Delta;
    int nbServer, inservice;    
    nbServer = AlwaysOn;
    if (E[1]==2) {nbServer += OnAndOff;}
    inservice = min(E[0], nbServer);
    Delta = 2*Lambda + Nu1 + Nu2 + 2*Mu*(AlwaysOn + OnAndOff) ;   /* sum of the rates for  uniformisation */
    switch (indexevt) {
		case 1:
			p1 = Lambda/Delta;
			break;
		case 2:
			p1 = (inservice)*Mu/Delta;
			break;
		case 3:
			p1 = Nu1/Delta;
			break;
		case 4:
			p1 =  (Mu*(AlwaysOn + OnAndOff - inservice) + Mu*(AlwaysOn + OnAndOff) + Lambda + Nu2)/Delta;
			break;
    }
    return(p1);
}

void Equation(int *E, int indexevt, int *F, int *R, int UP, int DOWN)
{
    F[0] = E[0]; F[1] = E[1];
     switch (indexevt) {
		case 1:
			if (E[0]<BufferSize) {F[0]++;}
			if ((E[0]>=UP) && (E[1]==0)) {F[1]=1;}
			break;
		case 2:
			if (E[0]>0) {F[0]--;}
			if ((F[0]==DOWN) && (E[1]>0)) {F[1]=0;}
			break;
		case 3:
			if (E[1]==1) {F[1]=2;}
			break;
		case 4:
			break;
    }
}


void InitParticuliere()
{
}
