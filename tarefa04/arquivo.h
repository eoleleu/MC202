
#ifndef RA213437_ARQUIVO_H
#define RA213437_ARQUIVO_H
    // Estrutura de dado que tem como membros um vetor do tipo char, um inteiro e um ponteiro
    typedef struct node {
        char word[128];
        struct node* next;
        int tipo;
    } node;

    node* criar_lista();

    void destruir_lista(node* listaTotal);

    node *destacar(node* lista, int inicio, int fim);

    void print_lista(node* lista);

    char* strsep(node* lista, int ini, int fim);

    node* inserir(node* lista, char *frase, int indice);

    void mostrar_resultado(node* lista);
#endif //RA213437_ARQUIVO_H
