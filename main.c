//#include "b_tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	mat_t *m = init(3, 3);
	(m->elements)[0][1] = 5;
	(m->elements)[1][2] = 12;
	
	mat_t *x = ext_col(m, 2);
	print_mat(x);

	free_mat(m);
	free_mat(x);
}
