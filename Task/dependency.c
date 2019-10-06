#include <omp.h>
#include <stdio.h>

// compile it with gcc-4.9 -fopenmp dependency.c////




int main()
{
#pragma omp parallel
{

#pragma omp single 
{

int x,y,z;

printf("tid: %d\n",omp_get_thread_num());

#pragma omp task shared(x,y,z) depend( out: x)
{x = 2;
printf("inside task1, tid: %d\n",omp_get_thread_num());
}

#pragma omp task shared(x,y,z) depend( in: x) depend( out: y)
{
y = x+2;
printf("inside task2, tid:%d\n",omp_get_thread_num());
printf("y: %d\n",y);
}

#pragma omp task shared(x,y,z) depend( in: x) depend( out: z)
{
z = x+4;
printf("inside task3, tid:%d\n",omp_get_thread_num());
printf("z: %d\n",z);
}


#pragma omp task shared(x,y,z) depend( in: y,z)
{
printf("inside task4, tid:%d\n",omp_get_thread_num());
printf("y: %d, z: %d\n",y,z);


}




}



}


return 0;

}
