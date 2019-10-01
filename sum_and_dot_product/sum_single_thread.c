#include <omp.h>
#include <stdio.h>

#define SIZE 1000000000
int a[SIZE];
int main (int argc, char *argv[]) 
{

double t1,t2;
int i,sum=0;

for( i=0;i<SIZE;i++)
a[i]=1;


t1 = omp_get_wtime();


for( i=0;i<SIZE;i++)
sum+= a[i];

t2 = omp_get_wtime();


printf("sum of array elements = %d, time: %g \n", sum,t2-t1);


return 0;
}
