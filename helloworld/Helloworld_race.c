#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) 
{
int nthreads, tid;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel 
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();

  printf("Hello World from thread = %d\n", tid); //race condition happens in some execution
  

  }  

}
