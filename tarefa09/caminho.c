#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1100
#define BRANCA 0xFFFFFF
#include "arquivo.h"

struct imagem *ler_imagem() {
    struct imagem *img;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    scanf("P3 ");
    while ((peek = getchar()) == '#')
        scanf("%*[^\r\n]%*[\r\n]");
    ungetc(peek, stdin);
    assert(scanf("%d %d %*d", &img->w, &img->h) == 2);
    assert(img->pix = malloc(sizeof(*img->pix) * img->h));
    assert(img->id = malloc(sizeof(*img->id) * img->h));
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        assert(img->id[i] = malloc(sizeof(**img->id) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b) == 3);
            img->pix[i][j] = (r << 16) + (g << 8) + b;
            img->id[i][j] = 0;
        }
    }
    return img;
}

void liberar_imagem(struct imagem *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img);
}

void inserir_na_lista(p_grafo grafo, int adjacente, int pixel, int id_adjacente, int n){

    int cont=0;
    while(grafo->v[cont].id != n){
        cont +=1;
    }

    p_no novo = malloc(sizeof (struct node));
    novo->v = adjacente;
    novo->id = id_adjacente;
    novo->next = NULL;

    if(grafo->adjacentes[cont] == NULL){
        grafo->adjacentes[cont] = novo;
    } else {
        int verificador=0;
        p_no aux = grafo->adjacentes[cont];
        //printf("%d  %d\n", aux->v, aux->id);
        while(aux->next != NULL){

            if(aux->v == novo->v && aux->id == novo->id){
                verificador = 1;
            }

            aux = aux->next;

        }

        if(aux->v == novo->v && aux->id == novo->id){
            verificador = 1;
        }
        if(verificador == 0){
            aux->next = novo;
        }
    }


}

void inserir_adjacentes(p_grafo grafo, struct imagem *img, int n){

    for (int i=0;i<img->h; i++){
        for (int j=0;j<img->w;j++){
            if(img->id[i][j] == n){

                if(j-1 >=0){
                    if(img->pix[i][j-1] != img->pix[i][j]){
                        inserir_na_lista(grafo, img->pix[i][j-1], img->pix[i][j], img->id[i][j-1], n);
                    }
                }

                if(j+1 < img->w){
                    if(img->pix[i][j+1] != img->pix[i][j]){
                        inserir_na_lista(grafo, img->pix[i][j+1], img->pix[i][j], img->id[i][j+1], n);

                    }
                }

                if(i-1 >=0){
                    if(img->pix[i-1][j] != img->pix[i][j]){
                        inserir_na_lista(grafo, img->pix[i-1][j], img->pix[i][j], img->id[i-1][j], n);

                    }
                }

                if(i+1 <img->h){
                    if(img->pix[i+1][j] != img->pix[i][j]){
                        inserir_na_lista(grafo, img->pix[i+1][j], img->pix[i][j], img->id[i+1][j], n);

                    }
                }
            }
        }
    }
}

struct imagem* preencher_id(struct imagem *img, int pixel, int identificador, int linha, int coluna){

    if(img->id[linha][coluna]==0){
        //img->id[linha][coluna] = identificador;
        return img;
    }
    if(coluna +1 < img->w){

        if(img->pix[linha][coluna+1] == pixel){
            img->id[linha][coluna+1] = identificador;
            img = preencher_id(img, pixel, identificador, linha, coluna+1);
        }
    }
    if(coluna -1 >=0){

        if(img->pix[linha][coluna-1] == pixel && img->id[linha][coluna-1] == 0){
            img->id[linha][coluna-1] = identificador;
            img = preencher_id(img, pixel, identificador, linha, coluna-1);
        }

    }
    if(linha +1 < img->h){

        if(img->pix[linha+1][coluna] == pixel && img->id[linha+1][coluna] == 0){
            img->id[linha+1][coluna] = identificador;
            img = preencher_id(img, pixel, identificador, linha+1, coluna);
        }

    }
    if(linha -1 >=0){

        if(img->pix[linha-1][coluna] == pixel && img->id[linha-1][coluna] == 0){
            img->id[linha-1][coluna] = identificador;
            img = preencher_id(img, pixel, identificador, linha-1, coluna);
        }
    }

    return img;

}

void inserir_vetor(int n, p_grafo grafo, struct imagem *img, int linha, int coluna){
    int verificador =0;
    for(int i=0;i<MAX;i++){
        if(grafo->v[i].valor == n && grafo->v[i].id == img->id[linha][coluna]){
            verificador =1;
        }
    }

    if(verificador==0){
        for(int i=0;i<MAX;i++){
            if(grafo->v[i].valor == 0){
                grafo->v[i].valor = n;
                grafo->v[i].id = img->id[linha][coluna];
                break;
            }
        }
    }
}

int buscar_regiao(int valor, p_grafo grafo, int id){
    int k=0;
    while(grafo->v[k].valor!= 0){
        if(grafo->v[k].valor==valor && grafo->v[k].id==id){
            break;
        }
        k+=1;
    }

    return k;
}

p_grafo criar_grafo(){

    p_grafo grafo = malloc(sizeof(struct grafo));
    grafo->v = malloc(sizeof(struct vetor) * MAX);

    for(int k=0; k<MAX;k++){
        grafo->v[k].valor =0;
        grafo->v[k].id= -1;
    }

    grafo->adjacentes = malloc(sizeof(p_no) * MAX);

    for(int i=0; i<MAX;i++){
        grafo->adjacentes[i] = NULL;
    }
    return grafo;
}

void buscar_distancia_min(p_grafo grafo, int *vetor, int d_atual, int origem, int id){

    p_no aux = grafo->adjacentes[origem];

    while(aux != NULL){
        int n = buscar_regiao(aux->v, grafo, aux->id);

        if(vetor[n]== -1){
            vetor[n]=d_atual+1;
            buscar_distancia_min(grafo, vetor, d_atual+1, n, aux->id);
        } else {
            if(vetor[n]>d_atual+1){
                vetor[n] = d_atual+1;
                buscar_distancia_min(grafo, vetor, d_atual+1, n, aux->id);
            }
        }
        aux = aux->next;
    }
}

void imprimir(p_grafo grafo, int* vetor, int cont){
    int r_branca=0;
    for(int i=0;i<cont;i++){
        if(grafo->v[i].valor == BRANCA){
            r_branca+=1;
        }
        if(r_branca==2){
            printf("Maria deve memorizar %d regioes.\n", vetor[i]-1);
            break;
        }
    }
}

int main(int argc, char *argv[]) {

    // lê a imagem da entrada e transforma em uma matriz;
    struct imagem *img = ler_imagem();

    int identificador=0;
    for(int i=0;i<img->h;i++){
        for(int j=0;j<img->w;j++){
            if(img->id[i][j] == 0){
                img->id[i][j] = identificador;
                img = preencher_id(img, img->pix[i][j], identificador, i, j);
                identificador+=1;
            }
        }
    }

    p_grafo grafo = criar_grafo();

    for (int i=0;i<img->h; i++){
        for (int j=0;j<img->w;j++){
            inserir_vetor(img->pix[i][j], grafo, img, i, j);
        }
    }

    int cont;
    for(int i=0;i<identificador;i++){
        inserir_adjacentes(grafo, img, i);
    }

    int cont2 =0;
    while(grafo->v[cont2].valor != BRANCA){
        cont2+=1;
    }

    cont=0;
    while(grafo->v[cont].valor != 0){
        cont+=1;
    }

    int *vetor = malloc(sizeof (int)*cont);
    for(int i=0;i<cont;i++){
        vetor[i] = -1;
    }

    vetor[cont2] = 0;
    buscar_distancia_min(grafo, vetor, 0, cont2, grafo->v[cont2].id);

    imprimir(grafo, vetor, cont);
    liberar_imagem(img);
    return 0;
}


