//#include "b_tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	mat_t *m  = init(1, 3);

	(m->elements)[0][0] = 1;
	(m->elements)[0][1] = 2;
	(m->elements)[0][2] = 3;

	mat_t *m_l, *m_u;
	lu_fact(&m_l, &m_u, m);

	print_mat(m_l);
	print_mat(m_u);

	free_mat(m_l);
	free_mat(m_u);
	free_mat(m);
}
