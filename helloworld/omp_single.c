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
  

  
  //#pragma omp single nowait
  #pragma omp single
   {nthreads = omp_get_num_threads(); //one of the thread does this
   
   printf("by thread %d \n", tid);
   
   }//implicit barrier is here due to omp single command. It can be removed by using nowait construct.
   //omp_master does the same thing but executes with master thread only..it also doesnt keep the implicit barrier.
    
    printf("Hello World from thread = %d of %d \n ", tid, nthreads);

  }  /* All threads join master thread and disband */

}
