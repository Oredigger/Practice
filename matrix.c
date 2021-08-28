#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

mat_t *init(size_t row, size_t col)
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
		m->elements[i] = (double *) calloc(m->col, sizeof(double));	
		if (!m->elements[i])
		{
			for (int j = 0; j < i; j++)
			{
				free(m->elements[j]);
				m->elements[j] = NULL;
			}	
			
			free(m->elements);
			m->elements = NULL;

			free(m);
			m = NULL;

			return NULL;
		}
	}

	return m;
}

mat_t *col_vec(mat_t *m_src, size_t target_col)
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

void lu_fact(mat_t **mat_l, mat_t **mat_u, mat_t *mat_src)
{
	*mat_l = init(mat_src->row, mat_src->row);
	if (!(*mat_l))
	{
		return;
	}

	*mat_u = init(mat_src->row, mat_src->col);
	if (!(*mat_u))
	{
		return;
	}

	// Populate mat_l and mat_u with known immediate values from mat_src based on their
	// definitions.
	for (int i = 0; i < mat_src->col; i++)
	{
		(*mat_u)->elements[0][i] = mat_src->elements[0][i];
		(*mat_l)->elements[i][i] = 1;
	}

	for (int i = 1; i < (*mat_l)->row; i++)
	{
		(*mat_l)->elements[i][0] = mat_src->elements[i][0]/mat_src->elements[0][0];
	}

	for (int i = 1; i < mat_src->row; i++)
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
		for (int j = i; j < (*mat_u)->col; j++)
		{
			(*mat_u)->elements[i][j] = mat_src->elements[i][j];
			
			for (int k = 0; k < i; k++)
			{
				(*mat_u)->elements[i][j] -= (*mat_l)->elements[i][k]*(*mat_u)->elements[k][j];
			}
		}
	}
}

mat_t *inv_mat(mat_t *m_src)
{
	mat_t* m_inv = init(m_src->col, m_src->row);
	if (!m_inv)
	{
		return NULL;
	}

	return m_inv;
}

void free_mat(mat_t *m_src)
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

void print_mat(mat_t *m)
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
