#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct mat
{
	size_t row, col;
	double **elements;
} mat_t;

// Matrix operations
mat_t *init(size_t, size_t);
mat_t *ext_col(mat_t *, size_t);

// Linear algebra
void lu_fact(mat_t *, mat_t *, mat_t *);
mat_t inv_mat(mat_t *);
int is_inv(mat_t *);

void free_mat(mat_t *);
void print_mat(mat_t *);

#endif
