#ifndef BTREE_H
#define BTREE_H

/*Declaracao incompleta para a estrutura de lista*/
struct node;

/*estrutura que representa um nó da arvore*/
struct b_node
{
  void *data;
  struct b_node *left_son;
  struct b_node *right_son;
};

/*cria novo no*/
struct b_node *new_b_node (void *data);

/*acidiona o nó "nd", à arvore apontada por bthree*/
void add_b_node (struct b_node **btree, struct b_node *nd, int (*compare) (struct b_node *, struct b_node *));

/*Retorna 3 para ambos, 2 para filho direito, 1 para esquerdo, 0 para nenhum e -1 p/ erro*/
int sons_of (struct b_node *father);

/*
 * gera as rotas para as folhas
 * retorna uma lista de rotas (listas)
 */
struct node *trace_leaf_routes (struct b_node *btree);

/*apaga a arvore*/
void destroy_tree (struct b_node **tree);

/*get level*/
#endif
