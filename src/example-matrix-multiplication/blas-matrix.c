#include <stdio.h>

#if USE_CBLAS

/* on macOS build with -framework Accelerate */
#if __APPLE__
#include <Accelerate/Accelerate.h>
#elif __linux__
#include <cblas.h>
#endif

#endif

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

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5000, 5000, 5000,
	    1.0f, a, 5000, b, 5000, 1.0f, c, 5000);

	return c;
}

int
main()
{
	float *a, *b, *c;
	uint32_t i, j, k;


	a = matrix_alloc(5000, 5000);
	b = matrix_alloc(5000, 5000);
	matrix_fill(a, 5000, 5000);
	matrix_fill(b, 5000, 5000);
	c = matrix_multiply(a, b, 5000, 5000);

	i = 0; k = 0;
	for (j = 0; j < 5; j++) {
		k = j * 5000;
		for (i = 0; i < 5; i++) {
			printf("%.2f\t", c[k]);
			k++;
		}
		printf("\n");
	}

	return 0;
}

