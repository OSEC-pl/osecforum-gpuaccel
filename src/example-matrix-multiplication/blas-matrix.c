#include <stdio.h>

/* on macOS build with -framework Accelerate */
#if __APPLE__
#include <Accelerate/Accelerate.h>
#elif __linux__
#include <cblas.h>
#endif

#define MATRIX_EDGE_SIZE 5000

/*
 * Allocate memory for m * n sized matrix.
 */
float *
matrix_alloc(uint32_t m, uint32_t n)
{
	float *matrix = malloc(sizeof(float) * m * n); 
	return matrix;
}

/*
 * Fill the matrix with numbers. Not random at all.
 */
void
matrix_fill(float *matrix, uint32_t m, uint32_t n)
{
	uint32_t i, j;
	float f;

	i = 0, j = 0, f = 0;

	matrix[0] = 10;
	matrix[1] = 10;
	// for...	
}

/*
 * Multiply matrices.
 */
float *
matrix_multiply(float *a, float *b, uint32_t m, uint32_t n)
{
	float *c;

	c = matrix_alloc(m, n);

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE, MATRIX_EDGE_SIZE,
	    1.0f, a, MATRIX_EDGE_SIZE, b, MATRIX_EDGE_SIZE, 1.0f, c, MATRIX_EDGE_SIZE);

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

	return 0;
}

