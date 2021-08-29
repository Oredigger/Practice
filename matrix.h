#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct mat
{
	int row, col;
	double **elements;
} mat_t;

// Matrix operations
mat_t *init(int, int);
mat_t *col_vec(mat_t *, int);
mat_t *mat_mult(mat_t *, mat_t *);

// Linear algebra
int     lu_fact(mat_t **, mat_t **, mat_t *);
mat_t   *inv(mat_t *);

// Cleanup
void free_mat(mat_t *);
void print_mat(mat_t *);

#endif
