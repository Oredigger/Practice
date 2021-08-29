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
	
	m->elem = (double **) calloc(m->row, sizeof(double *));
	if (!m->elem)
	{
		free(m);
		m = NULL;

		return NULL;
	}

	for (int i = 0; i < m->row; i++)
	{
		m->elem[i] = NULL;	
	}

	for (int i = 0; i < m->row; i++)
	{
		m->elem[i] = (double *) calloc(m->col, sizeof(double));	
		if (!m->elem[i])
		{
			free_mat(m);
		}
	}

	return m;
}

mat_t *get_v_col(mat_t *m_src, int target_col)
{
	int m = m_src->row;
	int n = m_src->col;

	if (target_col > n || target_col < 0)
	{
		return NULL;
	}

	mat_t *m_col = init(m, 1);
	if (!m_col)
	{
		return NULL;
	}

	for (int i = 0; i < m; i++)
	{
		m_col->elem[i][0] = m_src->elem[i][target_col];
	}

	return m_col;
}

mat_t *get_v_row(mat_t *m_src, int target_row)
{
	int m = m_src->row;
	int n = m_src->col;

	if (target_row > m || target_row < 0)
	{
		return NULL;
	}

	mat_t *m_row = init(1, n);
	if (!m_row)
	{
		return NULL;
	}

	for (int i = 0; i < m; i++)
	{
		m_row->elem[0][i] = m_src->elem[target_row][i];
	}

	return m_row;
}


mat_t *mat_mult(mat_t *m_A, mat_t *m_B)
{
	if (!m_A || !m_B || m_A->col != m_A->row)
	{
		return NULL;
	}

	mat_t *m_result = init(m_A->row, m_B->col);
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
				dot_prod += m_A->elem[i][k]*m_B->elem[k][j];
			}

			m_result->elem[i][j] = dot_prod; 
		}
	}

	return m_result;
}

mat_t *mat_transpose(mat_t *m_A)
{
	int m = m_A->col;
	int n = m_A->row;

	mat_t *m_transpose = init(m, n);
	if (!m_transpose)
	{
		return NULL;		
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m_transpose->elem[i][j] = m_A->elem[j][i];
		}
	}

	return m_transpose;
}

int lu_fact(mat_t **m_l, mat_t **m_u, mat_t *m_src)
{
	int m = m_src->row;
	int n = m_src->col;

	*m_l = init(m, m);
	if (!(*m_l))
	{
		return -1;
	}

	*m_u = init(m, n);
	if (!(*m_u))
	{
		return -1;
	}

	for (int i = 0; i < m; i++)
	{
		// Populate mat_l and mat_u with known immediate values from mat_src based on their
		// definitions.
		(*m_u)->elem[0][i] = m_src->elem[0][i];
		(*m_l)->elem[i][i] = 1;
		(*m_l)->elem[i][0] = m_src->elem[i][0]/m_src->elem[0][0];
		
		// Solve unknowns in row i in mat_l
		for (int j = 1; j < i; j++)
		{
			(*m_l)->elem[i][j] = m_src->elem[i][j];
			
			for (int k = 0; k < j; k++)
			{
				(*m_l)->elem[i][j] -= (*m_l)->elem[i][k]*(*m_u)->elem[k][j];
			}
			
			(*m_l)->elem[i][j] = (*m_l)->elem[i][j]/(*m_u)->elem[j][j];
		}

		// Solve unknowns in row j in mat_u
		for (int j = i; j < n; j++)
		{
			(*m_u)->elem[i][j] = m_src->elem[i][j];
			
			for (int k = 0; k < i; k++)
			{
				(*m_u)->elem[i][j] -= (*m_l)->elem[i][k]*(*m_u)->elem[k][j];
			}
		}
	}

	// Check for singularity in mat_l or mat_u
	for (int i = 0; i < m; i++)
	{
		if (!(*m_l)->elem[i][i] || !(*m_u)->elem[i][i])
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
		inv_m_u->elem[i][i] = 1/m_u->elem[i][i];
		
		for (int j = i + 1; j < n; j++)
		{
			for (int k = 0; k < j; k++)
			{
				inv_m_u->elem[i][j] -= inv_m_u->elem[i][k]*m_u->elem[k][j];	
			} 

			inv_m_u->elem[i][j] = inv_m_u->elem[i][j]/m_u->elem[j][j];
		}
	}

	inv_m_u->elem[n - 1][n - 1] = 1/m_u->elem[n - 1][n - 1];

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
		inv_m_l->elem[i][i] = 1;

		for (int j = i - 1; j >= 0; j--)
		{
			inv_m_l->elem[i][j] = -1*m_l->elem[i][j];
			for (int k = i - 1; k > j; k--)
			{
				inv_m_l->elem[i][j] -= inv_m_l->elem[i][k]*m_l->elem[k][j];	
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
			free(m_src->elem[i]);
			m_src->elem[i] = NULL;
		}

		free(m_src->elem);
		m_src->elem = NULL;

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
				printf("%f ", m->elem[i][j]);
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
