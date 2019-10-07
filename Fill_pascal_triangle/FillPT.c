//compile as gcc-4.9 -fopenmp main.c FillPT.c


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "main.h"
extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j,
int value ) ;

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{
int i, j ;
for( i = 0 ; i<MAXDIM ; i++ )
for( j = 0 ; j<MAXDIM ; j++ )
{
int value = 0 ;
// Compute the value of the i, j th entry. Use tasks as appropriate
#pragma omp task depend(in: arr[i-1][j-1],arr[i-1][j]) depend( out: arr[i][j])
{
if(j==0 || j==i)
value = 1;

else
value = arr[i-1][j-1]+arr[i-1][j];

}






// Update the entry in the table using the function PTUpdateEntry

PTUpdateEntry( arr, i, j, value ) ;
}
}









