#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"


// Cria uma cabeça para a lista, essa cabeça aponta para NULL e não tem nenhum valor dentro
// do nó.
node* criar_pilha(){
    node* pilha =(node*)malloc(sizeof (node));
    pilha->next = NULL;
    return pilha;
}


// A função tem o objetivo de destruir a pilha que passamos de referência, ou seja,
// desalocar a memória alocada quando criamos a pilha e empilhamos outros nós.
void destruir_pilha(node* pilha){
    node* aux = pilha->next;
    while(aux != NULL){
        node* aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    free(pilha);
}
// A função empilha um nó no topo da pilha.
// Parâmetro -> number (int): número que queremos colocar no nó que empilhamos.
void empilhar(node* pilha, int number){

    node* novo_node = (node*)malloc(sizeof(node));
    novo_node->dado = number;
    novo_node->next = pilha->next;
    pilha->next = novo_node;
}


// A função desempilha o nó do topo da pilha.
void desempilhar(node* pilha){
    node* aux;

    aux = pilha->next->next;
    free(pilha->next);
    pilha->next = aux;

}

// A função tem o objetivo de calcular o tamanho da pilha que passamos de referência.
int tamanho_p(node* pilha){
    int cont=0;
    while(pilha->next != NULL){
        cont +=1;
        pilha = pilha->next;
    }
    return cont;
}

// A função verifica se a sequência recebida na entrada é válida ou não é.
// Para isso a função percorre todos os nós da pilha, se o valor for negativo
// então empilha, se o valor for positivo e igual ao valor do topo da pilha checadora
// então desempilha. Se no final, a pilha checadora for vazia significa que a sequência é válida,
// caso contrário, a sequência é inválida.
// Parâmetros -> pilha (node*): estrutura de dados que armazenas os dados recebidos na entrada.
// n (int): tipo da maior matriosca da sequência.
// Retornos -> 1 (sequência válida), 0 (sequência inválida).
int verificar_validade_sequencia(node* pilha, int n){

    node* pilha_check = criar_pilha();
    int cont=0;
    int cont_n=0;
    int tamanho_pilha;

    tamanho_pilha = tamanho_p(pilha);
    while (cont < tamanho_pilha){
        if(pilha->next != NULL){
            pilha = pilha->next;
        }
        if(pilha->dado == n || pilha->dado == (-1)*n){
            cont_n+=1;
        }
        if (pilha->dado < 0){
            empilhar(pilha_check, pilha->dado);
            cont+=1;
        } else {
            //printf("%d\n", pilha->next->dado);
            if(pilha->dado == (-1)*pilha_check->next->dado){
                desempilhar(pilha_check);
                cont+=1;
            }
            else {
                destruir_pilha(pilha_check);
                return 0;
            }
        }
    }
    //mostrar_pilha(pilha_check);
    if(cont_n>2){
        destruir_pilha(pilha_check);
        return 0;

    }
    if(pilha_check->next == NULL){
        destruir_pilha(pilha_check);
        return 1;
    }
    destruir_pilha(pilha_check);
    return 0;
}

// A função tem o objetivo de imprimir o número de cada boneca e a
// quantidade de bonecas contidas diretamente a essa boneca. Para isso,
// ela percorre a pilha até achar a representação negativa da boneca que estamos
// iterando. Após isso, percorre a pilha até achar o número da boneca que estamos
// querendo saber a quantidade de bonecas que tem dentro. Enquanto isso ela empilha os outros números
// em uma pilha auxiliar se o número for negativo e desempilha se o número for positivo,
// diretamente depois disso, se a pilha auxiliar estiver vazia, acrescentamos 1 unidade
// ao total de quantidade de bonecas. Por fim, a função imprime o algarismo da boneca e a
// quantidade de bonecas que tem diretamente dentro.
// Parâmetros -> pilha (node*): estrutura de dados que armazenas os dados recebidos na entrada.
// k (int): boneca que queremos saber a qtd de bonecas que tem dentro dela.
void solucao(node*pilha, int k){
    int qtd_bonecas = 0;
    pilha = pilha->next;
    while(pilha->dado != (-1)*k){
        pilha = pilha->next;
        if(pilha == NULL){
            break;
        }
    }

    if(pilha!= NULL){
        node* aux = criar_pilha();
        while(pilha->dado != k){
            pilha = pilha->next;

            if(pilha->dado < 0){
                empilhar(aux, pilha->dado);
            } else {
                if(aux->next != NULL){
                    desempilhar(aux);
                }

                if(aux->next == NULL){
                    qtd_bonecas+=1;
                }
            }
        }

        printf("%d contem %d bonecas\n", k, qtd_bonecas-1);
        destruir_pilha(aux);
    }

}

int main(){
    // cria uma pilha
    node* pilha = criar_pilha();

    int n, i;

    // recebe o valor da maior matriosca
    scanf("%d", &n);

    // recebe a sequência representando um conjunto de matrioscas.
    while(scanf("%d", &i)!= EOF){
        empilhar(pilha, i);
    }

    // verifica se a sequência é válida
    int validade = verificar_validade_sequencia(pilha, n);

    if(validade == 0){
        printf("sequencia invalida\n");
    } else {
        for(int k=1;k<=n;k++){
            solucao(pilha, k);
        }
    }

    // desaloca a memoria da pilha que criamos
    destruir_pilha(pilha);

    return 0;
}


//void mostrar_pilha(node* pilha){
//
//    pilha = pilha->next;
//
//    while(pilha!=NULL){
//        printf("%d\n", pilha->dado);
//        pilha = pilha->next;
//    }
//}

