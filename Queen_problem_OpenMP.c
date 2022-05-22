#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 15
int col[N];
int diagP[N];
int diagN[N];    

void afficher_conf( int *col )
{  
    int i, j, k;
    for (i=0;  i<N; i++)
		printf("\t   %c", i+'a');
   	printf("\n");
	for (i=0;  i<N; i++)
		printf("\t-------");
   	printf("\n");
       for(i=1; i<=N; i++)  {
		printf("    %d", i);
		for (j=0; j<N; j++) {
			if ( j==col[i-1] ) printf("\t  R");
             else printf("\t   ");
		}
        printf("\n");
		for (k=0;  k<N; k++)
			printf("\t-------");
   		printf("\n");
}
printf("\n\n");
}

int placer(int nDames,int* col,int*diagP,int*diagN) // nDames=ligne en cours et dames restantes
{   
    int solution=0;
        
    if(nDames==N)
    {  
      /*  #pragma omp critical
        {
        afficher_conf(col);
        }*/
        return 1;}

    for(int i=0; i<N; ++i)
    {
    for(int j=0; j<nDames; ++j)
    if(col[j]==i || diagP[j]==nDames+1+i || diagN[j]==nDames+1-i) 
    goto next;
    
    col[nDames]=i;
    diagP[nDames]=nDames+1+i;
    diagN[nDames]=nDames+1-i;
    solution+=placer(nDames+1,col,diagP,diagN); 
    next: continue;
    }
    return solution;
}



    
int main(int argc, char *argv[])
{     
    int solution=0;
    double t=0;
    double tInitial=0, tFinal=0;
       
       omp_set_num_threads (N);
         tInitial=omp_get_wtime();
        #pragma omp parallel for lastprivate(col,diagP,diagN) reduction(+:solution)
        for (int i = 0; i < N; i++)
        {   
            col[0]=i;
            diagP[0]=1+i;
            diagN[0]=1-i;
            solution+=placer(1,col,diagP,diagN);

        }
        
      
       printf("\nNombre de solutions: %d\n",solution);
        tFinal=omp_get_wtime();
        t=(tFinal-tInitial);
            printf("temps = %f\n", t);
    
        return 0;
}