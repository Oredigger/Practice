#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    b_node_t *root = NULL;

    insert_tree(&root, 1);
    insert_tree(&root, 2);
    insert_tree(&root, 1);
    insert_tree(&root, 3);
    insert_tree(&root, 5);

    printf("%d\n", size(root));
    printf("%d\n", max_depth(root));
    printf("%f\n", min_value(root));

    print_tree(root);

    return 0;
}