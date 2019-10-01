#include <omp.h>
#include <stdio.h>


int main (int argc, char *argv[]) 
{

printf("omp_get_wtime: %g \n",omp_get_wtime() ); //fetches time at the point from timer...

printf("omp_get_wtick: %g \n",omp_get_wtick() ); //fetches resolution of timer...

return 0;
}
