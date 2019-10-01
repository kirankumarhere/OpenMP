#include <omp.h>
#include <stdio.h>

#define SIZE 500
int a[SIZE];
int b[SIZE];

int main (int argc, char *argv[]) 
{

int i;
double t1,t2;

int p=0; //p is dot product.

for( i=0;i<SIZE;i++)
{
a[i]=1;
b[i]=2;
}

t1 = omp_get_wtime(); //start time...

#pragma omp parallel default(shared)
{
//#pragma omp for reduction(+:p) schedule(static)....
#pragma omp for reduction(+:p) schedule(dynamic,50)
for( i=0;i<SIZE;i++)
p+= a[i]*b[i];
}

t2 = omp_get_wtime();

printf("dot product = %d, time: %g \n", p,t2-t1);
return 0;
}


