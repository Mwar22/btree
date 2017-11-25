#include "btree.h"
#include "list_library/list.h"
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
            i->right_son = nd;
            break;
          }
          else
          {
            i = i->right_son;
          }
      }
      else
        {
          if (i->left_son  == NULL)
          {
            i->left_son = nd;
            break;
          }
          else
          {
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
            
                can_branch = 1;
                path_list_size++;
                path_list_index = 0;
            }
            break;
           
        }
          
    }
  while (can_branch == 1 || path_list_index < path_list_size);
  
  /*apaga end_list (lixo)*/
  node *next;
  while (end_list != NULL)
    {
      next = end_list->next;
      free (end_list);
      end_list = next;
    }
  return path_list;
  
}
