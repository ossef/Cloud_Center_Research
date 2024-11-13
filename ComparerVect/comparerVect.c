#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main()
{
  
 
 FILE *fslb,*fslbz,*flb,*flbz;
 long double t1[10250];
 long double t2[10250];
 long double s1,s2;
 int i,n1,n,m1,m;
 

 fslb = fopen("mod50-V1.ordre.Lexico.pi","r");
 if(fslb == NULL)
 exit(2);

 fslbz = fopen("mod50-V1.sz","r");
 if(fslbz == NULL)
 exit(2);

 flb = fopen("mod50-V2.ordre.Lexico.pi","r");
 if(flb == NULL)
 exit(2);

 flbz = fopen("mod50-V2.sz","r");
 if(flbz == NULL)
 exit(2);

 

 fscanf(fslbz,"%d",&n1);
 fscanf(fslbz,"%d",&n);
 printf("n = %d \n",n);
 fscanf(flbz,"%d",&m1);
 fscanf(flbz,"%d",&m);
 printf("m = %d \n",m);
 
 for(i=0;i<n;i++)
 {
	fscanf(fslb,"%Le",&t1[i]);
	fscanf(flb,"%Le",&t2[i]);
 }
 

 printf("\n -------SANS LB -------- \n");
  for(i=0;i<n;i++)
 {
	printf("%.18Le \n",t1[i]);
 }
 printf("\n ------- LB -------- \n");
 
 for(i=0;i<m;i++)
 {
	printf("%.18Le \n",t2[i]);
 }
 s1 = 0;
 s2 = 0;
 for(i=n-1;i>=0;i--)
 { 
	 
			s1 += t1[i];
			s2 += t2[i];

			if(s1 < s2)
			{
			printf("Erreur : l'ordre st n'est plus etablie , voir ligne %d\n",i);
			return 0;
			}
			
			
		
	}
	printf("\n Resultats : V1<V2  implique Pi1 >st Pi2 !\n");
			
	fclose(fslb);
	fclose(fslbz);
	fclose(flb);
	fclose(flbz);
	
  return 0;
}
