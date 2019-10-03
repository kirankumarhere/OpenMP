#include <omp.h>
#include <stdio.h>

#define SIZE 3
int a[SIZE];


int do_sum(int start,int end)
{
int mid,x,y,res;

if(end == start)
res = a[start];

else
{
        mid = (start+end)/2;        
        
        
        printf("\nthread id: %d, sum(%d,%d)= sum(%d,%d) + sum(%d,%d)..\n",omp_get_thread_num(),start,end,start,mid,mid+1,end);
        
        #pragma omp task shared(x) //shared(x) is compulsory here...or else the value of x calculated by the task just disappers after the task..only if shared is given..it updates in old variable x rather than creating new variable x for the task.
        x = do_sum(start,mid);
        
        #pragma omp task shared(y)
        y = do_sum(mid+1,end);
        
        
        #pragma omp taskwait //waits for all the task spawned by this thread only...if we use barrier,it waits for all the tasks spawned by all the threads..thats not what we want here.
        
        //note: dont use barrier inside tasks also..code may hang..so wait for all tasks to complete...
        res = x+y;
        
}

printf("\nthread id: %d, sum(%d,%d) = %d\n",omp_get_thread_num(),start,end,res);

return res;
}


int main (int argc, char *argv[]) 
{

int i;
int sum = 0;

for( i=0;i<SIZE;i++)
a[i]=1;


#pragma omp parallel
#pragma omp single
sum = do_sum(0,SIZE-1);

printf("\nSum: %d\n",sum);


return 0;
}
