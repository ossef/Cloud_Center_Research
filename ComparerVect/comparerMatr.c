#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void comparaison_ST(long double t1[50],long double t2[50], int n)
{
 long double s1,s2;
 s1 = 0;
 s2 = 0;
 for(int i=n-1;i>=0;i--)
 { 
	 
			s1 += t1[i];
			s2 += t2[i];
			if(fabs(s1 - s2) > 0.00000001)
			{
				printf("Aie Arrêt \n"); 
				exit(2);
			}
		
	}
	printf("\n yes SLB< LB !!\n");	
	
}


int main()
{
  
 
 FILE *fslb,*fslbz,*flb,*flbz;
 long double t1[50];
 long double t2[50];

 int i,n1,n,m1,m;
 

 fslb = fopen("SLB-mod-50.Rii","r");
 if(fslb == NULL)
 exit(2);

 fslbz = fopen("SLB-mod-50.sz","r");
 if(fslbz == NULL)
 exit(2);

 flb = fopen("LB-mod-50.Rii","r");
 if(flb == NULL)
 exit(2);

 flbz = fopen("LB-mod-50.sz","r");
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
 }
 
  for(i=0;i<m;i++)
 {
	fscanf(flb,"%Le",&t2[i]);
 }

  for(i=0;i<n;i++)
 {
	printf("%.18Le \n",t1[i]);
 }
 printf("\n -------HOUBA-------- \n");
 
 for(i=0;i<m;i++)
 {
	printf("%.18Le \n",t2[i]);
 }
 
 comparaison_ST(t1,t2,n);
			
	fclose(fslb);
	fclose(fslbz);
	fclose(flb);
	fclose(flbz);
	
  return 0;
}
