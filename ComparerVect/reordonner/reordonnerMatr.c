#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

void afficherEtats(int t1[10250],int t2[10250],int t3[10250],int n)
{
	printf("[\n");
		for(int i=0;i<n;i++)
		printf("%d  %d  %d\n",t3[i],t1[i],t2[i]);
	printf("] \n");
}

void TrierEtats5(int t1[10250],int t2[10250],int t3[10250],int n) //5 éme tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1>Y2
{

 int i =0;
 int tmp1,tmp2,tmp3;
 int compt=0;
 int en_desordre =1;
 int c,ci;


 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if(t1[i]>t1[i+1] || (t1[i] == t1[i+1] && t2[i]<t2[i+1] ))
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

void TrierEtats6(int t1[10250],int t2[10250],int t3[10250],int n) //6 éme tri (..,0) (..,2) (..,1) : (0,0)(1,0) ... (7,0)(4,2) ... (10,2)(4,1) ... (10,1) 
{

 int i =0;
 int tmp1,tmp2,tmp3;
 int compt=0;
 int en_desordre =1;
 int c,ci;


 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if(t2[i]>t2[i+1] || (t2[i] == t2[i+1] && t1[i]>t1[i+1] ))
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
  
 
 c = 0;
 for(i=0;i<n;i++)
 {
 if(t2[i] == 1)
 c++;
 }
 
 
 for(i=0;i<n;i++)
 if(t2[i] == 1)
 {ci = i; break;}

 
  
  for(int j=ci;j<ci+c;j++)
  {
	  tmp1 = t1[j+c];
	  t1[j+c] = t1[j];
	  t1[j] = tmp1;
	  
	  tmp2 = t2[j+c];
	  t2[j+c] = t2[j];
	  t2[j] = tmp2;
	  
	  tmp3 = t3[j+c];
	  t3[j+c] = t3[j];
	  t3[j] = tmp3;  
  }
  
}

int Rechercher(int I[10250],int e,int n)
{
for(int i=0;i<n;i++)
	 {
		if (I[i] == e)
		return i; 	 
     }		
}

void OrdonnerMatrice(FILE *frii,int I[10250],char s[100],char rii[100],int n)
{
FILE *friiout;
char  riiout[100];
int i,j,c;
int t=0;

strcpy(riiout,s);
strcat(riiout,".lexico.Riu");

 
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
				fprintf(friiout,"% .15LE%12d",proba,Rechercher(I,e,n));
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
	 frii=fopen(rii,"r");
 }
 
 fclose(friiout);
	
}



int main(int argc, char *argv[])
{
  
 
 FILE *fcd,*fsz,*fpi,*frii,*fszout,*fcdout;
 char sz[100], cd[100], rii[100],szout[100], cdout[100];
 int I[10250];
 int X[10250];
 int Y[10250];
 long double proba;
 int i,n1,n2,n; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 2)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./reordonner mod50\n");
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
  	 strcat(szout,".lexico.sz"); 
	 strcat(cdout,".lexico.cd");


   

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



 fscanf(fsz,"%d",&n1);
 fscanf(fsz,"%d",&n);
 fscanf(fsz,"%d",&n2);
 printf("n = %d \n",n);
 fprintf(fszout,"%12d \n%12d \n%12d \n",n1,n,n2);
 
 
 
 for(i=0;i<n;i++)
 {
	fscanf(fcd,"%d %d %d",&I[i],&X[i],&Y[i]);
 }

if(DEBUG == 1)
{
  printf("Avant trie :\n");
  afficherEtats(X,Y,I,n);
}
  
  TrierEtats5(X,Y,I,n);

if(DEBUG == 1)
{  
  printf("Aprés trie :\n");
  afficherEtats(X,Y,I,n);
}

  for(i=0;i<n;i++)
	fprintf(fcdout," %12d %12d %12d\n",i,X[i],Y[i]); //fprintf(fcdout," %12d %12d %12d\n",I[i],X[i],Y[i]);
  
  OrdonnerMatrice(frii,I,argv[1],rii,n);

 

  
 
	fclose(fsz);
	fclose(fcd);
	fclose(frii);
	fclose(fszout);
	fclose(fcdout);
	
	
  return 0;
}
