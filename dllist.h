/*
 * Author: Manuel Mager
 * Copyright: GPL 3+
 * 2018
 * email: mmager@turing.iimas.unam.mx
 */

#ifndef list_h
#define list_h

typedef int (*dl_comparator)(void *, void *);
typedef int (*dl_print)(void *);
typedef int (*dl_freefunc)(void *);

typedef struct dlnode
{
    struct dlnode *next;
    struct dlnode *prev;
    void *data;
}dlnode;

typedef struct dllist
{
    dlnode *start;
    dlnode *end;
    dl_comparator comp;
    dl_print print;
    dl_freefunc free_func;
}dllist;

dllist  *list_new(dl_comparator, dl_print, dl_freefunc);
int     list_add(dllist *, void *);
int     list_add_end(dllist *, void *);
dlnode  *list_search(dllist *, void *);
int     list_remove(dllist *, void *);
void    *list_pop(dllist *);
void    *list_pop_end(dllist *);
void    list_free(dllist *);
void    list_print(dllist *);

void    *list_delnode(dllist *, dlnode *);
int     list_addafternode(dlnode *, void *);
int     list_addbeforenode(dlnode *, void *);
#endif
