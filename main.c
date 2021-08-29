//#include "b_tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	mat_t *m  = init(3, 3);

	(m->elements)[0][0] = 2;
	(m->elements)[0][1] = 4;
	(m->elements)[0][2] = 6;

	(m->elements)[1][0] = 2;
	(m->elements)[1][1] = 0;
	(m->elements)[1][2] = 2;

	(m->elements)[2][0] = 6;
	(m->elements)[2][1] = 8;
	(m->elements)[2][2] = 1;


	mat_t *inv_m = inv(m);
	print_mat(inv_m);

	free_mat(inv_m);
	free_mat(m);
}
