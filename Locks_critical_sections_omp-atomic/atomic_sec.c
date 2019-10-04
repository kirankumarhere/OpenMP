#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define INP_SIZE (1<<26)
#define HIST_SIZE (1<<20)
int hist[HIST_SIZE];
int inp[INP_SIZE];

omp_lock_t lock[HIST_SIZE]; //declaring locks//

int main (int argc, char *argv[]) 
{
int i;
int sum = 0,key;
double t1,t2;

//initialize locks..
for( i=0;i<HIST_SIZE;i++)
omp_init_lock(&lock[i]);

for( i=0;i<HIST_SIZE;i++)
hist[i]=0;

for( i=0;i<INP_SIZE;i++)
inp[i]=1;

t1 = omp_get_wtime(); //start time...

#pragma omp parallel for private(key)
for(i=0;i<INP_SIZE;i++)
{
key = inp[i];

//#pragma omp critical
//omp_set_lock(&lock[key]);


//we are trying to use this instead of critical sections and locks..to reduce delays..
#pragma omp atomic
hist[key]++;


//omp_unset_lock(&lock[key]);

}

t2 = omp_get_wtime();

for( i=0;i<HIST_SIZE;i++)
sum+= hist[i];

for( i=0;i<HIST_SIZE;i++)
omp_destroy_lock(&lock[key]);

printf("sum of array elements = %d, time: %g \n", sum,t2-t1);
return 0;
}


