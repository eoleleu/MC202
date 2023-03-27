

#ifndef RA213437_ARQUIVO_H
#define RA213437_ARQUIVO_H
#define MAX 10

    // Estrutura de dado que tem como membros um vetor do tipo char e ponteiros para a esquerda e direita
    typedef struct node{
        char info[MAX];
        struct node* dir;
        struct node* esq;

    } node;

    // Estrutura de dado de uma pilha que o objetivo de armazenar nó da árvore
    typedef struct node_pilha{

        node* dado;
        struct node_pilha *next;

    } node_pilha;

    node* criar_arvore();

    node_pilha * criar_pilha();

    void destruir_pilha(node_pilha* pilha);

    void empilhar(node_pilha * pilha, node* pont);

    void desempilhar(node_pilha * pilha);

    node* inserir(node* raiz, int chave, node_pilha* pilha, char *num);

    node* preencher(node* raiz, int chave, node_pilha* pilha, char *entrada);

    node* simplificar_funcao(node* raiz);

    void liberar_memoria_arvore(node* raiz);

    void mostrar_infixa(node* raiz);


#endif //RA213437_ARQUIVO_H
