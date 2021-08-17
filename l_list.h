#ifndef L_LIST_H
#define L_LIST_H

typedef struct node
{
    double val;
    struct node * next;
} node_t;

void push(node_t **, double);
void pop(node_t **);

void del_list(node_t **);
void print(node_t *);

#endif