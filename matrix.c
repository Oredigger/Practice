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

mat_t *ext_col(mat_t *m_src, size_t target_col)
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

mat_t *mat_mult(mat_t *m_A, mat_t *m_B)
{
	if (!m_A || !m_B || m_A->col != m_A->row)
	{
		return NULL;
	}

	mat_t* result = init(m_A->row, m_B->col);
	if (!result)
	{
		return NULL;
	}

	for (int i = 0; i < m_A->row; i++)
	{
		for (int j = 0; j < m_A->col; j++)
		{

		}
	}
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
}
