#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arquivo.h"
#define MAX 300

// A função cria uma lista que aponta para NULL
node* criar_lista() {
    return NULL;
}

// A função libera o espaço de memória da estrutura que criamos
void destruir_lista(node* lista){
    node *aux1, *aux2;
    aux1 = lista;
    while(aux1 != NULL){
        aux2 = (node*)aux1->next;
        free(aux1);
        aux1 = aux2;
    }
    lista = NULL;
}

//A função tem como objetivo separar a string que está dentro do
// nó que chamamos a função em um pedaço.
// Parâmetros -> ini (int): posição do caracter inicial que queremos
// fim (int): fim (int): posição do catacter final que queremos
// Retorno: vetor com um pedaço da string do nó que passamos de referência
char* strsep(node* lista, int ini, int fim) {
    char* new_word = malloc(128*sizeof(char));
    for (int i = ini; i < fim; i++) {
        new_word[i - ini] = lista->word[i];
    }
    new_word[fim - ini] = '\0';
    return new_word;
}

//A função insere a frase recebida na entrada na lista, caso a lista
// for vazia a função insere um novo nó, caso o índice recebido
// for 0 ela cria um nó no início da lista, caso precise inserir
// uma frase dentro de um nó ela separa a string do nó em pedaços,
// logo depois é feita a inserção. Ela também repassará o tipo
// da string que será inserida, 0 para normal ou 1 se for
// dentro de um trecho destacado;
// Parâmetros -> frase (vetor de caracteres): armazena a string que
// desejamos colocar na lista.
// indice (int): posição na lista que precisamos locar a string
node* inserir (node* lista, char *frase, int indice){
    node* novo_node = malloc(sizeof(node));
    strcpy(novo_node->word, frase);
    if (lista == NULL){
        lista = novo_node;
        novo_node->tipo = 0;
        novo_node->next = NULL;
    } else if (indice == 0){
        novo_node->next = lista;
        novo_node->tipo = lista->tipo;
        lista = novo_node;

    } else {
        node* no = lista;

        while (indice>0){
            //novo_node->tipo = no->tipo;
            if (strlen(no->word)<indice){
                //printf("caso 1:  %d %d\n", indice, strlen(no->word));
                indice -= strlen(no->word);
                //printf("%d %d\n", indice, strlen(no->word));
                novo_node->tipo = no->tipo;
                no = no->next;

                //novo_node->tipo = 1;
            }else if (indice== strlen(no->word)){
                //printf("caso 2:  %d %d\n", indice, strlen(no->word));

                indice -= strlen(no->word)+1;
                novo_node->next = no->next;


                no->next = novo_node;
                if (no->tipo == 1){
                    no = no->next;
                    no = no->next;
                    if(no->tipo==1){
                        novo_node->tipo = no->tipo;
                    }

                }


            }else if (indice < strlen(no->word)){
                //printf("caso 3:  %d %d\n", indice, strlen(no->word));

                char* pedaco1 = strsep(no, 0, indice);
                char* pedaco2 = strsep(no, indice, strlen(no->word));
                indice -= strlen(no->word);
                //printf("%s %d\n", pedaco1, strlen(pedaco1));
                //printf("%s %d\n", pedaco2, strlen(pedaco2));
                node* no_fim = malloc(sizeof(node));
                no_fim->next = no->next;
                strcpy(no->word, pedaco1);
                novo_node->next = no_fim;


                strcpy(no_fim->word, pedaco2);

                no->next = novo_node;
            }
        }
    }
    return lista;
}

// A função verifica onde irá começar o trecho que será destacado
// e também onde irá terminar. Conforme necessário pode acontecer de
// ter que "quebrar" um nó em 2 ou 3 pedaços para depois os pedaços
// serem inseridos na lista novamente com seus respectivos tipos (0 ou 1).
// Parâmetro: lista (node*): estrtura de dados que armazena nós de strings e
// o armazena tipo de cada nó, 0 se não é destacado e 1 se é destado
node *destacar (node* lista, int inicio, int fim){

    node* no = lista;
    int tam = strlen(no->word);

    if (inicio < tam && fim == tam ){
        char *pedaco1 = strsep(no, 0, inicio);
        char *pedaco2 = strsep(no, inicio, strlen(no->word));
        //printf("%s %d\n", pedaco1, strlen(pedaco1));
        //printf("%s %d", pedaco2, strlen(pedaco2));

        node* no_fim = malloc(sizeof(node));
        strcpy(no->word, pedaco1);
        no_fim->next = no->next;
        strcpy(no_fim->word, pedaco2);
        no->next = no_fim;
        no_fim->tipo = 1;

        free(pedaco1);
        free(pedaco2);

        return lista;
    } else if (inicio < tam && fim<tam){

        char* pedaco1 = strsep(no, 0, inicio);
        char* pedaco2 = strsep(no, inicio, fim);
        char* pedaco3 = strsep(no, fim, strlen(no->word));
        node* no_meio = malloc(sizeof(node));
        node* no_fim = malloc(sizeof(node));
        strcpy(no->word, pedaco1);
        strcpy(no_meio->word, pedaco2);
        strcpy(no_fim->word, pedaco3);

        no_fim->next = no->next;
        no_meio->next = no_fim;
        no->next = no_meio;
        no_meio->tipo = 1;
        no_fim->tipo =0;

        free(pedaco1);
        free(pedaco2);
        free(pedaco3);
        return lista;
    }

    int cont =0;
    for (node *n = no; n->next!=NULL; n = n->next){
        if(strlen(no->word) + cont <= inicio){
            no = n->next;
            cont += strlen(n->word);

        }
    }

    if (cont<inicio){
        char* pedaco1 = strsep(no, 0, inicio-cont);
        char* pedaco2 = strsep(no, inicio-cont, strlen(no->word));

        strcpy(no->word, pedaco1);
        node* no_fim = malloc(sizeof(node));
        strcpy(no_fim->word, pedaco2);
        no_fim->next = no->next;
        no->next = no_fim;
        no->tipo = 0;
        no_fim->tipo =1;
        no= no->next;
        no->tipo=1;
        free(pedaco1);
        free(pedaco2);
    }

    while (fim-cont+1>=strlen(no->word) && cont !=0){

        no->tipo = 1;
        cont += strlen(no->word);
        if(no->next != NULL){
            no = no->next;
        }
    }

    if (fim==strlen(no->word)-cont){
        //printf("2");
        char* pedaco1 = strsep(no, 0, inicio-cont);
        char* pedaco2 = strsep(no, inicio-cont, fim);
        strcpy(no->word, pedaco1);
        node* no_fim = malloc(sizeof(node));
        strcpy(no_fim->word, pedaco2);
        no_fim->next = no->next;
        no->next = no_fim;

        no_fim->tipo =1;
        free(pedaco1);
        free(pedaco2);
    }

    if (cont == inicio && fim < cont+ strlen(no->word)){
        char* pedaco1 = strsep(no, 0, inicio+1);
        char* pedaco2 = strsep(no, inicio+1, strlen(no->word));
        //printf("%s", pedaco2);
        node* no_fim = malloc(sizeof(node));
        strcpy(no->word, pedaco1);
        no->tipo = 1;
        strcpy(no_fim->word, pedaco2);
        no_fim->next = no->next;
        no->next = no_fim;
        free(pedaco1);
        free(pedaco2);
        return lista;
    } else if (cont-1 == inicio && fim>cont){
        char* pedaco1 = strsep(no, 0, fim-inicio);
        char* pedaco2 = strsep(no, fim-inicio, strlen(no->word));
        //printf("%s\n", pedaco1);
        //printf("%s\n", pedaco2);
        node* no_fim = malloc(sizeof(node));
        strcpy(no->word, pedaco1);
        no->tipo = 1;
        strcpy(no_fim->word, pedaco2);
        no_fim->next = no->next;
        no->next = no_fim;
        free(pedaco1);
        free(pedaco2);
    }
    return lista;
}

// A função mostra o conteúdo da saída conforme os comandos
// executados anteriormente. Os nós da lista que não estão
// destacados são mostrados com a palavra "NORMAL" anteriormente, já
// os nós destacados são mostrados com a palavra "NEGRITO" antes.
// Parâmetro: lista (node*): estrutura que armazena nós com strings,
// ponteiros e também armazena o tipo de cada nó, 0 se não é destacado e 1 se é destacado
void mostrar_resultado(node* lista){
    node* aux = lista;
    printf("NORMAL '");
    while(aux != NULL && aux->tipo==0){
        printf("%s", aux->word);
        aux = aux->next;
    }
    printf("\'");
    printf("\n\n");
    if(aux!=NULL){
        if(aux->tipo ==1 ){
            printf("NEGRITO '");
            while(aux != NULL && aux->tipo==1){
                printf("%s", aux->word);
                aux = aux->next;
            }
        }
        printf("\'");
        printf("\n\n");
    }


    if(aux!= NULL){
        if(aux->tipo ==0 ){
            printf("NORMAL '");
            while(aux != NULL && aux->tipo==0){
                printf("%s", aux->word);
                aux = aux->next;
            }
        }
        printf("\'");
        printf("\n\n");
    }


    if(aux!=NULL){
        printf("NEGRITO '");
        printf("%s", aux->word);
        aux = aux->next;


        printf("\'");
        printf("\n\n");
    }

    if(aux!= NULL){
        printf("NORMAL '");
        while(aux != NULL){
            printf("%s", aux->word);
            aux = aux->next;
        }

        printf("\'");
        printf("\n\n");
    }


}

int main() {

    // cria um lista vazia
    node* lista = criar_lista();

    // aloca um vetor dinamicamente para receber a frase que será inserida na lista
    char *frase = malloc(MAX *sizeof (char));
    // aloca um vetor dinamicamente para receber o comando que será executado (INSERIR, DESTACAR OU MOSTRAR)
    char *comando = malloc(MAX *sizeof (char));

    int indice;
    int verificador=1;
    int inicio, fim;

    while (verificador==1){
        scanf("%s", comando);

        if(strcmp(comando, "INSERIR")==0){

            scanf("%d", &indice);
            scanf(" '%[^']'", frase);
            lista = inserir(lista, frase, indice);

        } else if(strcmp(comando, "MOSTRAR")==0){

            mostrar_resultado(lista);
            verificador = 0;

        } else if(strcmp(comando, "DESTACAR")==0){

            scanf("%d %d", &inicio, &fim);
            lista = destacar(lista, inicio, fim);

        }

    }


    destruir_lista(lista);

    //Libera a memória dos vetores alocados dinamicamente
    free(frase);
    free(comando);

    return 0;
}