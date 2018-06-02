#include <stdio.h>
#include <stdint.h>

#include <cuda/cuda_runtime.h>
#include <cuda/cublas_v2.h>

#define MATRIX_EDGE_SIZE 5000 

cublasHandle_t handle;

/*
 * Allocate memory for m * n sized matrix.
 */
float *
matrix_alloc(uint32_t m, uint32_t n)
{
	float *matrix;

	cudaMallocManaged(&matrix, m * n * sizeof(cuComplex));

	return matrix;
}

/*
 * Fill the matrix with numbers. Not random at all.
 */
void
matrix_fill(float *matrix, uint32_t m, uint32_t n)
{
	matrix[0] = 10;
	matrix[1] = 10;
}

/*
 * Multiply matrices.
 */
float *
matrix_multiply(float *a, float *b, uint32_t m, uint32_t n)
{
	float *c;

	float alpha, beta;
       
	alpha = 1.0f;
	beta = 1.0f;	

	c = matrix_alloc(m, n);

	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
	    MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE, &alpha, a, MATRIX_EDGE_SIZE, b, MATRIX_EDGE_SIZE, &beta, c, MATRIX_EDGE_SIZE);

	cudaDeviceSynchronize ();

	return c;
}

int
main()
{
	float *a, *b, *c;
	uint32_t i, j, k;


	a = matrix_alloc(MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE);
	b = matrix_alloc(MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE);
	matrix_fill(a, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE);
	matrix_fill(b, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE);

	cublasCreate (&handle);

	c = matrix_multiply(a, b, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE);

	i = 0; k = 0;
	for (j = 0; j < 5; j++) {
		k = j * MATRIX_EDGE_SIZE;
		for (i = 0; i < 5; i++) {
			printf("%.2f\t", c[k]);
			k++;
		}
		printf("\n");
	}

	cudaFree(a);
	cudaFree(b);
	cudaFree(c);

	return 0;
}

