#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) 
{
int nthreads, tid;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(tid) shared(nthreads) //no need to specify shared here..by default nthreads will be shared even if not specified.
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();
  
  int i;
  

  /* Only master thread does this */
  if (tid == 0) 
  {
   nthreads = omp_get_num_threads();
   }
    
    #pragma omp barrier
    printf("Hello World from thread = %d of %d \n ", tid, nthreads);

  }  /* All threads join master thread and disband */

}
