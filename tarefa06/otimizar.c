#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#define MAX 10



node* criar_arvore(){
    return NULL;
}

node_pilha * criar_pilha(){
    node_pilha* pilha =(node_pilha*)malloc(sizeof (node_pilha));
    pilha->next = NULL;
    return pilha;
}

// A função libera as memórias dos nós que alocamos na pilha
void destruir_pilha(node_pilha* pilha){
    node_pilha* aux = pilha->next;
    while(aux != NULL){
        node_pilha* aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    free(pilha);
}

// A função empilha um nó no topo da pilha
void empilhar(node_pilha * pilha, node* pont){

    node_pilha * novo_node = (node_pilha *)malloc(sizeof(node_pilha));
    novo_node->dado = pont;
    novo_node->next = pilha->next;
    pilha->next = novo_node;
}


// A função desempilha um nó do topo da pilha.
void desempilhar(node_pilha * pilha){

    node_pilha * aux;
    aux = pilha->next->next;
    free(pilha->next);
    pilha->next = aux;

}

//void mostrar_arvore(node* raiz) {
//    if (raiz) {
//
//        mostrar_arvore(raiz->esq);
//        printf("%s", raiz->info);
//        mostrar_arvore(raiz->dir);
//    }
//}


// Função recursiva que insere um nó na árvore, caso a chave seja 0
// é inserido um nó à esquerda da raiz, caso seja 1, é inserido um nó
// à direita da raiz e também é colocado o elemento da entrada no nó.
// Caso a entrada seja parêntese, o nó é empilhado em uma pilha já que
// precisamos saber o endereço do nó quando recebemos uma operação na entrada (Função preencher).
node* inserir(node* raiz, int chave, node_pilha* pilha, char *num){


    node* novo;

    if(raiz == NULL) {
        novo = (node *) malloc(sizeof(struct node));
        novo->esq = novo->dir = NULL;
        strcpy(novo->info, num);
        if(strcmp(num, "#")==0){
            empilhar(pilha, novo);
        }

        return novo;
    }
    if(chave == 0){
        raiz->esq = inserir(raiz->esq, chave, pilha, num);
    } else {
        raiz->dir = inserir(raiz->dir, chave, pilha, num);
    }

    return raiz;

}

// A função recebe os elementos da entrada (parênteses, algorismo ou operação),
// com base na entrada que recebe, ela executa uma instrução diferente. Caso
// a entrada for "(", chama a função inserir, cria um nó na árvore com filhos NULL e empilha esse nó em uma pilha.
// Caso entrada for uma operação ( '+', '-' ou '*' ) o nó da árvore que está no topo
// da pilha recebe a operação. Caso for algarismo, o nó do topo da pilha recebe um filho
// com tal algarismo (à direita ou à esquerda). Caso for ")", o topo da pilha é desempilhado.
node* preencher(node* raiz, int chave, node_pilha* pilha, char *entrada){

    scanf(" %s", entrada);

    if(strcmp(entrada, "(")==0){

        if(pilha->next == NULL){

            raiz = inserir(raiz, chave, pilha, "#");

        } else {

            raiz = inserir(pilha->next->dado, chave, pilha, "#");

        }

        chave=0;

        preencher(raiz, chave, pilha, entrada);

    } else if(strcmp(entrada, "+")==0 || strcmp(entrada, "-")==0 || strcmp(entrada, "*")==0 || strcmp(entrada, "/")==0){
        strcpy(pilha->next->dado->info, entrada);
        chave = 1;
        preencher(raiz, chave, pilha, entrada);

    }
    else if (strcmp(entrada, ")")==0){
        desempilhar(pilha);
        if(pilha->next == NULL){
            return raiz;
        }
        preencher(raiz, chave, pilha, entrada);

    } else {

        raiz = inserir(pilha->next->dado, chave, pilha, entrada);
        preencher(raiz, chave, pilha, entrada);

    }

    return raiz;
}

// A função simplifica as operações da árvore, ou seja,
// ela percorre nós da árvore, caso os nós filhos sejam
// algarismos, é feita a respectiva operação do nó pai. O
// nó pai vira o resultado da operação dos filhos e também
// é liberada a memória dos nós filhos.
node* simplificar_funcao(node* raiz){

    if (raiz->dir != NULL && raiz->esq != NULL) {

        int num = atoi(raiz->esq->info);
        int num2 = atoi(raiz->dir->info);

        if((num != 0 || strcmp(raiz->dir->info, "0")==0) && (num2 != 0 || strcmp(raiz->dir->info, "0")==0)){

            int res=0;
            if(strcmp(raiz->info, "+")==0){
                res = num + num2;
                res = res%256;
            }
            else if(strcmp(raiz->info, "-")==0){
                res = num - num2;
                if(res < 0){
                    res = -res;
                    res = 256-(res%256);
                }

            } else if(strcmp(raiz->info, "*")==0){
                res = num * num2;
                res = res%256;
            }

            char str[MAX];

            sprintf(str, "%d", res);

            free(raiz->esq);
            free(raiz->dir);
            raiz->esq = NULL;
            raiz->dir = NULL;

            strcpy(raiz->info, str);

            return raiz;
        }

        else {
            if(strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0){

                node* retorno_dir =  simplificar_funcao(raiz->dir);
                node* retorno_esq = simplificar_funcao(raiz->esq);
                int k1 = atoi(retorno_dir->info);
                int k2 = atoi(retorno_esq->info);

                if((k1 != 0 || strcmp(retorno_dir->info, "0")==0) && (k2 != 0 || strcmp(retorno_esq->info, "0")==0)){
                    return simplificar_funcao(raiz);
                } else {
                    return raiz;
                }
            } else {
                return raiz;
            }
        }

    }
    return raiz;
}

// A função libera o espaço de memória da árvore que criamos
void liberar_memoria_arvore(node* raiz){
    if(raiz!= NULL){
        liberar_memoria_arvore(raiz->esq);
        liberar_memoria_arvore(raiz->dir);
        free(raiz);
    }
}

// A função imprime a saída com notação infixa, fazendo com
// que cada operação seja rodeada por parênteses.
void mostrar_infixa(node* raiz){

    if (raiz == NULL){
        return;
    }

    if (strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0){
        printf("( ");
    }

    mostrar_infixa(raiz->esq);

    if (strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0){
        printf(" %s ", raiz->info);
    } else {
        printf("%s", raiz->info);
    }

    mostrar_infixa(raiz->dir);

    if (strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0){
        printf(" )");
    }

}

int main() {
    // cria uma árvore
    node *raiz = criar_arvore();
    // cria uma pilha
    node_pilha *pilha = criar_pilha();

    int chave=0;

    char *entrada = malloc(MAX*sizeof(char));

    raiz = preencher(raiz, chave, pilha, entrada);

    raiz = simplificar_funcao(raiz);

    mostrar_infixa(raiz);

    //liberar as memórias
    destruir_pilha(pilha);
    free(entrada);
    liberar_memoria_arvore(raiz);

}
