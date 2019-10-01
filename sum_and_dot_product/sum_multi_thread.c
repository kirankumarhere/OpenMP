#include <omp.h>
#include <stdio.h>

#define SIZE 1000000000
int a[SIZE];

int main (int argc, char *argv[]) 
{

int i;
int sum = 0;
double t1,t2;

for( i=0;i<SIZE;i++)
a[i]=1;

t1 = omp_get_wtime(); //start time...

#pragma omp parallel default(shared)
{

int psum=0;

#pragma omp for
for( i=0;i<SIZE;i++)
psum+= a[i];

#pragma omp critical
sum+= psum;

t2 = omp_get_wtime();

}
printf("sum of array elements = %d, time: %g \n", sum,t2-t1);
return 0;
}


