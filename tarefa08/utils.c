/*
Implementação de funções auxiliares para string.

Você NÃO deve modificar este arquivo.
*/

#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

p_no_str ler_lista_periodos(char *nome_arquivo, int *numero_periodos) {
    FILE *fp = fopen(nome_arquivo, "r");
    assert(fp);
    p_no_str lista_periodos = NULL;
    p_no_str *prox = &lista_periodos;
    char periodo[MAX_BUFFER];
    *numero_periodos = 0;
    while (fscanf(fp, " %[^.].", periodo) != EOF) {
        p_no_str novo = malloc(sizeof(struct no_str));
        assert(novo);
        novo->prox = NULL;
        novo->str = malloc(strlen(periodo) + 1);
        assert(novo->str);
        strcpy(novo->str, periodo);
        *prox = novo;
        prox = &novo->prox;
        *numero_periodos += 1;
    }
    fclose(fp);
    return lista_periodos;
}

p_no_str extrair_palavras(char *periodo) {
    char buffer[MAX_BUFFER];
    strcpy(buffer, periodo);
    int n = strlen(buffer);
    for (int i = 0; i < n; i++) {
        if (!isalnum(buffer[i])) {
            buffer[i] = ' ';
        }
    }
    p_no_str lista_palavras = NULL;
    p_no_str *prox = &lista_palavras;
    char *palavra = strtok(buffer, " ");
    while (palavra != NULL) {
        p_no_str novo = malloc(sizeof(struct no_str));
        assert(novo);
        novo->prox = NULL;
        novo->str = malloc(strlen(palavra) + 1);
        assert(novo->str);
        strcpy(novo->str, palavra);
        *prox = novo;
        prox = &novo->prox;

        palavra = strtok(NULL, " ");
    }
    return lista_palavras;
}

int corresponde(p_no_str busca, p_no_str lista) {
    for (p_no_str p = lista; p != NULL; p = p->prox) {
        int ok = 1;
        p_no_str c, q;
        for (c = busca, q = p; c != NULL && q != NULL; c = c->prox, q = q->prox) {
            if (strcmp(q->str, c->str) != 0) {
                ok = 0;
                break;
            }
        }
        if (ok && c == NULL) {
            return 1;
        }
    }
    return 0;
}

void mostrar_palavras(char *info, p_no_str lista_palavras) {
    printf("%s:\n", info);
    while (lista_palavras) {
        printf("  - '%s'\n", lista_palavras->str);
        lista_palavras = lista_palavras->prox;
    }
}

void liberar_lista_str(p_no_str lista) {
    while (lista) {
        p_no_str tmp = lista;
        lista = lista->prox;
        free(tmp->str);
        free(tmp);
    }
}
