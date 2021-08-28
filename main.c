//#include "b_tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	mat_t *m = init(2, 2);

	(m->elements)[0][0] = 2;
	(m->elements)[0][1] = 0;

	(m->elements)[1][0] = 1;
	(m->elements)[1][1] = 1;

	print_mat(m);

	mat_t *l = NULL;
	mat_t *u = NULL;

	lu_fact(&l, &u, m);
	print_mat(l);
	print_mat(u);

	free_mat(m);
	free_mat(l);
	free_mat(u);
}
