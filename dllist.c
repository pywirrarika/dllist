/*
 * Author: Manuel Mager
 * Copyright: GPL 3+
 * 2018
 * email: mmager@turing.iimas.unam.mx
 */


#include<stdio.h>
#include<stdlib.h>

#include "dllist.h"

dllist  *
list_new(dl_comparator comp, dl_print print, dl_freefunc ff)
{
    dllist *list;
    
    if(comp && print && ff)
    { 
        list = malloc(sizeof(dllist));
        list->comp = comp;
        list->print = print;
        list->free_func = ff;
        list->start = NULL;
        list->end = NULL;

        return list;
    }
    return NULL;
}

int     
list_add(dllist *list, void *data)
{
    dlnode *node;
    dlnode *tmp;

    if(!(list && data))
        return 0;

    node = malloc(sizeof(dlnode));
    if(node == NULL)
        return 0;
    node->data = data;

    if(list->start == NULL)
    {
        list->start = node;
        list->end = node;
        node->next = NULL;
        node->prev = NULL;
        return 1;
    }
    tmp = list->start;
    list->start = node;
    node->next = tmp;
    node->prev = NULL;
    tmp->prev = node;
    
    return 1;
}

int     
list_add_end(dllist *list, void *data)
{
    dlnode *node;
    dlnode *tmp;

    if(!(list && data))
        return 0;

    node = malloc(sizeof(dlnode));
    if(node == NULL)
        return 0;
    node->data = data;

    if(list->start == NULL)
    {
        list->start = node;
        list->end = node;
        node->next = NULL;
        node->prev = NULL;
        return 1;
    }
    tmp = list->end;
    list->end= node;
    node->next = NULL;
    node->prev = tmp;
    tmp->next = node;
    
    return 1;
}

dlnode  *
list_search(dllist *list, void *data)
{
    dlnode *node;

    if(!list)
        return NULL;
    if(!(list->start))
        return NULL;
    if(!data)
        return NULL;

    node = list->start;
    while(node != NULL)
    {
        if(list->comp(data, node->data))
            return node;
        node = node->next;
    }
    return NULL;
}

int
list_remove(dllist *list, void *data)
{
    dlnode *node;
    if(!list)
        return 0;
    if(!(list->start))
        return 0;
    if(!data)
        return 0;
            
    node = list->start;
    while(node != NULL)
    {
        if(list->comp(data, node->data))
        {
            if(node->prev)
            {
                if(node->next)
                    node->prev->next = node->next;
                else 
                    node->prev->next = NULL;
            }
            if(node->next)
            {
                if(node->prev)
                    node->next->prev = node->prev;
                else
                    node->next->prev = NULL;
            }
            
            if(list->start == node)
            {
                list->start = node->next;
                if(!(node->next))
                    list->end = node->next;
            }
            else if(list->end == node)
            {
                list->end = NULL;
                list->start = NULL;
            }
            
            list->free_func(node->data);
            free(node);
            node = NULL;

            return 1;
        }
        node = node->next;
    }
    return 0;
}

void *
list_pop(dllist *list)
{
    dlnode *node;
    void *data;
    node = list->start;
    node->next->prev = NULL;
    data = node->data;
    list->start = list->start->next;
    free(node);
    node = NULL;
    return data;
}
    
void *
list_pop_end(dllist *list)
{
    dlnode *node;
    void *data;
    node = list->end;
    node->prev->next = NULL;
    data = node->data;
    list->end = node->prev;
    free(node);
    node = NULL;
    return data;
}

void    
list_free(dllist *list)
{
    dlnode *node;
    dlnode *tmp;
    node = list->start;
    while(node)
    {
        list->free_func(node->data);
        tmp = node;
        node = node->next;
        free(tmp);
        tmp = NULL;
    }
    free(list);
    list = NULL;
}
        
void *
list_delnode(dllist *list, dlnode *node)
{
    void *data;
            
    if(!node)
        return NULL;

    if(node->prev)
    {
        if(node->next)
            node->prev->next = node->next;
        else 
            node->prev->next = NULL;
    }
    if(node->next)
    {
        if(node->prev)
            node->next->prev = node->prev;
        else
            node->next->prev = NULL;
    }
    
    if(list->start == node)
    {
        list->start = node->next;
        if(!(node->next))
            list->end = node->next;
    }
    else if(list->end == node)
    {
        list->end = NULL;
        list->start = NULL;
    }
    
    data = node->data;
    free(node);
    node = NULL;
    return data;
}

int 
list_addafternode(dlnode *node, void *data)
{
    dlnode *new_node;
    new_node = malloc(sizeof(new_node));
    if(!new_node)
        return 0;
    new_node->data = data;
    new_node->next = node->next;
    new_node->prev = node;
    node->next = new_node;
    return 1;
}

int 
list_addbeforenode(dlnode *node, void *data)
{
    dlnode *new_node;
    new_node = malloc(sizeof(new_node));
    if(!new_node)
        return 0;
    new_node->data = data;
    new_node->next = node->next;
    new_node->prev = node;
    node->next = new_node;
    return 1;
}

void    
list_print(dllist *list)
{
    int i = 0;
    dlnode *node;

    if(list)
        if(list->start)
            node = list->start;
        else
            return;
    else
        return;

    while(node)
    {
        printf("%d: ",i);
        list->print(node->data);
        node = node->next;
        i++;
    }
    return;
}
        

