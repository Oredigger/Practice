#include "matrix.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

mat_t *init(int row, int col)
{
	mat_t *m = (mat_t *) malloc(sizeof(mat_t));
	if (!m)
	{
		return NULL;
	}
		
	m->row = row;
	m->col = col;
	
	m->elements = (double **) calloc(m->row, sizeof(double *));
	if (!m->elements)
	{
		free(m);
		m = NULL;

		return NULL;
	}

	for (int i = 0; i < m->row; i++)
	{
		m->elements[i] = NULL;	
	}

	for (int i = 0; i < m->row; i++)
	{
		m->elements[i] = (double *) calloc(m->col, sizeof(double));	
		if (!m->elements[i])
		{
			free_mat(m);
		}
	}

	return m;
}

mat_t *col_vec(mat_t *m_src, int target_col)
{
	if (target_col > m_src->col + 1)
	{
		return NULL;
	}

	mat_t *m_dest = init(m_src->row, 1);
	if (!m_dest)
	{
		return NULL;
	}

	for (int i = 0; i < m_dest->row; i++)
	{
		m_dest->elements[i][0] = m_src->elements[i][target_col - 1];
	}

	return m_dest;
}

mat_t *mat_mult(mat_t *m_A, mat_t *m_B)
{
	if (!m_A || !m_B || m_A->col != m_A->row)
	{
		return NULL;
	}

	mat_t* m_result = init(m_A->row, m_B->col);
	if (!m_result)
	{
		return NULL;
	}

	for (int i = 0; i < m_A->row; i++)
	{
		for (int j = 0; j < m_B->col; j++)
		{
			double dot_prod = 0;
			
			for (int k = 0; k < m_A->col; k++)
			{
				dot_prod += m_A->elements[i][k]*m_B->elements[k][j];
			}

			m_result->elements[i][j] = dot_prod; 
		}
	}

	return m_result;
}

int lu_fact(mat_t **mat_l, mat_t **mat_u, mat_t *mat_src)
{
	int m = mat_src->row;
	int n = mat_src->col;

	*mat_l = init(m, m);
	if (!(*mat_l))
	{
		return -1;
	}

	*mat_u = init(m, n);
	if (!(*mat_u))
	{
		return -1;
	}

	// Populate mat_l and mat_u with known immediate values from mat_src based on their
	// definitions.
	for (int i = 0; i < n; i++)
	{
		(*mat_u)->elements[0][i] = mat_src->elements[0][i];
		(*mat_l)->elements[i][i] = 1;
	}

	for (int i = 1; i < m; i++)
	{
		(*mat_l)->elements[i][0] = mat_src->elements[i][0]/mat_src->elements[0][0];
	}

	for (int i = 1; i < m; i++)
	{
		// Solve unknowns in row i in mat_l
		for (int j = 1; j < i; j++)
		{
			(*mat_l)->elements[i][j] = mat_src->elements[i][j];
			
			for (int k = 0; k < j; k++)
			{
				(*mat_l)->elements[i][j] -= (*mat_l)->elements[i][k]*(*mat_u)->elements[k][j];
			}
			
			(*mat_l)->elements[i][j] = (*mat_l)->elements[i][j]/(*mat_u)->elements[j][j];
		}

		// Solve unknowns in row j in mat_u
		for (int j = i; j < n; j++)
		{
			(*mat_u)->elements[i][j] = mat_src->elements[i][j];
			
			for (int k = 0; k < i; k++)
			{
				(*mat_u)->elements[i][j] -= (*mat_l)->elements[i][k]*(*mat_u)->elements[k][j];
			}
		}
	}

	// Check for singularity in mat_l or mat_u
	for (int i = 0; i < mat_src->row; i++)
	{
		if (!(*mat_l)->elements[i][i] || !(*mat_u)->elements[i][i])
		{
			return 1;
		}
	}

	return 0;
}

static mat_t *inv_u(mat_t *m_u)
{
	if (m_u->row != m_u->col)
	{
		return NULL;
	}

	int n = m_u->col;

	mat_t *inv_m_u = init(n, n);
	if (!inv_m_u)
	{
		return NULL;
	}

	// Go through each row, one by one
	for (int i = 0; i < n - 1; i++)
	{
		inv_m_u->elements[i][i] = 1/m_u->elements[i][i];
		
		for (int j = i + 1; j < n; j++)
		{
			for (int k = 0; k < j; k++)
			{
				inv_m_u->elements[i][j] -= inv_m_u->elements[i][k]*m_u->elements[k][j];	
			} 

			inv_m_u->elements[i][j] = inv_m_u->elements[i][j]/m_u->elements[j][j];
		}
	}

	inv_m_u->elements[n - 1][n - 1] = 1/m_u->elements[n - 1][n - 1];

	return inv_m_u;
} 

static mat_t *inv_l(mat_t *m_l)
{
	if (m_l->row != m_l->col)
	{
		return NULL;
	}

	int n = m_l->col;

	mat_t *inv_m_l = init(n, n);
	if (!inv_m_l)
	{
		return NULL;
	}

	// Go through each row, one by one
	for (int i = 0; i < n; i++)
	{
		inv_m_l->elements[i][i] = 1;

		for (int j = i - 1; j >= 0; j--)
		{
			inv_m_l->elements[i][j] = -1*m_l->elements[i][j];
			for (int k = i - 1; k > j; k--)
			{
				inv_m_l->elements[i][j] -= inv_m_l->elements[i][k]*m_l->elements[k][j];	
			}
		}
	}

	return inv_m_l;
}

mat_t *inv(mat_t *m_src)
{
	if (m_src->row != m_src->col)
	{
		return NULL;
	}

	mat_t *m_l, *m_u;
	if (lu_fact(&m_l, &m_u, m_src))
	{
		free_mat(m_l);
		free_mat(m_u);

		return NULL;
	}

	mat_t *inv_m_u = inv_u(m_u);
	free_mat(m_u);

	mat_t *inv_m_l = inv_l(m_l);
	free_mat(m_l);

	mat_t *inv_m = mat_mult(inv_m_u, inv_m_l);

	free_mat(inv_m_l);
	free_mat(inv_m_u);

	return inv_m;
}

void free_mat(mat_t *m_src)
{
	if (m_src)
	{
		for (int i = 0; i < m_src->row; i++)
		{
			free(m_src->elements[i]);
			m_src->elements[i] = NULL;
		}

		free(m_src->elements);
		m_src->elements = NULL;

		free(m_src);
		m_src = NULL;
	}
}

void print_mat(mat_t *m)
{
	if (m)
	{
		for (int i = 0; i < m->row; i++)
		{
			for (int j = 0; j < m->col; j++)
			{
				printf("%f ", m->elements[i][j]);
			}
			
			printf("\n");
		}
	
		printf("\n");
	}
	else
	{
		printf("Cannot print matrix!");
	}
	
}
