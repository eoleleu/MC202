
#ifndef RA213437_ARQUIVO_H
#define RA213437_ARQUIVO_H

// Estrutura de dado que tem como membros um inteiro e um ponteiro.
typedef struct node{
    int dado;
    struct node *next;
} node;

node* criar_pilha();

void destruir_pilha(node* pilha);

void empilhar(node* pilha, int number);

void desempilhar(node* pilha);

int tamanho_p(node* pilha);

int verificar_validade_sequencia(node* pilha, int n);

void solucao(node*pilha, int k);


#endif //RA213437_ARQUIVO_H
