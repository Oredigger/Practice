#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct mat
{
	int row, col;
	double **elem;
} mat_t;

// Matrix initialization and extractions
mat_t *init(int, int);
mat_t *get_v_col(mat_t *, int);
mat_t *get_v_row(mat_t *, int);

// Matrix operations
mat_t *mat_mult(mat_t *, mat_t *);
mat_t *mat_transpose(mat_t *);

// Linear algebra
int    lu_fact(mat_t **, mat_t **, mat_t *);
mat_t *inv(mat_t *);

// Cleanup
void free_mat(mat_t *);

// Diagnostics
void print_mat(mat_t *);

#endif
