#include "btree.h"
#include "list_library/lista.h"
#include <stdio.h>
#include <stdlib.h>


/*cria novo no*/
struct b_node *new_b_node (void *data)
{
  struct b_node *new  =  (struct b_node *)malloc (sizeof(struct b_node));
  
  if (new == NULL)
    {
      printf ("\t>>Sem memoria para alocar no!\n");
      return NULL;
    }
  
  new->data = data;
  new->right_son =  NULL;
  new->left_son = NULL;
  
  return new;
}

/*acidiona o nó "nd", à arvore apontada por bthree*/
void add_b_node (struct b_node **btree, struct b_node *nd, int (*compare) (struct b_node *, struct b_node *))
{
  if (*btree == NULL)
  {
    *btree = nd;
    return;
  }
  else
  {
    struct b_node *i = *btree;
    
    while (1)
    {
      if ((*compare)(nd,i) > 0)
      {
          if (i->right_son  == NULL)
          {
            printf ("stab right\n");
            i->right_son = nd;
            break;
          }
          else
          {
            printf ("walked right\n");
            i = i->right_son;
          }
      }
      else
        {
          if (i->left_son  == NULL)
          {
            printf ("stab left\n");
            i->left_son = nd;
            break;
          }
          else
          {
            printf ("walked left\n");
            i = i->left_son;
          }
        }
    }
  }
}



/*Retorna 3 para ambos, 2 para filho direito, 1 para esquerdo, 0 para nenhum e -1 p/ erro*/
int sons_of (struct b_node *father)
{
  int sons = 3;
  if (father != NULL)
    {
      if (father->left_son == NULL)
        sons -= 1;
      
      if (father->right_son == NULL)
        sons -= 2;
    }
    else
        sons = -1;  /*erro*/
    
  return sons;
}

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

static void print_endlist (node *end_list)
{
  int i = 0;
  node *tmp = end_list;
  printf ("end_list_size :%d\n", getSize (end_list));
  do
    {
      printf ("position: %d | end_value: %d\n", i++,*((int *)((struct b_node *) ((node *) tmp->data)->data)->data));
      tmp =  tmp->next;
    }
   while (tmp != NULL);
}

static void add_to_path (node *path_end, struct b_node *no)
{
  ((node *) path_end->data)->next =  new (no); /*adiciona um novo no (o novo ultimo) para o caminho atual */
  path_end->data = ((node *) path_end->data)->next;      /*atualiza o endereço do ultimo ultimo*/
  ((node *) path_end->data)->next = NULL;
}

/*
 * gera as rotas para as folhas
 * retorna uma lista de rotas (listas)
 */
struct node *trace_leaf_routes (struct b_node *btree)
{
  int path_list_size = 0;   /*tamanho da lista de caminhos*/
  int path_list_index = 0;  /*posição corrente na lista de caminhos*/
  node *path_list =  NULL;  /*lista que armazena o endereço de uma lista de cada caminho*/
  node *end_list = NULL;      /*lista que aponta p o ultimo de cada caminho*/
  
  struct b_node *current = NULL;
  
  int can_branch = 0;       /* 1 se tem a chance de haver uma bifurcacao */
  
  if (btree == NULL)
    return path_list;
  else
  {
    path_list =  new (new (btree)); /*nova lista (caminho)*/
    path_list_size++;
    
    end_list = new (path_list->data);  /*aponta p o ultimo elemento*/
  }
  
  do
    {
      node *end = (node *) (getNode (path_list_index, end_list)); /* armazena ponteiro para o nó do fim do caminho */
      struct b_node *end_value = (struct b_node *) ((node *) end->data)->data; /*o valor armazenado pelo fim do caminho*/
      printf ("-------------------\n");
      printf ("index %d|node val: %d\n",path_list_index, *((int *) end_value->data));
                
      
      switch (sons_of (end_value))
        {
          case 0:  /* nenhum filho, folha */
              can_branch = 0;
              path_list_index++;
            break;
          case 1: /*1 filho, filho esquerdo */
              add_to_path (end, end_value->left_son);
              can_branch = 1;
              
            break;
            
          case 2: /*1 filho, filho direito */
              add_to_path (end, end_value->right_son);
              can_branch = 1;
            break;
          
          case 3: /*2 filhos, direito e esquerdo*/
            {
                printf ("caso 3\n");
                node *tmp = getNode (path_list_index, path_list);
                node *path = (node *) (tmp->data);
                node *clone = copy (path);
                
              
                
                /*pega o fim dos clones*/
                node *clone_end =  clone;
                while (clone_end->next != NULL)
                  clone_end = clone_end->next;
                
                node *clone_end_pointer = new (clone_end);
                
                
                /*filho esquerdo para o caminho, e o direito p o clone*/
                add_to_path (end, end_value->right_son);
                add_to_path (clone_end_pointer, end_value->left_son);
         
                
                /*adiciona o clone no começo e adiciona  o end do mesmo */
                addAtHead (new (clone), &path_list);
                addAtHead (clone_end_pointer, &end_list);
                
                
                
                
                printf ("end_list_top val: %d\n", *((int *) ((struct b_node *) ((node *) end_list->data)->data)->data));
                printf ("after adding\n");
                print (path_list);
                
            
                can_branch = 1;
                path_list_size++;
                path_list_index = 0;
            }
            break;
           
        }
         print_endlist (end_list);
         printf ("\n*****************\nPATHS\n");
         print (path_list);
          
    }
  while (can_branch == 1 || path_list_index < path_list_size);
  
  delete (&end_list);
  return path_list;
  
}
