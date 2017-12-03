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

/*retorna uma lista com os dados da arvore em preorder e posorder*/
void post_order_lst (struct b_node *tree, struct node **list);
void pre_order_lst  (struct b_node *tree, struct node **list);

/*apaga a arvore*/
void destroy_tree (struct b_node **tree);

/*função que balanceia a arvore, segundo o criterio apresentado "menor"- lado esquerdo, "maior"- lado direito*/
void balance_tree (struct b_node **tree);


/*retorna a profundidade do nível da arvore. retorna 0 se a arvore esta vazia*/
int get_level (struct b_node *tree);

/*verifica se a arvore é uma arvore de busca*/
int is_search_tree (struct b_node *tree, int (*compare) (struct b_node *, struct b_node *));



/*get level*/
#endif
