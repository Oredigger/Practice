#include "l_list.h"
#include <stdlib.h>
#include <stdio.h>

void push(node_t **head, double val)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node != NULL) 
    {
        new_node->val = val;
        new_node->next = NULL;
        
        if (*head == NULL)
        {
            *head = new_node;
        }
        else
        {
            node_t *temp_head = *head;
            while (temp_head->next != NULL) temp_head = temp_head->next;
            temp_head->next = new_node;
        }  
    }
}

void pop(node_t **head)
{
    node_t *temp_head = *head;
    if (temp_head->next == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        while (temp_head->next->next != NULL) temp_head = temp_head->next;
        free(temp_head->next);
        temp_head->next = NULL;
    }
}

void del_list(node_t **head)
{
    while (*head != NULL)
    {
        node_t *c_node = *head;
        *head = (*head)->next;
        
        free(c_node);
        c_node = NULL;
    }
}

void print(node_t *head)
{
    if (head != NULL)
    {
        printf("Contains %f\n", head->val);
        print(head->next);
    }
}
