#ifndef LIST_H
#define LIST_H

enum
{
  crescente,
  decrescente
};


typedef struct node
{
  void *data;
  struct node *next;
}
node;

/*cria novo elemento da lista, o qual pode ser qualquer tipo de elemento (passa-se o endereço do mesmo)*/
node *new (void *data);

/*apaga uma lista*/
void delete (node **head);

/*gera uma copia da lista... lista*/
node *copy (node *head);


/*adiciona novo elemento à lista (pela cabeça da lista), pt_to_head é um ponteiro para o seu ponteiro do head*/
node *addAtTail (node *no, node **pt_to_head);  

/*msm coisa, mas adiciona na calda*/
node *addAtHead (node *no, node **pt_to_head);  

/*adiciona em uma posição indicada pelo id position (0 até tamanho -1)*/
node *addAt (node *no, int position, node **pt_to_head);  

/*separa a lista referenciada por head em duas listas (corta depois da posição indicada por i), retorna o endereço da nova cabeça de lista (se der erro, retorna NULL ), cujo primeiro endereço seria o mesmo de i +1 */
node *split (int i, node *head); 

/*Une a lista representada por head no final da lista apontada(ponteiro para o ponteiro de head) por main_head
 * retorna main_head se der td OK, NULL se deu algo errado;
 */
node *join (node **head, node **main_head);

/*deleta o elemento indicado na posição i, retorna 0 se foi tudo ok*/
int delAt (int i, node **pt_to_head); 

/*retorna o numero de elementos da lista*/
int getSize (node *head);   

/*retorna o nó, começando em no nó 0 até o nó especificado (p/ i < 0, conta-se de traz para frente)*/
node *getNode (int i, node *head); 

/*ordena a lista, recebe dois parametros, um é o ponteiro para o ponteiro de head,
 * o outro é o endereço de uma função de ordenação (vc declara uma função que retorne uma função que retorna um int com dois parametros, um nó a e um b)
 * na ordem especificada por order (passe 'crescente' ou 'decrescente')
 */
int sort (node **lista, int (*compare) (node *a, node *b), int order);

/*
 * reverte a ordem da lista
 */
void revert (node **lista);

#endif
