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
            i->right_son = nd;
            break;
          }
          else
            i = i->right_son;
      }
      else
        {
          if (i->left_son  == NULL)
          {
            i->left_son = nd;
            break;
          }
          else
            i = i->left_son;
        }
    }
  }
}



/*Retorna 3 para ambos, 2 para filho direito, 1 para esquerdo, 0 para nenhum e -1 p/ erro*/
static int sons_of (struct b_node *father)
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


/*
 * gera as rotas para as folhas
 * retorna uma lista de rotas (listas)
 */
struct node *trace_leaf_routes (struct b_node *btree)
{
  int paths_length = 0;   /*tamanho da lista de caminhos*/
  node *paths = NULL;     /*lista de caminhos*/
  node *last_nodes_list = NULL;  /*lista com os ultimos nos de cada caminho */
  
  int track_pos = 0;     /*posicao (na lista) do caminho*/
  node *track =  NULL;    /*o caminho em específico*/
  
  if (btree == NULL)
    return NULL;
  
  if (paths == NULL)    /* config iniciais */
    {
      track = new (btree); 
      paths = new (track);
      last_nodes_list = track;
      
      track_pos = 0;
      paths_length = 1;
    }
    
  int can_bif = 0;       /*caminho pode bifurcar? 0 não, 1 sim */
  do
    {
      node *last_node = getNode (track_pos, last_nodes_list);
      struct b_node *ln = (struct b_node *) (last_node->data);
      
      switch (sons_of (ln))
        {
          case 0:
                can_bif = 0;
                break;
          case 1:
              last_node->next = new (ln->left_son);
              (last_node->next)->next = NULL;
              last_node = last_node->next;
              can_bif = 1;
            break;
            
          case 2:
              last_node->next = new (ln->right_son);
              (last_node->next)->next = NULL;
              last_node = last_node->next;
              can_bif = 1;
            break;
          
        }
        
      if (track->next != NULL)  /*avança*/
        {
          track = track->next;
          track_pos++;
        }
      else if (can_bif == 1)  /*volta pro começo*/
        {
          track = paths;
          track_pos = 0;
        }
    }
  while (track_pos < paths_length || can_bif == 1);   /*enquanto nao tiver chegado no fim e nem ter chance de bifurcar...*/
  return paths;
}
