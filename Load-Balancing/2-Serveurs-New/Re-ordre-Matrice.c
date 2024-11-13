#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "math.h"

#define Buffer 20
#define DEBUG 0

void afficherEtats(int *t1,int *t2,int *t3,int n)
{
	printf("[\n");
		for(int i=0;i<n;i++)
		printf("%d  %d  %d \n",t1[i],t2[i],t3[i]);
	printf("] \n");
}

void TrierEtats(int *t1,int *t2,int *t3,int n) //5 éme tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1>Y2
{

 int i,tmp1,tmp2,tmp3;
 int en_desordre =1;
	
 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if( fabs(t2[i] - t3[i]) <  fabs(t2[i+1] - t3[i+1]) )  // (t2[i]>t2[i+1]) || (t2[i] == t2[i+1] && t3[i]>t3[i+1])  )
		{
			tmp1 = t1[i+1];
			t1[i+1] = t1[i];
			t1[i] = tmp1;

			tmp2 = t2[i+1];
			t2[i+1] = t2[i];
			t2[i] = tmp2;

			tmp3 = t3[i+1];
			t3[i+1] = t3[i];
			t3[i] = tmp3;

			en_desordre = 1;
		}
	}

  }
  
}


int Rechercher(int *I,int e,int n)
{
for(int i=0;i<n;i++)
	 {
		if (I[i] == e)
		return i; 	 
     }		
}

void OrdonnerMatrice(FILE *frii,int *I,char s[100],char rii[100],int n)
{
FILE *friiout;
char  riiout[100];
int i,j,c;
int t=0;

strcpy(riiout,s);
strcat(riiout,"-reordre.Rii");

friiout = fopen(riiout,"w");
if(friiout == NULL)
 exit(2);


int iter,degre,e,k,arret;
long double proba;
c= 0;

while(c <n)
 {
	for(i=0;i<n;i++)
	 {
		fscanf(frii,"%d %d",&iter,&degre);
		if(iter == I[c])
		 {
			  fprintf(friiout,"%12d %12d ",t++,degre);
			  for(j=0;j<degre;j++)
			  {
				fscanf(frii,"%Le %d",&proba,&e);
				fprintf(friiout,"% .15LE%12d",proba,Rechercher(I,e,n)); // recherche le nouvel emplacement de l'etats
			  }
				fprintf(friiout,"\n");
			c++;	
		 }
		 else
		 {
			   for(j=0;j<degre;j++)
				fscanf(frii,"%Le %d",&proba,&e);
		 }
	 }
	  fseek( frii, 0, SEEK_SET );
	 //frii=fopen(rii,"r");
 }
 
 fclose(friiout);	
}

FILE* Open_file(char s[100])
{ 
	FILE *f = fopen(s,"w");
	if(f == NULL)
	exit(2);
	
	return f;
}


void Decoupage_NCD(int t1[40000],int t2[40000],int t3[40000],char s[100],long double seuil, int deadline,int n)
{
int i,j,e,degre,c,c1,t,iter,degree,bool;
long double proba;
FILE *fA1,*fA2,*fA3,*fRiiOrd;  //Sous Matrice Nord-Ouest : Matrice A
FILE *fAps1,*fAps2,*fAps3;	   //Sous Matrice Nord-Est	 : Matrice Epsilon1
char sa1[100], sa2[100], sa3[100],s4[100];
char saps1[100], saps2[100], saps3[100];
FILE *fB1,*fB2,*fB3;		   //Sous Matrice Sud-Est 	 : Matrice B
FILE *fBps1,*fBps2,*fBps3; 		//Sous Matrice Sud-Ouest : Matrice Epsilon 2
char sb1[100], sb2[100], sb3[100];
char sbps1[100], sbps2[100], sbps3[100];


bool = 1;

     strcpy(sa1,s); 
	 strcpy(sa2,s);
	 strcpy(sa3,s);
	 strcpy(saps1,s); 
	 strcpy(saps2,s);
	 strcpy(saps3,s);
	 strcpy(s4,s); 
	 
	 strcpy(sb1,s); 
	 strcpy(sb2,s);
	 strcpy(sb3,s);
	 strcpy(sbps1,s); 
	 strcpy(sbps2,s);
	 strcpy(sbps3,s);

  	 strcat(sa1,"-reordre.NO.sz"); // On concatène chaine2 dans chaine1
  	 strcat(sa2,"-reordre.NO.cd"); 
  	 strcat(sa3,"-reordre.NO.Rii"); 
  	 strcat(saps1,"-reordre.NE.sz"); 
	 strcat(saps2,"-reordre.NE.cd");
	 strcat(saps3,"-reordre.NE.Rii");
	 strcat(s4,"-reordre.Rii");
	 
	 strcat(sb1,"-reordre.SE.sz"); // On concatène chaine2 dans chaine1
  	 strcat(sb2,"-reordre.SE.cd"); 
  	 strcat(sb3,"-reordre.SE.Rii"); 
  	 strcat(sbps1,"-reordre.SO.sz"); 
	 strcat(sbps2,"-reordre.SO.cd");
	 strcat(sbps3,"-reordre.SO.Rii");
	 
	 fA1 = Open_file(sa1);
	 fA2 = Open_file(sa2);
	 fA3 = Open_file(sa3);
	 fAps1 = Open_file(saps1);
	 fAps2 = Open_file(saps2);
	 fAps3 = Open_file(saps3);
	 
	 fB1 = Open_file(sb1);
	 fB2 = Open_file(sb2);
	 fB3 = Open_file(sb3);
	 fBps1 = Open_file(sbps1);
	 fBps2 = Open_file(sbps2);
	 fBps3 = Open_file(sbps3);
	 
	 fRiiOrd = fopen(s4,"r");
	 if(fRiiOrd==NULL)
	 exit(2);
	 
	 c = c1 = 0;
	 
	 for(i=0;i<n;i++)
	 {
		  if(t3[i] == 0)
			  {
				 fprintf(fA2,"%12d %12d %12d %12d \n",i,t1[i],t2[i],t3[i]);
				 fprintf(fAps2,"%12d %12d %12d %12d \n",i,t1[i],t2[i],t3[i]);
					if( t1[i]>seuil*Buffer || t2[i] == deadline )
						c1++;
				 c++; 
			  } 
		  else
			  {
				fprintf(fB2,"%12d %12d %12d %12d \n",i,t1[i],t2[i],t3[i]);
				fprintf(fBps2,"%12d %12d %12d %12d \n",i,t1[i],t2[i],t3[i]);  
			  }
	 }
	 printf("c = %d et c1 = %d \n",c,c1);
	 fprintf(fA1,"%12d \n%12d \n%12d \n", c1 + (c-c1)*(NbEvtsPossibles-1),c,NEt);	 
	 fprintf(fAps1,"%12d \n%12d \n%12d \n",c - c1,c,NEt);	
	 
	 fprintf(fB1,"%12d \n%12d \n%12d \n", c1 + (c-c1)*(NbEvtsPossibles-1),c,NEt);	 
	 fprintf(fBps1,"%12d \n%12d \n%12d \n",c - c1,c,NEt);	

/*-------------- Generation de la Matrice A et la Matrice Epsilon1 -------------*/	 

	 //for(i=0;i<c-c1;i++)
	 for(i=0;i<c;i++)
	 {
				fscanf(fRiiOrd,"%d %d",&iter,&degre);
				fprintf(fA3,"%12d %12d ",i,degre-1);
				fprintf(fAps3,"%12d %12d",i,bool);
					  for(j=0;j<degre;j++)
					  {
							fscanf(fRiiOrd,"%Le %d",&proba,&e);
							if(e<c)
							fprintf(fA3,"% .15LE%12d",proba,e); 
							else
							fprintf(fAps3,"% .15LE%12d",proba,e);
					  }
					  fprintf(fA3,"\n");	
					  fprintf(fAps3,"\n");	
	 }
	 
	 /*for(i=c-c1;i<c;i++) // la partie ou il y'a que des 1
	 {
				fscanf(fRiiOrd,"%d %d",&iter,&degre);
				fprintf(fA3,"%12d %12d ",i,bool);
				fprintf(fAps3,"%12d %12d",i,1-bool);
				
				fscanf(fRiiOrd,"%Le %d",&proba,&e);
				fprintf(fA3,"% .15LE%12d",proba,e); 
				fprintf(fA3,"\n");		
				fprintf(fAps3,"\n");	
	 }*/
	 
/*------------ Generation de la Matrice B et la matrice Epsilon2 --------------*/
	//for(i=c;i<c+(c-c1);i++) 
	for(i=c;i<2*c;i++)
	 {
				fscanf(fRiiOrd,"%d %d",&iter,&degre);
				fprintf(fBps3,"%12d %12d ",i,bool);
				fprintf(fB3,"%12d %12d",i-c,degre-1);
				
					  for(j=0;j<degre;j++)
					  {
							fscanf(fRiiOrd,"%Le %d",&proba,&e);
							if(e<c)
							fprintf(fBps3,"% .15LE%12d",proba,e); 
							else
							fprintf(fB3,"% .15LE%12d",proba,e-c);
					  }
					  fprintf(fB3,"\n");	
					  fprintf(fBps3,"\n");	
	 }
	 
	 /*for(i=c+(c-c1);i<2*c;i++) // (2*c =n) la partie ou il y'a que des 1
	 {
				fscanf(fRiiOrd,"%d %d",&iter,&degre);
				fprintf(fBps3,"%12d %12d",i,1-bool);
				fprintf(fB3,"%12d %12d ",i-c,bool);
				
				fscanf(fRiiOrd,"%Le %d",&proba,&e);
				fprintf(fB3,"% .15LE%12d",proba,e-c); 
				fprintf(fB3,"\n");		
				fprintf(fBps3,"\n");	
	 }*/
}

int main(int argc, char *argv[])
{
  
 
 FILE *fcd,*fsz,*fpi,*friiout,*fszout,*fcdout,*frii;
 char sz[100], cd[100], rii[100],szout[100], cdout[100];
 /*int I[40000];
 int X[40000];
 int H[40000];
 int M[40000];*/
 int *I,*X1,*X2;
 long double proba,seuil;

 int i,n1,n2,n; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 2)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./reordonner model50 \n");
 	exit(1);
 }
	 
	 
	 
	 strcpy(sz,argv[1]); 
	 strcpy(cd,argv[1]);
	 strcpy(rii,argv[1]);
	 strcpy(szout,argv[1]); 
	 strcpy(cdout,argv[1]);
	 
	


  	 strcat(sz,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cd,".cd");
  	 strcat(rii,".Rii");
  	 strcat(szout,"-reordre.sz"); 
	 strcat(cdout,"-reordre.cd");


   

 fsz = fopen(sz,"r");
 if(fsz == NULL)
 exit(2);


 fcd = fopen(cd,"r");
 if(fcd == NULL)
 exit(2);


 frii = fopen(rii,"r");
 if(frii == NULL)
 exit(2);


 fszout = fopen(szout,"w");
 if(fszout == NULL)
 exit(2);

 
 fcdout = fopen(cdout,"w");
 if(fcdout == NULL)
 exit(2);


/*-------------------- Lecture du fichier ".sz" et ecriture dans ".reorder.sz" --------------*/

 fscanf(fsz,"%d",&n1);
 fscanf(fsz,"%d",&n);
 fscanf(fsz,"%d",&n2);
 printf("n = %d \n",n);
 fprintf(fszout,"%12d \n%12d \n%12d \n",n1,n,n2);

 fclose(fsz);
 fclose(fszout);
 
 
/*-------------------- Lecture du fichier ".cd" -----------------*/

I = calloc(n,sizeof(int));
X1 = calloc(n,sizeof(int));
X2 = calloc(n,sizeof(int));


for(i=0;i<n;i++)
 {
	fscanf(fcd,"%d %d %d",&I[i],&X1[i],&X2[i]);
 }
 
 fclose(fcd);


if(DEBUG == 1)
{
  printf("Avant trie :\n");
  afficherEtats(I,X1,X2,n);
}

/*------------------ Tri des états !! ----------------------------*/

  TrierEtats(I,X1,X2,n);


if(DEBUG == 1)
{  
  printf("\n Aprés trie :\n");
  afficherEtats(I,X1,X2,n);
}

/*-----------------Ecriture du nouveau fichier reorder.cd .........*/

  for(i=0;i<n;i++)
	fprintf(fcdout,"%12d %12d %12d \n",i,X1[i],X2[i]);
  fclose(fcdout);

/*---------------- Re ordonner et ecriture de la nouvel matrice ".reorder.Rii" !! -----*/
 
  OrdonnerMatrice(frii,I,argv[1],rii,n); 
  //Decoupage_NCD(X,H,M,argv[1],seuil,deadline,n);
 

  
 

	fclose(frii);
	
	
	
  return 0;
}
