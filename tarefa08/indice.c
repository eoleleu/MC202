/*
Este arquivo conterá a implementação do índice.
Na versão atual, a estrutura de dados corresponde
somente a uma lista de períodos e não há nenhuma
estrutura pensada para realizar buscas rapidamente.

Você DEVE completar este arquivo, modificando-o livremente.
*/

#include "indice.h"
#include "utils.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 160001
// num : este campo armazena a chave da palavra (número de hash)
// n_perido: este campo armazena uma lista ligada que guarda as posições do período lido com base na chave da string.
// tam : indica quantas frases foi encontrada a string.
typedef struct number {

    int num;

    int n_perido;
    int tam;
    struct number* prox;
} number;

// lista_peridos: armazena as frases lidas do arquivo, em ordem.
// hash: armezena a string em uma posição com base no número de hash calculado.
// v: vetor que armazena os campos da struct number.
struct indice {

    number* v;

    int tamanho;
    p_no_str lista_periodos;
    p_no_str hash;
} ;



void criarLista(p_no_str lista){
    lista = NULL;
}

// A função cria uma lista ligada em cada índice do vetor 'lista_periodo' e 'hash', na qual
// estão inseridos no campo 'tabela'
void criarTabela(p_indice tabela){
    for(int i=0;i<MAX;i++){
        criarLista(tabela->lista_periodos[i].prox);
        criarLista(tabela->hash[i].prox);
    }
}

// Essa função hash de usa o método da divisão
// para strings, isto é, a função percorre
// todas os caracteres da string para obter
// o melhor número de hash possível. Com isso
// é menos provável que duas palavras diferentes
// tenham o mesmo número de hash, evitando algumas
// colisões.
// Parâmetro -> chave(char*): string que precisamos inserir na tabela hash
// Retorno -> número inteiro (n) que indica a posição na tabela que precisamos inserir a string
int funcao_hash(char *chave){
    int i, n=0;

    for(i=0;i<strlen(chave);i++){
        n = (256 * n + chave[i]) % MAX;
    }

    return n;
}

// A função insere na posição n (número de hash) a palavra que precisamos inserir na tabela hash.
// palavra (char*): string que queremos inserir na tabela hash.
// n (int) : inteiro que indica qual a posição que vamos inserir a string.
void inserir_lista(p_indice tabela, char* palavra, int n){
    p_no_str novo = malloc(sizeof (struct no_str));

    if(novo){
        novo->str = malloc(strlen(palavra)+1);
        novo->prox = tabela->hash[n].prox;

        strcpy(novo->str, palavra);

        tabela->hash[n].prox = novo;
        tabela->v[n].num = n;

    }
}

// A função guarda a frase no vetor "lista_periodos" de acordo
// com ordem da frase lida do arquivo.
void guardar_frase(p_indice tabela, int cont, char* periodo){
    p_no_str novo = malloc(sizeof (struct no_str));
    if(novo){
        novo->str = malloc(strlen(periodo)+1);
        novo->prox = tabela->lista_periodos[cont].prox;
        strcpy(novo->str, periodo);
        tabela->lista_periodos[cont].prox = novo;
    }
}

// A função armazena o número da frase lida na mesma posição (número de hash)
// da palavra que estamos inserindo na tabela hash.
// Parãmetros -> cont (int) : número do período lido. Número que queremos inserir no campo n_perido
// n (int): número de hash da palavra. A função inserir no índice 'n' o inteiro 'cont'
void guardar_posicao_perido(p_indice tabela, int cont, int n){
    number* novo = malloc(sizeof (struct number));
    novo->prox = NULL;
    novo->n_perido = cont;

    if(tabela->v[n].prox == NULL){
        novo->prox = tabela->v[n].prox;
        tabela->v[n].prox = novo;
    } else {
        number* aux = tabela->v[n].prox;
        while(aux->prox != NULL){
            aux= aux->prox;
        }
        aux->prox = novo;

    }
}

// A função insere as palavras das frases lidas do arquivo na tabela hash,
// para isso ela chama uma função que calcula a chave da palavra que precisamos inserir,
// caso dê alguma colisão percorremos a tabela hash até encontrar alguma posição vazia, assim
// então inserimos a palavra.
void inserir(p_indice tabela, char* palavra, int cont){

    int n = funcao_hash(palavra);

    if(tabela->v[n].num == 0){
        inserir_lista(tabela, palavra, n);

        int verificador=0;
        number* aux1 = tabela->v[n].prox;

        while(aux1 != NULL){
            if(aux1->n_perido == cont){
                verificador = 1;
            }
            aux1 = aux1->prox;

        }
        if(verificador==0){
            guardar_posicao_perido(tabela, cont, n);
            tabela->v[n].tam+=1;
        }
    } else {

        p_no_str aux = tabela->hash[n].prox;
        if(strcmp(aux->str, palavra)!=0){

            while(tabela->v[n].num != 0){
                n+=1;
                if(tabela->v[n].num==0){
                    break;
                } else {
                    p_no_str a = tabela->hash[n].prox;
                    if(strcmp(a->str, palavra)==0){
                        break;
                    }

                }

            }

            inserir_lista(tabela, palavra, n);



            int verificador=0;
            number* aux2 = tabela->v[n].prox;

            while(aux2 != NULL){
                if(aux2->n_perido == cont){
                    verificador = 1;
                }
                aux2 = aux2->prox;

            }
            if(verificador==0){
                guardar_posicao_perido(tabela, cont, n);
                tabela->v[n].tam+=1;
            }

        }

        int verificador=0;
        number* aux3 = tabela->v[n].prox;

        while(aux3 != NULL){
            if(aux3->n_perido == cont){
                verificador = 1;
            }
            aux3 = aux3->prox;

        }
        if(verificador==0){
            guardar_posicao_perido(tabela, cont, n);
            tabela->v[n].tam+=1;
        }

    }

}

// A função lê cada linha do arquivo recebido no arquivo buscador.c
// A função também chama uma função que separa a cada palavra da frase
// lida em uma lista ligada, então ela insere na nossa tabela hash;
// Parâmetros -> tabela (p_indice): estrutura de dados que armazena
// as frases lidas e as palavras separa pelo número de hash.
// nome_arquivo (char*): nome do arquivo que deseja ser lido.
void ler_arquivo(p_indice tabela, char* nome_arquivo){

    FILE *fp = fopen(nome_arquivo, "r");
    assert(fp);
    char periodo[1000];
    int cont=0;

    while (fscanf(fp, " %[^.].", periodo) != EOF) {
        //printf("%s\n", periodo);
        guardar_frase(tabela, cont, periodo);
        p_no_str palavras_periodo = extrair_palavras(periodo);
        p_no_str aux = palavras_periodo;
        while(aux != NULL){

            inserir(tabela, aux->str, cont);

            aux = aux->prox;
        }

        cont+=1;

    }

    tabela->tamanho = cont;

}

// A função cria as estrutura de dados que foram utilizadas para
// resolver o exercício. O vetor "lista_periodos" guarda as frases lidas
// do arquivo e o vetor "hash" guarda as palavras do arquivo lido, na qual cada
// está associada a uma chave obtida na função hash.
// Retorno -> tabela (p_indice): campo que armazena os vetores.
p_indice criar_indice(char *nome_arquivo) {
    p_indice tabela = malloc(sizeof(struct indice));

    tabela->v = malloc(MAX*sizeof (number));
    tabela->lista_periodos = malloc(MAX*sizeof(struct no_str));
    tabela->hash = malloc(MAX*sizeof (struct no_str));

    for(int i=0;i<MAX;i++){
        tabela->v[i].num = 0;
        tabela->v[i].tam=0;
    }

    criarTabela(tabela);

    ler_arquivo(tabela, nome_arquivo);

    return tabela;
}

// A função calcula o número de hash da palavra que deseja buscar, caso a índice
// do número de hash encontrado for 0, retorna que a palavra não foi encontrada.
// Caso a palavra que está no índice forem diferente da palavra que estamos buscando, percorremos
// a tabela hash até encontrar, se não for encontrado, também retornamos que não a palavra não foi encontrada.
// Se encontramos a palavra diretamente na posição retornada pela função hash ou se for encontrada após percorrer
// o vetor, então mostrado as frases que ela foi encontrada.
// Retorno -> tabela->v[h].tam : qunatida de vezes que a palavra foi encontrada.
int consultar_indice(p_indice tabela, char *consulta, void(callback)(char *periodo, int numero_ocorrencia)) {

    int h = funcao_hash(consulta);

    if(tabela->v[h].num!= 0){
        p_no_str a = tabela->hash[h].prox;
        if(strcmp(a->str, consulta)!=0) {

            while (tabela->v[h].num != 0) {
                h += 1;
                if (tabela->v[h].num == 0) {
                    break;
                } else {
                    p_no_str b = tabela->hash[h].prox;
                    if (strcmp(b->str, consulta) == 0) {
                        break;
                    }

                }

            }
        }
    }

    if(tabela->v[h].num==0){
        return 0;
    } else {
        p_no_str a = tabela->hash[h].prox;

        if(strcmp(a->str, consulta)!=0){
            return 0;
        }
    }



    if(tabela->v[h].tam ==0){
        return 0;
    } else if(tabela->v[h].tam==1){
        number* aux = tabela->v[h].prox;
        p_no_str periodo = tabela->lista_periodos[aux->n_perido].prox;
        callback(periodo->str, tabela->v[h].tam);
        //printf("%s\n", periodo->str);
        return tabela->v[h].tam;
    } else if(tabela->v[h].tam == 2) {
        number* aux2 = tabela->v[h].prox;
        p_no_str perido2 = tabela->lista_periodos[aux2->n_perido].prox;
        callback(perido2->str, tabela->v[h].tam);

        aux2 = aux2->prox;
        perido2 = tabela->lista_periodos[aux2->n_perido].prox;
        callback(perido2->str, 2);

        return 2;
    } else if(tabela->v[h].tam >= 3){
        number* aux3 = tabela->v[h].prox;
        p_no_str periodo3 = tabela->lista_periodos[aux3->n_perido].prox;
        callback(periodo3->str, 3);

        aux3 = aux3->prox;
        periodo3 = tabela->lista_periodos[aux3->n_perido].prox;
        callback(periodo3->str, 3);

        aux3 = aux3->prox;
        periodo3 = tabela->lista_periodos[aux3->n_perido].prox;
        callback(periodo3->str, 3);

        if(tabela->v[h].tam==3){
            return 3;
        }
    }

    return tabela->v[h].tam;


}

// Libera a memória do vetor que armazena as frases lidas do arquivo.
void liberar_indice(p_indice indice) {
    liberar_lista_str(indice->lista_periodos);

    free(indice);
}


//void     imprimir_tabela_periodos(p_indice tabela){
//
//    for(int i=0;i<tabela->tamanho;i++){
//        p_no_str aux = tabela->lista_periodos[i].prox;
//        printf("%s\n", aux->str);
//    }
//}


//void imprimir_lista(p_indice tabela){
//    p_no_str aux = tabela->lista_periodos;
//    while(aux){
//
//        printf("%s", aux->str);
//        aux = aux->prox;
//    }
//}
//
//void imprimir_tabela_hash(p_indice tabela){
//    for(int i=0;i<MAX;i++){
//        //printf("%d\n", tabela->v[i].num);
//        if(tabela->v[i].num != 0){
//            //printf("%d = ", i);
//            p_no_str aux = tabela->hash[tabela->v[i].num].prox;
//            printf("%s %d   ", aux->str, tabela->v[i].num);
//
//            printf("tam : %d", tabela->v[i].tam);
//
//            printf("\n");
//        }
//
//    }
//}