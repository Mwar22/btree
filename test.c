#include <stdio.h>
#include <stdlib.h>
#include "list_library/lista.h"
#include "btree.h"


int compare (struct b_node *a, struct b_node *b)
{
  if (*((int *) a->data) > *((int *) b->data))
    return 1;
  else
    return -1;
}


void print(node *rotas)
{
  node *cursor = NULL;
  while (rotas != NULL)
    {
      cursor = (node *) rotas->data;
      while (cursor != NULL)
        {
          printf (" %d ", *((int *)(((struct b_node *) cursor->data))->data));
          cursor = cursor->next;
        }
      printf ("\n");
      rotas = rotas->next;
    }
}


int main (int argc, char *argv[])
{
  int m = 4;
  int n[2] = {2,3};
  struct b_node *tree = NULL;

  /*
 
  add_b_node (&tree, new_b_node (&m),compare);
  add_b_node (&tree, new_b_node (&n[1]),compare);
  add_b_node (&tree, new_b_node (&n[0]),compare);*/
  printf ("worked 2\n");
  
  node *rotas = trace_leaf_routes (tree);
  printf ("worked 4\n");
  print (rotas);
  return (0);
}
