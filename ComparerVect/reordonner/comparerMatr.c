#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define epsilon 0.0000000000000000001
#define Version 1  // 1 pour la comparaison St état par état 
	            
	              
long double *t1;
long double *t2;	
int n;			 

void affiche_tabs(int ii1)
{
printf("Affiche ligne %d [",ii1);
for(int i=0;i<n;i++)
	 {
		 printf("%.10Le -",t1[i]);
	 }
printf("]\n");

/*printf("[");
for(int i=0;i<n;i++)
	 {
		 printf("%.10Le -",t2[i]);
	 }
printf("]");	*/
}


void alloc_tabs()
{
t1 = calloc(n , sizeof(*t1));
t2 = calloc(n , sizeof(*t2));	
}

void init_tabs()
{
	for(int i=0;i<n;i++)
	 {
		 t1[i] = t2[i] = 0;
	 }
	
}				 

void comparerVect_st(int ii1)
{
long double s1,s2;
s1 = s2 =0;

 for(int i=n-1;i>=0;i--)
 {
      s1 += t1[i];
	  s2 += t2[i];
	  if(s1>1) {printf("hmm s1 = %.10Le \n",s1); s1=1;}
	  if(s2>1) {printf("hmm s2 = %.10Le \n",s2); s2=1;}
		 if( s1<s2 & fabs(s1-s2)<epsilon ) // s1<s2 pour tri6 // s1<s2 & fabs(s1-s2)<epsilon pour trier5
		 {
			 affiche_tabs(ii1);
			 printf("pas d'ordre st voir ligne %d : s1 = %.10Le et s2 = %.10Le et s1 - s2 = %.10Le  \n",ii1,s1,s2,s1-s2);
			 exit(1);
		 }
 }
 printf("\n ligne %d : Je passe s1 = %.10Le et s2 = %.10Le \n",ii1,s1,s2);
}	
	


int main()
{
  
 
 FILE *fV1Rii,*fV2Rii,*fV1sz,*fV2sz;
 
 long double s1,s2;
 int i,j,n1,m1,m;
 
 fV1Rii = fopen("mod70-V1.lexico.Rii","r");
 if(fV1Rii == NULL)
 exit(2);

 fV1sz = fopen("mod70-V1.lexico.sz","r");
 if(fV1sz == NULL)
 exit(2);

 fV2Rii = fopen("mod70-V2.lexico.Rii","r");
 if(fV2Rii == NULL)
 exit(2);
 
 fV2sz = fopen("mod70-V2.lexico.sz","r");
 if(fV2sz == NULL)
 exit(2);

 

 fscanf(fV1sz,"%d",&n1);
 fscanf(fV1sz,"%d",&n);
 printf("n = %d \n",n);
 fscanf(fV2sz,"%d",&m1);
 fscanf(fV2sz,"%d",&m);
 printf("m = %d \n",m);
 
if(Version == 1) // comparaison St : v1<v2 alors ??  
{
  int d1,d2,i1,i2,ii1,ii2;
 
  long double s1,s2,p1,p2;
  
 alloc_tabs();
 
 for(i=0;i<n;i++)
	 {
		init_tabs();
		fscanf(fV1Rii,"%d %d ",&ii1,&d1);
		fscanf(fV2Rii,"%d %d ",&ii2,&d2);
		s1 = s2 = 0;
		for(j=0;j<d1;j++)
		{ 
			 fscanf(fV1Rii,"%Le %d",&p1,&i1);
			 t1[i1] = p1;
			 fscanf(fV2Rii,"%Le %d",&p2,&i2);
			 t2[i2] = p2;	 
	    }
	    //affiche_tabs(ii1);
	   comparerVect_st(ii1);
    }
printf("\n V1<V2 alors on a l'ordre P1 >st P2 !! \n");
}

			

	fclose(fV1Rii);
	fclose(fV2Rii);
	fclose(fV1sz);
	fclose(fV2sz);
	
  return 0;
}
