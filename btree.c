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

/*apaga a arvore*/
void destroy_tree (struct b_node **btree)
{
  struct b_node *tree = *btree;
  if (tree != NULL)
    {
      destroy_tree (&(tree->left_son));
      destroy_tree (&(tree->right_son));
      free (tree);
    }
    
  *btree = NULL;
  
}

/*função que balanceia a arvore, segundo o criterio apresentado "menor"- lado esquerdo, "maior"- lado direito*/
void balance_tree (struct b_node **tree)
{
  if (*tree != NULL)
    {
      struct b_node *rs = (*tree)->right_son;
      struct b_node *ls = (*tree)->left_son;
      
      /*pega o "level" das subarvores filhas*/
      int L = get_level (ls);
      int R = get_level (rs);
      
      /* se a arvore filha direita tiver um desnivel maior que 1 com a direita:
       * o intuito é fazer o filho direito o novo head (rotaciona p/ a esquerda)
       */
      if (R- L > 1)
        {
          
          /*salva o neto esquerdo do filho direito de head */
          struct b_node *rs_left = rs->left_son;
          
          /*faz de head a um filho do filho direito*/
          rs->left_son = *tree;
          
          (*tree)->right_son =  rs_left;
          
          /*altera o novo head p rs*/
          *tree = rs;
          
          /*tenta balancear denovo (pode não estar balanceado)*/
          balance_tree (tree);
        }
        else if (L - R > 1)
          {
            /*salva o neto direito do filho esquerdo de head */
            struct b_node *ls_right = ls->right_son;
            
            /*faz de head a um filho do filho esquerdo*/
            ls->right_son = *tree;
            
            (*tree)->left_son =  ls_right;
            
            /*altera o novo head p ls*/
            *tree = ls;
            
            /*tenta balancear denovo (pode não estar balanceado)*/
            balance_tree (tree);
          }
    }
}

/*retorna a profundidade do nível da arvore. retorna 0 se a arvore esta vazia*/
int get_level (struct b_node *tree)
{
  int left_tree_level = 0;
  int right_tree_level = 0;
  
  if (tree != NULL)
    {
      left_tree_level = get_level (tree->left_son) +1;
      right_tree_level = get_level (tree->right_son) +1;
    }
  
  /*retorna o maior caminho*/
  if (left_tree_level > right_tree_level)
    return left_tree_level;
  else
    return right_tree_level;
}
