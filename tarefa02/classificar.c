#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
typedef struct {
    //char nome_completo[30];
    char nome[30];
    char sobrenome[30];

}pessoas;

// FAZ UMA COMPARAÇÃO DE TODOS OS SOBRENOMES QUE ESTÃO ARMAZENADOS NA STRUCT PESSOAS, CASO FOREM IGUAIS E O ÍNDICE DIFERENTE, MANDO IMPRIMIR
void imprimir_resultado_parentes(pessoas *nome_completo, int n){
    for (int i=0; i<n;i++){
        int cont=0;
        for (int j=0;j<n;j++){
            if(i!=j && strcmp(nome_completo[i].sobrenome, nome_completo[j].sobrenome)==0 && cont==0){
                printf("%s%s", nome_completo[i].nome, nome_completo[i].sobrenome);
                cont+=1;
            }

        }
    }
}

// COM OS NOMES DAS PESSOAS ORDENADOS COM BASE EM SEUS SOBRENOMES, DEVE-SE ORDENAR O NOME ANTES DO UNDERLINE
void ordenar_nomes_dos_sobrenomes_ordenados(pessoas *nome_completo, int n){
    pessoas temporario2;
    for(int i=0;i<n;i++){
        for (int j=0; j< n-1;j++){
            if ((strcmp(nome_completo[j].sobrenome, nome_completo[j+1].sobrenome)==0) && (strcmp(nome_completo[j].nome, nome_completo[j+1].nome)>0)){
                temporario2 = nome_completo[j];
                nome_completo[j] = nome_completo[j+1];
                nome_completo[j+1]=temporario2;

            }
        }
    }
}

// COLOCA EM ORDEM ALFABÉTICA OS NOMES DAS PESSOAS PELO SOBRENOME
void ordenacao_parentes(pessoas *nome_completo, int n){
    pessoas temporario2;
    for(int i=0;i<n;i++){
        for (int j=0; j< n-1;j++){
            if (strcmp(nome_completo[j].sobrenome, nome_completo[j+1].sobrenome)>0){
                temporario2 = nome_completo[j];
                nome_completo[j] = nome_completo[j+1];
                nome_completo[j+1]=temporario2;
            }
        }
    }
}

// IMPRIME O RESULTADO COMPARANDO TODOS OS NOMES ANTES DO UNDERLINE ARMAZENADOS NA STRUCT PESSOAS, CASO FOREM IGUAIS E ÍNDICE DIFERENTE, MANDO IMPRIMIR
void imprimir_resultado_homonimos(pessoas *nome_completo, int n){
    for (int i=0; i<n;i++){
        int cont=0;
        for (int j=0;j<n;j++){
            if(i!=j && strcmp(nome_completo[i].nome, nome_completo[j].nome)==0 && cont==0){
                printf("%s%s", nome_completo[i].nome, nome_completo[i].sobrenome);
                cont+=1;
            }

        }
    }
}

// VISTO QUE OS NOMES ANTES DO UNDERLINE ESTÃO ORDENADOS, A FUNÇÃO ORDENADA O SOBRENOME
void ordenar_sobrenomes_dos_nomes_ordenados(pessoas *nome_completo, int n){
    pessoas temporario;
    for(int i=0;i<n;i++){
        for (int j=0; j< n-1;j++){
            if ((strcmp(nome_completo[j].nome, nome_completo[j+1].nome)==0) && (strcmp(nome_completo[j].sobrenome, nome_completo[j+1].sobrenome)>0)){
                temporario = nome_completo[j];
                nome_completo[j] = nome_completo[j+1];
                nome_completo[j+1]=temporario;

            }
        }

    }
}

// ORDENA OS NOMES DOS PACIENTE COM BASE NO NOME ANTES DO UNDERLINE
void ordenacao_homonimos(pessoas *nome_completo, int n){
    pessoas temporario;
    for(int i=0;i<n;i++){
        for (int j=0; j< n-1;j++){
            if (strcmp(nome_completo[j].nome, nome_completo[j+1].nome)>0){
                temporario = nome_completo[j];
                nome_completo[j] = nome_completo[j+1];
                nome_completo[j+1]=temporario;
            }
        }

    }
}

// RECEBE TODAS AS ENTRADAS E ARMAZENA O NOME E O SOBRENOME NA STRUCT PESSOAS
int receber_entradas(pessoas *nome_completo, char *comando){
    int n;
    scanf("%d", &n);
    scanf("%s", comando);
    // recebo as entradas, as string antes do underline vai para a estrutura nome e a string
    // após o underline irá para a estrutura sobrenome
    for (int i=0; i<n;i++){
        scanf("%[^_] %s", nome_completo[i].nome, nome_completo[i].sobrenome);
    }
    return n;
}

int main(){

    int n;
    char *comando = malloc(MAX * sizeof(char));
    pessoas *nome_completo = (pessoas*)malloc(MAX*sizeof(pessoas));

    n = receber_entradas(nome_completo, comando);

    if(strcmp(comando, "homonimos")==0){
        // ordena as pessoas com base em seus nomes antes do underline
        ordenacao_homonimos(nome_completo, n);

        // ordenada os nomes repetidos com base nos seus sobrenomes
        ordenar_sobrenomes_dos_nomes_ordenados(nome_completo, n);

        // imprime o resultado caso os nomes sejam iguais e os sobrenomes sejam diferentes
        imprimir_resultado_homonimos(nome_completo, n);
    }

    if(strcmp(comando, "parentes")==0){
        // ordena as pessoas com base em seus respectivos sobrenomes
        ordenacao_parentes(nome_completo, n);

        // ordenada os sobrenomes repetidos com base no seus respectivos nomes antes do _
        ordenar_nomes_dos_sobrenomes_ordenados(nome_completo, n);

        // imprime o resultado caso os sobrenomes sejam iguais
        imprimir_resultado_parentes(nome_completo, n);
    }

    // LIBERAÇÃO DA MEMÓRIA
    free(comando);
    free(nome_completo);

    return 0;
}
