#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- programme qui prend en enrée un fichier .sz,.cd,.pi , puis copie les états et la distribution associé, puis génére le un fichier modéle .out, afin de générer un diagrame de temperature----*/


int main()
{
  
 
 FILE *fslbsz,*fslbcd,*fslbpi,*flbsz,*flbcd,*flbpi,*fout;

 int i,n1,n,m,N1,N2,N;
 long double pi1,pi2,s1,s2,s3,s4;
 s1 = s2 = s3 = s4 = 0;

 fslbsz = fopen("SLB-mod-50.sz","r");
 if(fslbsz == NULL)
 exit(2);

 fslbpi = fopen("SLB-mod-50.pi","r");
 if(fslbpi == NULL)
 exit(2);

 fslbcd = fopen("SLB-mod-50.cd","r");
 if(fslbcd == NULL)
 exit(2);
 
 flbsz = fopen("LB-mod-50.sz","r");
 if(flbsz == NULL)
 exit(2);

 flbpi = fopen("LB-mod-50.pi","r");
 if(flbpi == NULL)
 exit(2);

 flbcd = fopen("LB-mod-50.cd","r");
 if(flbcd == NULL)
 exit(2);
 
 fout = fopen("Resultat.out","w");
 if(fout == NULL)
 exit(2);

 

 fscanf(fslbsz,"%d",&n1);
 fscanf(fslbsz,"%d",&n);

 fscanf(flbsz,"%d",&n1);
 fscanf(flbsz,"%d",&N);

 if(n == N)
 {
		 for(i=0;i<n;i++)
		 {
			fscanf(fslbcd,"%d %d %d",&m,&N1,&N2);
			fscanf(fslbpi,"%Le",&pi1);
			fscanf(flbcd,"%d %d %d",&m,&N1,&N2);
			fscanf(flbpi,"%Le",&pi2);
			fprintf(fout,"%12d %12d   			 %.18Le   			 %.18Le   			 %.18Le\n", N1, N2,pi1,pi2,pi1-pi2);
			if(pi1>pi2)
				printf("(%d,%d) \n",N1,N2);
			if(N1 ==0 )
				{
					s1+= pi1; 
					s2+= pi2;
				}
			if(N2 ==0 )
			{
				s3+= pi1;
				s4+= pi2;
			}

		 } // %.18Le   			 %.18Le   			 %.18Le
		 printf( "s1 = %.18Le et s2 = %.18Le \n s3 = %.18Le et s4 = %.18Le \n",s1,s2,s3,s4);
}
 
  
			
	fclose(fslbsz);
	fclose(fslbcd);
	fclose(fslbpi);
	fclose(flbsz);
	fclose(flbcd);
	fclose(flbpi);
	fclose(fout);
	
  return 0;
}
