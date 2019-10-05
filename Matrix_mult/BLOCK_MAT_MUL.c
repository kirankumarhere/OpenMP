

void Matmul(int block_size, int MATRIX_SIZE)
{
int matrix1[MATRIX_SIZE][MATRIX_SIZE];
int matrix2[MATRIX_SIZE][MATRIX_SIZE];
int calc_product[MATRIX_SIZE][MATRIX_SIZE];
//assume matrix1 and matrix2 are initialized to random vals...and calc_product is initialized to zeros.




#pragma omp parallel for collapse(2) // threads are split based on (i,j)..which means they are told to compute a block from C matrix whose start index is (i,j)..
for (int i = 0; i < MATRIX_SIZE; i += block_size)
		{
			for (int j = 0; j < MATRIX_SIZE; j += block_size)
			{
				
			for (int k = 0; k < MATRIX_SIZE; k += block_size)
			{
				//prefetching for next sub-matrices(cache blocks) of the same thread will be done here..[one from submatrices(b*b size) row of first matrix...second from submatrices(b*b size) col of second matrix] 
				
				for (int x = 0; x < block_size; ++x)
				{
					for (int y = 0; y < block_size; ++y)
					{
						for (int z = 0; z < block_size; ++z)
						{
							//#pragma omp critical..//dont think this will be needed...
							calc_product[i + x][j + y] += matrix1[i + x][k+z] * matrix2[k+z][j + y];
						}
					}
				}
			}
		}
		
		}
		
}
