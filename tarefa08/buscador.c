/*
Este arquivo corresponde ao programa principal.
Esse programa é um "cliente" do arquivo indice.h.
Você NÃO deve modificar este arquivo.
*/

#include "indice.h"

#include <assert.h>
#include <stdio.h>

#define MAX_BUFFER 1024
#define MAX_RESULTADOS 3

void callback(char *periodo, int numero_ocorrencia) {
    if (numero_ocorrencia <= MAX_RESULTADOS) {
        printf("   -> encontrado em '%s'\n", periodo);
    }
}

int main() {
    char nome_aquivo[MAX_BUFFER];
    char consulta[MAX_BUFFER];

    assert(scanf(" %[^?]", nome_aquivo) == 1);
    p_indice indice = criar_indice(nome_aquivo);

    while (scanf(" %*[^=]=%[^\n]", consulta) != EOF) {
        printf("Buscando '%s'\n", consulta);

        int resultados = consultar_indice(indice, consulta, callback);
        if (resultados == 0) {
            printf("   -> '%s' nao encontrado\n", consulta);
        } else if (resultados > MAX_RESULTADOS) {
            printf("   -> e em mais %d periodos...\n", resultados - MAX_RESULTADOS);
        }
        printf("\n");
    }

    liberar_indice(indice);
    return 0;
}
