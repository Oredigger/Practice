//#include "b_tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	mat_t *m  = init(3, 3);

	(m->elem)[0][0] = 2;
	(m->elem)[0][1] = 4;
	(m->elem)[0][2] = 6;

	(m->elem)[1][0] = 2;
	(m->elem)[1][1] = 2;
	(m->elem)[1][2] = 2;

	(m->elem)[2][0] = 6;
	(m->elem)[2][1] = 8;
	(m->elem)[2][2] = 14;

	mat_t *m_l, *m_u;
	printf("%d\n", lu_fact(&m_l, &m_u, m));

	print_mat(m_l);
	print_mat(m_u);

	mat_t *m_t = mat_transpose(m);
	print_mat(m);
	print_mat(m_t);

	free_mat(m_l);
	free_mat(m_u);
	free_mat(m_t);
	free_mat(m);
}
