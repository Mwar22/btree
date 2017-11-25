#include <stdio.h>
#include <stdlib.h>
#include "list_library/list.h"
#include "btree.h"


void print(node *rotas)
{

  node *cursor = NULL;
  do
    {
      cursor = (node *) rotas->data;
      do
        {
         
          printf (" %d ", *((int *)(((struct b_node *) cursor->data))->data));
          cursor = cursor->next;
        }
      while (cursor != NULL);
      printf ("\n");
      rotas = rotas->next;
   
    }
  while (rotas != NULL);
}



int compare (struct b_node *a, struct b_node *b)
{
  if (*((int *) a->data) > *((int *) b->data))
    return 1;
  else
    return -1;
}




int main (int argc, char *argv[])
{
  int m = 15;
  int n[] = {4,16,20,6,18,5,7,17,21,19};
  struct b_node *tree = NULL;

  
 
  add_b_node (&tree, new_b_node (&m),compare);
  int i = 0;
  for (i = 0; i < 10; i++)
    add_b_node (&tree, new_b_node (&n[i]), compare);
  
  node *rotas = trace_leaf_routes (tree);
  print (rotas);
  return (0);
}
