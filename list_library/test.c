#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void prt (node *head)
{
  printf ("n: %d\n",*((int *) head->data));
  if (head->next != NULL)
    prt (head->next);
}

int compare (node *a, node *b);

int main()
{
  /* define os elementos head e tail da lista a ser criada - OBRIGATORIO*/
  node *head = NULL;
    
  /*adiciona elementos à lista (inicializa), no caso adicionando inteiros de 0 à 4    */
  int i;
  
  for (i = 1; i < 7; i++)
    {
      // aloca e atribui um inteiro
      int *t = (int *)malloc (sizeof (int));
      *t = i;

      //cria e adiciona um elemento (no fim)//
      addAtTail (new (t), &head);
    }
  
  prt (head);
  printf ("sz: %d\n", getSize (head));
  
  
  printf("-------------------------\n");
  node *t = getNode (-1, head);
  printf ("nd 6: %d\n", ((t != NULL) ? *((int *) t->data): 0));
  
  
  
  printf("-------------------------\n");
  int *k = (int *)malloc (sizeof (int));
      *k = 99;
  
  addAt (new (k), 3, &head);
  prt(head);
  
  
  delAt(-5,&head);
  printf("-------------------------\n");
  prt(head);
  printf ("-fafafa------------------\n");
  
  node *hd2  = split (4, head);

  prt(head);
  printf("+++++++++++++\n");
  
  join (&hd2, &head);
  prt(head);
  
  printf("+++++++++++++\n");
  
  int *l = (int *)malloc (sizeof (int));
      *l = -1;
      
  addAt (new (l),3, &head);
  prt(head);
  
  printf("++++++++++++7+\n");
  
  sort (&head, compare, decrescente); /*passa endereço do ponteiro de head, e a função de comparação*/
  prt(head);
  
  
  printf ("\n\ntest- revert\n");
  revert (&head);
  prt(head);
  
  printf ("\n\ntest- revert\n");
  
  
  printf ("\n\ntest- delete\n");
  
  delete (&head);
  if (head == NULL)
  {
    printf ("\nLISTA VAZIA\n");
  }
}

int compare (node *a, node *b)
{
  if (*((int *) a->data) > *((int *) b->data))
      return 1;
    else if (*((int *) a->data) < *((int *) b->data))
      return -1;
    
  return 0;
}


