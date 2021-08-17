#ifndef B_TREE_H
#define B_TREE_H

typedef struct b_node
{
    double val;
    struct b_node *left;
    struct b_node *right;
} b_node_t;

// Process for creating a new node
void new_b_node(b_node_t **, double);

// Insert a new value, and consequently a new node, into the binary tree.
void insert_tree(b_node_t **, double);

// Print the tree
void print_tree(b_node_t *);

// Check if the binary tree in question contains the target value
int lookup_tree(b_node_t *, double);

// Count the total number of nodes in the binary tree
int size(b_node_t *);

// Obtain the maximum depth of the binary tree
int max_depth(b_node_t *);

// Obtain the minimum value in the binary tree
double min_value(b_node_t *);

#endif