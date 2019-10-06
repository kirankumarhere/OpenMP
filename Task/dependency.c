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

#pragma omp task shared(x,y,z) depend( out: x) //gets dependent on previous task if it has x in out/in/inout dependency..
{x = 2;
printf("inside task1, tid: %d\n",omp_get_thread_num());
}

#pragma omp task shared(x,y,z) depend( in: x) depend( out: y) //gets dependent on previous task if it has x in out/inout and y in out/in/inout dependency..
{
y = x+2;
printf("inside task2, tid:%d\n",omp_get_thread_num());
printf("y: %d\n",y);
}

#pragma omp task shared(x,y,z) depend( in: x) depend( out: z)  //gets dependent on previous task if it has x in out/inout and z in out/in/inout dependency..
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
