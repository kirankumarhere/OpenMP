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
int psum=0;
int start,end;
n = omp_get_num_threads();

printf("\n before omp for: address of psum is %p \n",&psum);///psum address printed for the first time..




#pragma omp for
for(i=0;i<SIZE;i+=STEP_SIZE)
{
start= i; 
end = i+STEP_SIZE-1;

int t;
t=omp_get_thread_num();

printf("\n inside omp for: address of n is %p...tid: %d \n",&n,t);///n's address printed for the first time..

//printf("\ntask activated: sum from %d to %d, from thread %d of %d\n",start,end,t,n);

printf("\n inside omp for: address of psum is %p...tid: %d \n",&psum,t); //this psum has the same address as the psum address printed before for..

#pragma omp task shared(n)
{

//printf("\ntask computing: sum from %d to %d, from thread %d of %d\n",start,end,omp_get_thread_num(),n);

printf("\n inside task: address of n is %p...tid: %d \n",&n,t);///has the same address as the previous n..as it has shared scope inside task..

printf("\n inside task: address of psum is %p...tid: %d\n",&psum,omp_get_thread_num()); //this psum is newly created for the task..it has firstprivate scope by default. so it shows a different address from the previous psum declared before the task..

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


