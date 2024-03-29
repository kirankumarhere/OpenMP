
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 4                /* number of rows in matrix A */
#define NCA 4                /* number of columns in matrix A */
#define NCB 4               /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB],            /* result matrix C */
	t1,
	t2;           

chunk = 1;                    /* set loop iteration chunk size */

/*** Spawn a parallel region explicitly scoping all variables ***/
t1 = omp_get_wtime(); //start time...

#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  
  
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (dynamic, chunk) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (dynamic, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (dynamic, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (dynamic, chunk)
  for (i=0; i<NRA; i++)    
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
    
   
    
  }   
  
   t2 = omp_get_wtime(); //end time...
  
printf("\n"); //result
printf("chunk size: %d \n", chunk);
printf("time: %g \n", t2-t1);
  
  
 


/*
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }*/

return 0;
}

