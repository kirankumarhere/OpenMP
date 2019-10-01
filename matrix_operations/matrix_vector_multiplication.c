#include <omp.h>
#include <stdio.h>

#define SIZE 200
double a[SIZE][SIZE];
double b[SIZE];
double c[SIZE];

int main (int argc, char *argv[]) 
{

int i,j;
double t1,t2;


for(i=0;i<SIZE;i++)
for(j=0;j<SIZE;j++)
a[i][j]=20;


for(i=0;i<SIZE;i++)
{
b[i]=1;
c[i] = 0; //result
}


t1 = omp_get_wtime(); //start time...

#pragma omp parallel default(shared)
{
#pragma omp for schedule(dynamic,16)
for(i=0;i<SIZE;i++)
{
c[i] = 0;
for(j=0;j<SIZE;j++)
c[i]+= a[i][j]*b[j];
}
}


t2 = omp_get_wtime();

printf("\n"); //result

for(i=0;i<SIZE;i++)
printf(" %g ",c[i]); //result


printf("time: %g \n", t2-t1);
return 0;
}


