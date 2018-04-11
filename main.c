/*
 * Author: Manuel Mager
 * Copyright: GPL 3+
 * 2018
 * email: mmager@turing.iimas.unam.mx
 */

#include<stdio.h>
#include<stdlib.h>

#include "dllist.h"

// Function that compares two objects. Returns 1 if equal, 0 if not. 
int 
comparator(void *a, void *b)
{
  if((int *)a == (void *)b)
    return 1;
  else;
    return 0;
}

//Function that print a object
int 
print(void *a)
{
  printf("%d\n", *((int *)a));
}

//Function that free object
int
free_o(void *a)
{
  free(a);
}

int
main()
{
  printf("This is a demo to show how to use dllist header.\n");
  printf("---------------------\n");
  printf("We add 1,2,3 int ponters to the list\n");
    
  dllist *list;
  int a=1,b=2,c=3,d=4;
  dlnode *node;
  
  list = list_new(&comparator, &print, &free_o);
  
  list_add(list, &a);
  list_add(list, &b);
  list_add(list, &c);

  list_print(list);

  printf("Lets add one element at the end of the list.\n");
  list_add_end(list, &d);
  list_print(list);
  
  printf("Now we will search for element with number 2.\n");
  node = list_search(list, &b); 
  print(node->data);

  printf("With the node we retrived from search, lets remove it from the list.\n");
  list_delnode(list, node);
  list_print(list);

  printf("At next, we will pop the first element from the list and print the content.\n");
  node = list_pop(list);
  list_print(list);
  
  return 0;
}
