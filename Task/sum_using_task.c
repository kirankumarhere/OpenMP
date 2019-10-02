#include <omp.h>
#include <stdio.h>

#define SIZE 600
#define STEP_SIZE 100
int a[SIZE];

int main (int argc, char *argv[]) 
{

int i,j;
int sum = 0,n;
double t1,t2;

for( i=0;i<SIZE;i++)
a[i]=1;


#pragma omp parallel shared(n)
{

int start,end;
n = omp_get_num_threads();

#pragma omp for
for(i=0;i<SIZE;i+=STEP_SIZE)
{
start= i; 
end = i+STEP_SIZE-1;

int t;
t=omp_get_thread_num();

printf("\ntask activated: sum from %d to %d, from thread %d of %d\n",start,end,t,n);

#pragma omp task
{
int psum=0;
printf("\ntask computing: sum from %d to %d, from thread %d of %d\n",start,end,omp_get_thread_num(),n);

for(j=start;j<=end;j++)
psum+=a[j];

#pragma omp critical
sum+=psum;
}


}
}

printf("sum of array elements = %d \n", sum);
return 0;
}


