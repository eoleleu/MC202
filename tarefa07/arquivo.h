//
// Created by leleu on 17/11/2022.
//

#ifndef RA213437_ARQUIVO_H
#define RA213437_ARQUIVO_H
#define MAX 20

// Estrutura de dados do item que ocupa cada posição do heap, composto por uma string e um inteiro;
typedef struct node{
    char fruta[MAX];
    int peso;
} node;

//Estrutura de dados do heap;
typedef struct FP{
    node *v;
    int n;
    int chave;
} FP;

FP* criar_vetor(int tam);

FP* troca(int a, int b, FP* heap);

int pai(int k);

int filho_direito(int k);

int filho_esquerdo(int k);

void desce_min_heap(FP* min_heap, int k);

void extrair_min(FP* min_heap);

FP* transformar_max_heap(FP* heap, int k);

void desce_max_heap(FP* max_heap, int k);

void extrair_max(FP* max_heap);

FP* transformar_min_heap(FP* heap, int k);

void imprimir_mediana(FP* max_heap, FP* min_heap);

void inserir(FP* max_heap, FP* min_heap, char *fruta, int peso, int chave);

void liberar_memoria_heap(FP* heap);

int main();

#endif //RA213437_ARQUIVO_H
