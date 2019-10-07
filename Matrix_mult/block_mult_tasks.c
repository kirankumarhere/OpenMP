// compile it with gcc-4.9 -fopenmp "filename".c


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 4                /* number of rows in matrix A */
#define NCA 4                /* number of columns in matrix A */
#define NCB 4               /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k,x,y,z,block_size;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB],            /* result matrix C */
	t1,
	t2;           

block_size = 2;                    /* set loop iteration chunk size */

int cb[2][2]; //no of blocks in C(product matrix)// used to create task dependency

/*** Spawn a parallel region explicitly scoping all variables ***/

t1 = omp_get_wtime(); //start time...

#pragma omp parallel shared(a,b,c,cb,nthreads,block_size) private(tid,i,j,k)
  {
  
  
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (dynamic, 10) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= j;
  #pragma omp for schedule (dynamic, 10) 
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= 1;
  #pragma omp for schedule (dynamic, 10) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;
      
  #pragma omp for schedule (dynamic, 10) 
  for (i=0; i<(NRA/block_size); i++)
    for (j=0; j<(NCB/block_size); j++)
      cb[i][j]= 0;
      
      
     
#pragma omp single 
{

  /*** Do matrix multiply sharing iterations on outer loop ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  
for (i = 0; i < NRA; i += block_size)
		{
			for (j = 0; j < NCB; j += block_size)
			{
				
			 for (k = 0; k < NCA; k += block_size)
			 {
				
				int inew = (i/block_size);
				int jnew = (j/block_size);
				
				printf(" inew, jnew %d,%d\n",inew,jnew);
				
				#pragma omp task shared(a,b,c,cb,block_size) depend(out: cb[inew][jnew]) // creates order among the tasks updating the same block of product matrix..
				{
				
				
				
				//printf(" inew, jnew %d,%d\n",inew,jnew);
				printf("\ntid:%d...starting task %d for cb[%d][%d]..\n",omp_get_thread_num(),(cb[inew][jnew]+1),inew,jnew);
				for (x = 0; x < block_size; ++x)
				{
					for (y = 0; y < block_size; ++y)
					{
						for (z = 0; z < block_size; ++z)
						{
							c[i + x][j + y] += a[i + x][k+z] * b[k+z][j + y];
							//printf("Thread=%d did row=%d, col=%d\n",tid,i,j);
						} 
					}
			        }
			       printf("tid:%d...finishing task %d for cb[%d][%d]..\n\n",omp_get_thread_num(),(cb[inew][jnew]+1),inew,jnew);
			       cb[inew][jnew]++;
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
  
  
 



printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }
  
  
printf("\naccess Matrix:\n");
for (i=0; i<(NRA/block_size); i++)
  {
  for (j=0; j<(NCB/block_size); j++) 
    printf("%d   ", cb[i][j]);
  printf("\n"); 
  }  
  
return 0;
}

