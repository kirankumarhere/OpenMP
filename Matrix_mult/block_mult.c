
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 500                /* number of rows in matrix A */
#define NCA 500                /* number of columns in matrix A */
#define NCB 500               /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k,x,y,z,block_size;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB],            /* result matrix C */
	t1,
	t2;           

block_size = 10;                    /* set loop iteration chunk size */

/*** Spawn a parallel region explicitly scoping all variables ***/

t1 = omp_get_wtime(); //start time...

#pragma omp parallel shared(a,b,c,nthreads,block_size) private(tid,i,j,k)
  {
  
  
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  #pragma omp for 
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  #pragma omp for 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for collapse(2) // threads are split based on (i,j)..which means they are told to compute a block from C matrix whose start index is (i,j)..
for (i = 0; i < NRA; i += block_size)
		{
			for (j = 0; j < NCB; j += block_size)
			{
				
			for (k = 0; k < NCA; k += block_size)
			{
				//prefetching for next sub-matrices(cache blocks) of the same thread will be done here..[one from submatrices(b*b size) row of first matrix...second from submatrices(b*b size) col of second matrix] 
				
				for (x = 0; x < block_size; ++x)
				{
					for (y = 0; y < block_size; ++y)
					{
						for (z = 0; z < block_size; ++z)
						{
							//#pragma omp critical..//dont think this will be needed...
							c[i + x][j + y] += a[i + x][k+z] * b[k+z][j + y];
						}
					}
				}
			}
		}
		
		}
		
    
  }   
  
  t2 = omp_get_wtime(); //end time...
  
printf("\n"); //result
printf("block size: %d \n", block_size);
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

