#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 70
#define Version 1  // 1 pour la comparaison St état par état, en utilisant .pi
	              // 4 pour la comparaison St état par état, en utilisant .Lexico
				 //	2 pour la comparaison st avec état agreger (projection sur le nbre de clients) chaine devient : [0,1,2... BufferSize]
				 // 3 pour la comparaison st avec état agreger (projection sur l'etat des serveurs ) chaine devient : [0,1,2] 
				 // 5 pour la comparaison st avec état agreger (projection sur l'etat des serveurs ) chaine devient : [0,2,1] 
				 
void  usage()
{
	printf("usage: ./comparerVect U D \n");
	exit(1);
}


int main(int argc,char *argv[])
{
  
 
 FILE *fslb,*fslbz,*flb,*flbz,*fslbi,*flbi,*fout;
 long double t1[10250];
 long double t2[10250];
 long double s1,s2;
 int i,n1,n,m1,m;
 
 //printf("je passe 0\n");
 fslbi = fopen("mod50-V1.lexico.Rii","r");
 if(fslbi == NULL)
 exit(2);
 
 //printf("je passe 2\n");
 fslb = fopen("mod50-V1.lexico.pi","r");
 if(fslb == NULL)
 exit(2);
 
 //printf("je passe 3\n");
 fslbz = fopen("mod50-V1.lexico.sz","r");
 if(fslbz == NULL)
 exit(2);
 
 //printf("je passe 4\n");
 flbi = fopen("mod50-V2.lexico.Rii","r");
 if(flbi == NULL)
 exit(2);
 
 //printf("je passe 5\n");
 flb = fopen("mod50-V2.lexico.pi","r");
 if(flb == NULL)
 exit(2);
 
 //printf("je passe 6\n");
 flbz = fopen("mod50-V2.lexico.sz","r");
 if(flbz == NULL)
 exit(2);
 
 //printf("je passe 7\n");
 

 fscanf(fslbz,"%d",&n1);
 fscanf(fslbz,"%d",&n);
 printf("n = %d \n",n);
 fscanf(flbz,"%d",&m1);
 fscanf(flbz,"%d",&m);
 printf("m = %d \n",m);
 
if(Version == 1)
{ 
	
   if (argc!=3) usage();
   int U = atoi(*(++argv));
   int D = atoi(*(++argv));
   
   fout = fopen("mod50-V1.mod50-V2.comp","a");
   if(fout == NULL)
   exit(2);
  
  for(i=0;i<n;i++)
	 {
		fscanf(fslb,"%Le",&t1[i]);
		fscanf(flb,"%Le",&t2[i]);
	 }

 /*printf("\n -------V1 -------- \n");
  for(i=0;i<n;i++)
	 {
		printf("%.18Le \n",t1[i]);
	 }
 printf("\n ------- V2 -------- \n");
 
 for(i=0;i<n;i++)
	 {
		printf("%.18Le \n",t2[i]);
	 }*/
 s1 = 0;
 s2 = 0;
 for(i=n-1;i>0;i--)
	 { 
		 
				s1 += t1[i];
				s2 += t2[i];

				if(s1 < s2)
				{
				printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d, car s1 = %.18Le < s2 = %.18Le\n",i+1,s1,s2);
				fprintf(fout,"%10d %10d 		-100\n",U,D);
				return 0;
				}
				
				
			
		}
	fprintf(fout,"%10d %10d 		+100\n",U,D);
	printf("\n Resultats : V1<V2  implique Pi1 >st Pi2 !\n");
	printf("s1 = %.18Le < s2 = %.18Le \n",s1,s2);
	fclose(fout);
}
 
if(Version == 3) // ici on a  V1<V2  et on veut Pi1 <st Pi2, 
{
  
  long double z1,z2;
  long double tab1[3];
  long double tab2[3];
  
  for(i=0;i<3;i++)
	 {
		tab1[i] = tab2[i] = 0;
	 }
 
 for(i=0;i<n;i++)
	 {
		fscanf(fslbi,"%d %d %Le",&m,&m1,&z1);
		printf("m = %d \n",m);
		tab1[m1] += z1;
		fscanf(flbi,"%d %d %Le",&m,&m1,&z2);
		tab2[m1] += z2;
	 }
 
 printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab1[i]);
		 }
  printf("]\n");
  
  printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab2[i]);
		 }
  printf("]\n");
  
  s1=s2=0;
  
  for(i=2 ;i>0; i--)
  {  
			s1 += tab1[i];
			s2 += tab2[i];

			if(s1 > s2)
			{
			printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d, car s1 = %.18Le > s2 = %.18Le\n",i+1,s1,s2);
			return 0;
			}	
		
	}
	s1 += tab1[0];
	s2 += tab2[0];
	
	printf("\n Resultats : V1<V2  implique Pi1 <st Pi2 !\n");
	printf("s1 = %.18Le et  s2 = %.18Le \n",s1,s2);
}

if(Version == 5) // ici on a  V1<V2  et on veut Pi1 >st Pi2, 
{
  
  long double z1,z2;
  long double tab1[3];
  long double tab2[3];
  long double temp;
  
  for(i=0;i<3;i++)
	 {
		tab1[i] = tab2[i] = 0;
	 }
 
 for(i=0;i<n;i++)
	 {
		fscanf(fslbi,"%d %d %Le",&m,&m1,&z1);
		printf("m = %d \n",m);
		tab1[m1] += z1;
		fscanf(flbi,"%d %d %Le",&m,&m1,&z2);
		tab2[m1] += z2;
	 }
 
 printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab1[i]);
		 }
  printf("]\n");
  
  printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab2[i]);
		 }
  printf("]\n");
  
  s1=s2=0;
  
  temp = tab1[1];
  tab1[1] = tab1[2];
  tab1[2] = temp;
  
  temp = tab2[1];
  tab2[1] = tab2[2];
  tab2[2] = temp;
  
  printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab1[i]);
		 }
  printf("]\n");
  
  printf("[");
 for(i=0;i<3;i++)
		 {
			printf("%.18Le \n",tab2[i]);
		 }
  printf("]\n");
  
  for(i=2 ;i>0; i--)
  {  
			s1 += tab1[i];
			s2 += tab2[i];

			if(s1 < s2)
			{
			printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d, car s1 = %.18Le > s2 = %.18Le\n",i+1,s1,s2);
			return 0;
			}	
		
	}
	s1 += tab1[0];
	s2 += tab2[0];
	
	printf("\n Resultats : V1<V2  implique Pi1 >st Pi2 !\n");
	printf("s1 = %.18Le et  s2 = %.18Le \n",s1,s2);
}
  
 
if(Version == 2)
{
  
  long double z1,z2;
  long double tab1[BUFFERSIZE+1];
  long double tab2[BUFFERSIZE+1];
  
  for(i=0;i<BUFFERSIZE+1;i++)
	 {
		tab1[i] = tab2[i] = 0;
	 }
 
 for(i=0;i<n;i++)
	 {
		fscanf(fslbi,"%d %d %Le",&m,&m1,&z1);
		printf("m = %d \n",m);
		tab1[m] += z1;
		fscanf(flbi,"%d %d %Le",&m,&m1,&z2);
		tab2[m] += z2;
	 }
 
 printf("[");
 for(i=0;i<BUFFERSIZE+1;i++)
		 {
			printf("%.18Le \n",tab1[i]);
		 }
  printf("]\n");
  
  printf("[");
 for(i=0;i<BUFFERSIZE+1;i++)
		 {
			printf("%.18Le \n",tab2[i]);
		 }
  printf("]\n");
  
  s1=s2=0;
  
  for(i=BUFFERSIZE+1 ;i>0; i--)
  {  
			s1 += tab1[i];
			s2 += tab2[i];

			if(s1 < s2)
			{
			printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d, car s1 = %.18Le < s2 = %.18Le\n",i+1,s1,s2);
			return 0;
			}	
		
	}
	printf("\n Resultats : V1<V2  implique Pi1 >st Pi2 !\n");
	printf("s1 = %.18Le < s2 = %.18Le \n",s1,s2);
}
  



if(Version == 4)
{ 

  
  for(i=0;i<n;i++)
	 {
		fscanf(fslbi,"%d %d %Le",&m,&m1,&t1[i]);
		fscanf(flbi,"%d %d %Le",&m,&m1,&t2[i]);
	 }

 printf("\n -------V1 -------- \n");
  for(i=0;i<n;i++)
	 {
		printf("%.18Le \n",t1[i]);
	 }
 printf("\n ------- V2 -------- \n");
 
 for(i=0;i<n;i++)
	 {
		printf("%.18Le \n",t2[i]);
	 }
 s1 = 0;
 s2 = 0;
 for(i=n-1;i>0;i--)
	 { 
		 
				s1 += t1[i];
				s2 += t2[i];

				if(s1 < s2)
				{
				printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d, car s1 = %.18Le < s2 = %.18Le\n",i+1,s1,s2);
				return 0;
				}
				
				
			
		}
	printf("\n Resultats : V1<V2  implique Pi1 >st Pi2 !\n");
	printf("s1 = %.18Le < s2 = %.18Le \n",s1,s2);
}
			
	fclose(fslb);
	fclose(fslbz);
	fclose(flb);
	fclose(flbz);
	fclose(fslbi);
	fclose(flbi);
	
  return 0;
}
