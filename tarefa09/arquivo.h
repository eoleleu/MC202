
#ifndef RA213437_ARQUIVO_H
#define RA213437_ARQUIVO_H

/*

Essa estrutura guarda um inteiro 'valor' que guarda o número da região e
um inteiro 'id' que representa tal região. Que serão representados como os
vértices do nosso grafo;
*/
typedef struct vetor* p_vetor;
struct vetor {
    int valor;
    int id;
};

/*
A estrutura armazena o nó da lista de adjacência, esse nó representa a região que o
tal vértice está conectado.
*/
typedef struct node* p_no;
struct node {
    int v;
    int id;
    p_no next;
};


/*
A estrutura comporta um vetor que servirá para guarda os vértices do grafo e
uma lista ligada que servirá para armazenar as regiões que tal vértice está conectado;
*/
typedef struct grafo* p_grafo;
struct grafo {
    p_no *adjacentes;
    p_vetor v;
};


struct imagem {
    int w, h;
    int **pix;
    int **id;
};


/*
A função presume que não ocorrem erros e que
máximo valor de um canal de cor é 255
*/
struct imagem *ler_imagem();


/*
Libera a memória da gerada após ler a imagem;
*/
void liberar_imagem(struct imagem *img);


/*
A função insere na lista de adjacência as regiões que cada vértice está se conectando;
*/
void inserir_na_lista(p_grafo grafo, int adjacente, int pixel, int id_adjacente, int n);


/*
A função percorre toda a matriz dos pixels e insere na lista de adjacência as regiões
que representam as regiões que cada vértice está fazendo ligação;
*/
void inserir_adjacentes(p_grafo grafo, struct imagem *img, int n);


/*
Essa é uma função recursiva que percorre todos os pixel da matriz gerada após o recebimento da entrada
e separa os pixel por id's, ou seja, cada pixel e os que estão em volta que são iguais serão representados
por um id;

Devolve a matriz de regiões com cada pixel e seus semelhantes ao redor representados por um id;
*/
struct imagem* preencher_id(struct imagem *img, int pixel, int identificador, int linha, int coluna);


/*
A função insere no vetor que está no campo grafo todas as regiões com diferentes id's
da imagem, que passarão a ser representadas como vértices do grafo;
 */
void inserir_vetor(int n, p_grafo grafo, struct imagem *img, int linha, int coluna);


/*
A função busca no vetor qual o índice da região que passamos na chamada da função.
*/
int buscar_regiao(int valor, p_grafo grafo, int id);


/*
A função aloca uma estrutura grafo e também os elementos que estão dentro desse campo,
como o vetor que serão armazenados os vértices do grafo e também a lista de adjacência
que serão armazenadas com ligações que cada vértice faz.
*/
p_grafo criar_grafo();


/*
A função gera as todas em distâncias a partir de uma região branca que escolhemos até os outros vértices do grafo;
*/
void buscar_distancia_min(p_grafo grafo, int *vetor, int d_atual, int origem, int id);


/*
A função imprime o resultado de quantas regiões Maria deve passar
*/
void imprimir(p_grafo grafo, int* vetor, int cont);

#endif //RA213437_ARQUIVO_H
