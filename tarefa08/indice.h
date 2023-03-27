/*
Esta deve ser a interface do índice.

Você NÃO deve modificar este arquivo.
*/

#ifndef INDICE_H
#define INDICE_H

typedef struct indice *p_indice;

/*
Cria um novo índice para um arquivo.
*/
p_indice criar_indice(char *nome_arquivo);

/*
Busca no índice todos os períodos que
correspondem à consulta. Para cada período,
em ordem, a função callback deve ser chamada
como no exemplo:

    callback(periodo, numero_ocorrencia);

Devolve o número total de períodos encontrados.
*/
int consultar_indice(
    p_indice indice,
    char *consulta,
    void(callback)(char *periodo, int numero_ocorrencia));

/*
Libera a memória de todos os dados
alocados para o índice.
*/
void liberar_indice(p_indice indice);

#endif
