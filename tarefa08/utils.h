/*
Interface de funções auxiliares para string.

A implementação do índice de exemplo utiliza a biblioteca utils.h, que contém
algumas funções para manipular listas de strings. Você pode utilizar essas
funções livremente, se desejar, ou pode criar suas próprias funções modificando
essas.

Você NÃO deve modificar este arquivo.
*/

#ifndef UTILS_H
#define UTILS_H

#define MAX_BUFFER 1024

typedef struct no_str *p_no_str;

struct no_str {
    char *str;
    p_no_str prox;
};

/*
Cria uma nova lista de strings contendo
os períodos em um arquivo de texto.
Armazena o número de períodos na variável
passada por referência numero_periodos.
*/
p_no_str ler_lista_periodos(char *nome_arquivo, int *numero_periodos);

/*
Cria uma nova lista de strings contendo
as palavras de um período.
*/
p_no_str extrair_palavras(char *periodo);

/*
Mostra palavras na tela.
*/
void mostrar_palavras(char *info, p_no_str lista_palavras);

/*
Verifica se a lista de strings busca está
contida na lista.
*/
int corresponde(p_no_str busca, p_no_str lista);

/*
Libera a memória de uma lista de strings.
*/
void liberar_lista_str(p_no_str lista);

#endif
