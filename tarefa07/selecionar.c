#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#define MAX 20



FP* criar_vetor(int tam){
    FP* heap = malloc(sizeof(FP));
    heap->v = malloc(tam*sizeof (node));
    //vetor->tam = tam;
    heap->n = 0;
    return heap;
}

FP* troca(int a, int b, FP* heap){
    int aux_peso;
    char aux_fruta[20];

    aux_peso = heap->v[a].peso;
    heap->v[a].peso = heap->v[b].peso;
    heap->v[b].peso = aux_peso;


    strcpy(aux_fruta, heap->v[a].fruta);
    if(a != b){
        strcpy(heap->v[a].fruta, heap->v[b].fruta);
    }
    strcpy(heap->v[b].fruta, aux_fruta);

    return heap;
}


int pai(int k){
    int a;
    a = (k-1)/2;
    return a;
}

int filho_direito(int k){
    int a;
    a = 2*k+1;
    return a;
}
int filho_esquerdo(int k){
    int a;
    a = 2*k+2;
    return a;
}

void desce_min_heap(FP* min_heap, int k){
    int menor_filho;
    if(filho_esquerdo(k) < min_heap->n){
        //printf("entrou\n");
        menor_filho = filho_esquerdo(k);

        if(filho_direito(k) < min_heap->n && (min_heap->v[filho_esquerdo(k)].peso > min_heap->v[filho_direito(k)].peso)){
            menor_filho = filho_direito(k);
        }

        if(min_heap->v[k].peso > min_heap->v[menor_filho].peso){
            troca(k, menor_filho, min_heap);
            desce_min_heap(min_heap, menor_filho);
        }
    }

}

void extrair_min(FP* min_heap){
    //node item = min_heap->v[0];
    troca(0, min_heap->n-1, min_heap);
    min_heap->n-=1;
    desce_min_heap(min_heap, 0);

}

FP* transformar_max_heap(FP* heap, int k){
    if(k>0 && heap->v[pai(k)].peso < heap->v[k].peso){

        troca(k, pai(k), heap);
        heap = transformar_max_heap(heap, pai(k));
    }
    return heap;
}

void desce_max_heap(FP* max_heap, int k){
    int maior_filho;
    if(filho_esquerdo(k) < max_heap->n){

        maior_filho = filho_esquerdo(k);
        if(filho_direito(k) < max_heap->n && max_heap->v[filho_esquerdo(k)].peso < max_heap->v[filho_direito(k)].peso){
            maior_filho =filho_direito(k);
        }
        //printf("%d %d\n", maior_filho, max_heap->n);



        if(max_heap->v[k].peso < max_heap->v[maior_filho].peso){
            //printf("entrou\n");
            troca(k, maior_filho, max_heap);
            desce_max_heap(max_heap, maior_filho);

        }
    }
}


void extrair_max(FP* max_heap){
    //troca(0, max_heap->n-1, max_heap);

    max_heap->v[0].peso = max_heap->v[max_heap->n-1].peso;

    strcpy(max_heap->v[0].fruta, max_heap->v[max_heap->n-1].fruta);

    max_heap->n-=1;
    desce_max_heap(max_heap, 0);
    transformar_max_heap(max_heap, max_heap->n-1);
}
FP* transformar_min_heap(FP* heap, int k){

    if(k >0 && heap->v[pai(k)].peso > heap->v[k].peso){
        troca(k, pai(k), heap);
        //troca(PAI(k), k, vetor);
        heap = transformar_min_heap(heap, pai(k));
    }
    return heap;
}

void imprimir_mediana(FP* max_heap, FP* min_heap){

    if(max_heap->n > min_heap->n){
        printf("%s: %d\n", max_heap->v[0].fruta, max_heap->v[0].peso);
    } else if(min_heap->n > max_heap->n){
        printf("%s: %d\n", min_heap->v[0].fruta, min_heap->v[0].peso);
    } else {
        printf("%s: %d\n", max_heap->v[0].fruta, max_heap->v[0].peso);
        printf("%s: %d\n", min_heap->v[0].fruta, min_heap->v[0].peso);
    }

}

// A função insere no max_heap ou no min_heap, depende se a quantidade de fruta
// diferir em 2 unidades. Caso a quantidade de fruta no max_heap tenha duas ou mais
// frutas comparada ao min_heap, o valor máximo do max_heap é jogado para o min_heap
// então é chamada uma função para colocar o min_heap com os elementos em seus devidos lugares.
// O mesmo acontece no caso contrário.
void inserir(FP* max_heap, FP* min_heap, char *fruta, int peso, int chave){

    if(peso > max_heap->v[0].peso && peso < min_heap->v[0].peso && min_heap->chave==1 && min_heap->n > max_heap->n){

        if((max_heap->n+1) - min_heap->n >= 2){
            //printf("AA \n");
            min_heap->v[min_heap->n].peso = max_heap->v[0].peso;
            strcpy(min_heap->v[min_heap->n].fruta, max_heap->v[0].fruta);
            min_heap->n+=1;
            transformar_min_heap(min_heap, min_heap->n-1);


            max_heap->v[0].peso = peso;
            strcpy(max_heap->v[0].fruta, fruta);
            transformar_max_heap(max_heap, max_heap->n-1);

        }else {
            //printf("BB \n");
            max_heap->v[max_heap->n].peso = peso;
            strcpy(max_heap->v[max_heap->n].fruta, fruta);
            max_heap->n+=1;
            transformar_max_heap(max_heap, max_heap->n-1);

        }
    } else {

        if ((peso > max_heap->v[0].peso)) {

            if ((min_heap->n + 1) - max_heap->n >= 2) {
                //printf("D  \n");
                //printf("%d\n", peso);
                max_heap->v[max_heap->n].peso = min_heap->v[0].peso;
                strcpy(max_heap->v[max_heap->n].fruta, min_heap->v[0].fruta);
                max_heap->n += 1;
                transformar_max_heap(max_heap, max_heap->n - 1);

                extrair_min(min_heap);
                transformar_min_heap(min_heap, min_heap->n - 1);

                min_heap->v[min_heap->n].peso = peso;
                strcpy(min_heap->v[min_heap->n].fruta, fruta);
                min_heap->n += 1;
                transformar_min_heap(min_heap, min_heap->n - 1);

            } else {
                //printf("C \n");
                min_heap->v[min_heap->n].peso = peso;
                strcpy(min_heap->v[min_heap->n].fruta, fruta);
                min_heap->n += 1;

                transformar_min_heap(min_heap, min_heap->n - 1);
                //chave +=1;
                min_heap->chave=1;
            }

        } else {

            if ((max_heap->n + 1) - min_heap->n >= 2) {
                //printf("A \n");
                min_heap->v[min_heap->n].peso = max_heap->v[0].peso;
                strcpy(min_heap->v[min_heap->n].fruta, max_heap->v[0].fruta);
                min_heap->n += 1;
                transformar_min_heap(min_heap, min_heap->n - 1);

                extrair_max(max_heap);

                transformar_max_heap(max_heap, max_heap->n-1);

                max_heap->v[max_heap->n].peso = peso;
                strcpy(max_heap->v[max_heap->n].fruta, fruta);
                max_heap->n+=1;

                transformar_max_heap(max_heap, max_heap->n-1);

            } else {
                //printf("B \n");
                max_heap->v[max_heap->n].peso = peso;
                strcpy(max_heap->v[max_heap->n].fruta, fruta);
                max_heap->n += 1;
                transformar_max_heap(max_heap, max_heap->n - 1);

            }
        }

    }

    imprimir_mediana(max_heap, min_heap);

}

// A função libera o espaço de memória do vetor do heap e o próprio heap;
void liberar_memoria_heap(FP* heap){
    free(heap->v);
    free(heap);
}

int main(){
    int n, peso;
    char fruta[20];
    scanf("%d", &n);
    FP* max_heap = criar_vetor(n*2);
    FP* min_heap = criar_vetor(n*2);
    max_heap->v[0].peso = 0;
    min_heap->v[0].peso = 0;
    int chave=0;
    for (int i=0;i<n;i++) {
        scanf("%s", fruta);
        scanf("%d", &peso);

        inserir(max_heap, min_heap, fruta, peso, chave);

    }

    liberar_memoria_heap(max_heap);
    liberar_memoria_heap(min_heap);
}
