//independent critical sections can be named to reduce delays....

#include <omp.h>
#include <stdio.h>

#define SIZE 1000000
int a[SIZE];

int main (int argc, char *argv[]) 
{

int i;
int sum = 0;
unsigned int product = 1;
double t1,t2;

for( i=0;i<SIZE;i++)
a[i]=1;

t1 = omp_get_wtime(); //start time...

#pragma omp parallel default(shared)
{

int psum=0;
int pprod=1;

#pragma omp for
for( i=0;i<SIZE;i++)
{
psum+= a[i];
pprod=pprod*a[i];

//printf("pprod in for :%d, thread no: %d\n",pprod,omp_get_thread_num());

}

#pragma omp critical(section1)
{
printf("In CS1 \n");
printf("psum :%d\n",psum);
sum+= psum;
}

#pragma omp critical(section2)
{
printf("In CS2 \n");
printf("pprod :%d\n",pprod);
product*= pprod;

}

}

t2 = omp_get_wtime();

printf("sum of array elements = %d, product of array elements = %d time: %g \n", sum,product,t2-t1);
return 0;
}


