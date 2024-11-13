#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Trier1(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1<Y2
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 long double tmp3 =0;
 int en_desordre =1;

 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if(t1[i]>t1[i+1])
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

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}

void Trier2(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1>Y2
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 long double tmp3 =0;
 int en_desordre =1;

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

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}

void Trier3(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //3 éme tri: (X1,Y1)<(X2,Y2) si Y1<Y2 ou que Y1=Y2 et X1<X2
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 long double tmp3 =0;
 int en_desordre =1;

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

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}

void Trier4(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //4 éme tri: (X1,Y1)<(X2,Y2) si Y1<Y2 ou que Y1=Y2 et X1>X2
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 long double tmp3 =0;
 int en_desordre =1;

 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if(t2[i]>t2[i+1] || (t2[i] == t2[i+1] && t1[i]<t1[i+1] ))
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

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}

void Trier5(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //6 éme tri (..,0) (..,2) (..,1) : (7,0)(6,0) ... (0,0)(10,2) ... (4,2)(10,1) ... (4,1) 
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 int compt=0;
 long double tmp3 =0;
 int en_desordre =1;
 int c,ci;


 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if(t2[i]>t2[i+1] || (t2[i] == t2[i+1] && t1[i]<t1[i+1] ))
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
  
 for(i=0;i<n;i++)
 if(t2[i] == 1)
 c++;
 
 //printf("\n c = %d \n",c);
 
 for(i=0;i<n;i++)
 if(t2[i] == 1)
 {ci = i; break;}
 //printf("\n first = %d \n",ci);
 
  
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
  
  

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}

void Trier6(int t1[10250],int t2[10250],long double t3[10250],int n, FILE *foL,FILE *foLpi) //6 éme tri (..,0) (..,2) (..,1) : (0,0)(1,0) ... (7,0)(4,2) ... (10,2)(4,1) ... (10,1) 
{

 int i =0;
 int tmp1 =0;
 int tmp2 =0;
 int compt=0;
 long double tmp3 =0;
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
  
 for(i=0;i<n;i++)
 if(t2[i] == 1)
 c++;
 
 //printf("\n c = %d \n",c);
 
 for(i=0;i<n;i++)
 if(t2[i] == 1)
 {ci = i; break;}
 //printf("\n first = %d \n",ci);
 
  
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
  
  

  for(i=0;i<n;i++)
	{
		fprintf(foL,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
		fprintf(foLpi, "%Le \n",t3[i]);
	}

}


void afficher(int t[10250],int n)
{
	printf("[");
		for(int i=0;i<n;i++)
		printf("%d - ",t[i]);
	printf("] \n");
}


int main(int argc, char *argv[])
{
  
 
 FILE *fcd,*fsz,*fpi,*foL,*foB,*foLpi;
 char sz[80], cd[80], pi[80], oB[100], oL[100],oLpi[120];
 int t1[10250];
 int t2[10250];
 long double t3[10250];
 int i,n1,n;
 
 if(argc != 2)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./reordonner mod50\n");
 	exit(1);
 }

	 strcpy(sz,argv[1]); 
	 strcpy(cd,argv[1]);
	 strcpy(pi,argv[1]);
	 strcpy(oB,argv[1]);
	 strcpy(oL,argv[1]);
	 strcpy(oLpi,argv[1]);


  	 strcat(sz,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cd,".cd");
  	 strcat(pi,".pi");
  	 strcat(oB,".ordre.Basique");
  	 strcat(oL,".ordre.Lexico");
  	 strcat(oLpi,".ordre.Lexico.pi");

   

 fsz = fopen(sz,"r");
 if(fsz == NULL)
 exit(2);

 fcd = fopen(cd,"r");
 if(fcd == NULL)
 exit(2);

 fpi = fopen(pi,"r");
 if(fpi == NULL)
 exit(2);

 foB = fopen(oB,"w");
 if(foB == NULL)
 exit(2);

 foL = fopen(oL,"w");
 if(foL == NULL)
 exit(2);

 foLpi = fopen(oLpi,"w");
 if(foLpi == NULL)
 exit(2);

 

 

 fscanf(fsz,"%d",&n1);
 fscanf(fsz,"%d",&n);
 printf("n = %d \n",n);
 
 
 
 for(i=0;i<n;i++)
 {
	fscanf(fcd,"%d %d %d",&n1,&t1[i],&t2[i]);
	fscanf(fpi,"%Le",&t3[i]);
	fprintf(foB,"%d  %d   %.18Le\n",t1[i],t2[i],t3[i]);
 }

  /*afficher(t1,n);
  afficher(t2,n);*/

  Trier2(t1,t2,t3,n,foL,foLpi);

  /*afficher(t1,n);
  afficher(t2,n);*/

  
 
	fclose(fsz);
	fclose(fcd);
	fclose(fpi);
	fclose(foB);
	fclose(foL);
	fclose(foLpi);
	
  return 0;
}
