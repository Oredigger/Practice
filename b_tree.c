#include "b_tree.h"
#include <stdlib.h>
#include <stdio.h>

void new_b_node(b_node_t **root, double val)
{
    b_node_t *new_b_node = (b_node_t *)malloc(sizeof(b_node_t));
    if (new_b_node != NULL)
    {
        new_b_node->val   = val;
        new_b_node->left  = NULL;
        new_b_node->right = NULL;

        *root = new_b_node;
    }
}

void insert_tree(b_node_t **root, double val)
{
    if (*root == NULL) 
        new_b_node(root, val);
    else
    {
        if (val > (*root)->val)
            insert_tree(&((*root)->right), val);
        else
            insert_tree(&((*root)->left), val);
    }
}

void print_tree(b_node_t *root)
{
    if (root != NULL)
    {
        print_tree(root->left);
        printf("%f ", root->val);
        print_tree(root->right);
    }
}

int lookup_tree(b_node_t *root, double val)
{
    if (root == NULL) 
        return 0;
    if (root->val == val) 
        return 1;
    
    (val > root->val) ? lookup_tree(root->right, val) : lookup_tree(root->left, val);   
}

int size(b_node_t *root)
{
    if (root == NULL) 
        return 0;
    else
        return 1 + size(root->right) + size(root->left);
}

int max_depth(b_node_t *root)
{
    if (root == NULL) 
        return 0;
    if (max_depth(root->left) > max_depth(root->right)) 
        return 1 + max_depth(root->left);
    else 
        return 1 + max_depth(root->right);
}

double min_value(b_node_t *root)
{
    if (root == NULL) 
        return 0;
    if (root->left == NULL) 
        return root->val;
    else
        return min_value(root->left);
}