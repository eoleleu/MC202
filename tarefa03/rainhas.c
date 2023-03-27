#include <stdio.h>
#include <stdlib.h>

// LIBERA O ESPAÇO DE MEMÓRIA ALOCADO
// Parâmetros -> tamanho (int): extensão de casas do tabuleiro.
// tabuleiro(matriz)
void free_array(int tamanho, char **tabuleiro){
    for (int i=0; i<tamanho;i++){
        free(tabuleiro[i]);
    }
}

// A função imprime a quantidade de peões utilizados para resolver e
// o tabuleiro, com as rainhas e peões nas posições corretas.
// Parâmetros -> qtd_peoes(int): quantidade total de peões utilizados na solução
// qtd_rainhas(int): quantidade total de rainhas que precisavam ser colocadas no tabuleiro
void imprimir_tabuleiro(char **tabuleiro, int tamanho, int qtd_peoes, int qtd_rainhas){

    int numero_rainhas=0;
    int numero_peoes=0;

    for (int i=0;i<tamanho;i++){
        for (int j=0;j<tamanho;j++){
            if(tabuleiro[i][j]=='r'){
                numero_rainhas+=1;
            }
        }
    }
    for(int i=0;i<tamanho;i++){
        for (int j=0;j<tamanho;j++){
            if(tabuleiro[i][j]=='p'){
                numero_peoes+=1;
            }
        }
    }
    if(numero_rainhas==qtd_rainhas && numero_peoes==qtd_peoes){
        printf("%d\n", qtd_peoes);
        for (int i=0;i<tamanho;i++){
            for(int j=0;j<tamanho;j++){
                printf("%c ", tabuleiro[i][j]);
            }
            printf("\n");
        }
        free_array(tamanho, tabuleiro);
        free(tabuleiro);
        exit(0);
    }
}

// A função percorre total as linhas de determinada coluna para checar se há algum peão nela.
// Parâmetros: tamanho (int): extensão de casas do tabuleiro
// coluna(int): coluna que deseja verificar
// Retorno -> caso a função encontre algum peão na coluna retorna 1, caso não encontre nenhum peão OU a
// coluna que deseja ser verificada não foi alocada também retorna 0
int verificar_se_existe_peao_na_coluna(char **tabuleiro, int tamanho, int coluna){

    // returna 0 para não verificar uma coluna que não exista, assim evitando erro de memória
    if (coluna>=tamanho){
        return 0;
    }

    for (int i=0;i<tamanho;i++){
        if (tabuleiro[i][coluna]=='p'){
            return 1;
        }
    }

    return 0;
}

// A função percorre total as casas em volta de determinada posição para verificar
// se alguma rainha ataca tal posição, além disso, verifica os peões que defende a posição
// Parâmetros -> linha(int): posição horizontal que deseja ser verificada
// coluna(int): posição vertical que deseja ser verificada
//Retorno -> 0 caso encontre uma rainha que ataca aquela posição ou 1 caso não encontre nenhuma
// rainha que ataque.
int pode_colocar_rainha(char **tabuleiro, int tamanho, int linha, int coluna){
    int i, j;

    // returna 0 para não verificar uma coluna que não exista, assim evitando erro de memória
    if (coluna>=tamanho){
        return 0;
    }
    // retorna 0 para não colocar em uma posição que já exista uma peça
    if (tabuleiro[linha][coluna]=='r' || tabuleiro[linha][coluna]=='p'){
        return 0;
    }
    // verifica a parte esquerda da linha
    for (i=coluna-1;i>=0;i--){
        if (tabuleiro[linha][i]=='r'){
            return 0;
        } else if(tabuleiro[linha][i]=='p'){
            break;
        }
    }

    // verifica a parte de cima da coluna
    for(i=linha-1;i>=0;i--){
        if(tabuleiro[i][coluna]== 'r'){
            return 0;
        } else if(tabuleiro[i][coluna]== 'p'){
            break;
        }
    }
    // verifica a parte debaixo da coluna
    for(i=linha+1;i<tamanho;i++){
        if(tabuleiro[i][coluna]== 'r'){
            return 0;
        }else if(tabuleiro[i][coluna]== 'p'){
            break;
        }
    }
    // verifica na diagonal superior esquerda
    for( i=linha, j=coluna;i>=0 && j>=0;i--, j--){
        if(tabuleiro[i][j]=='r'){
            return 0;
        } else if(tabuleiro[i][j]=='p') {
            break;
        }
    }
    // verifica na diagonal inferior esquerda
    for(i=linha, j=coluna;i<tamanho && j>=0;i++,j--){
        if(tabuleiro[i][j]=='r'){
            return 0;
        } else if(tabuleiro[i][j]=='p'){
            break;
        }
    }

    return 1;
}

// A função recursiva que encontra a solução do problema utilizando backtracking, ela encerra quando
// a quantidade de rainhas que já colocamos for igual à quantidade de rainhas que devem ser colocadas.
// Além disso, caso ela tenha colocado uma rainha em determinada coluna e encontre um peão nessa mesma
// coluna, é feita uma nova chamada já que precisamos colocar outro peão nessa mesma coluna
// Parâmetros -> coluna(int): coluna que estamos percorrendo para colocar uma rainha e verificar se existe peão
// qtd_rainhas(int): quantidade de rainhas que precisam ser colocadas
// r(int): quantidade de rainhas que já posicionamos até o momento
// qtd_peoes(int): quantidade de peões que já colocamos no tabuleiro e que estamos utlizando para encontrar o solução
void solucao(char **tabuleiro, int tamanho, int qtd_rainhas,int qtd_peoes, int coluna, int r){

    if(qtd_rainhas==r){
        imprimir_tabuleiro(tabuleiro, tamanho, qtd_peoes, qtd_rainhas);

    }
    for(int i=0;i<tamanho;i++){

        if(pode_colocar_rainha(tabuleiro, tamanho, i, coluna)==1){

            tabuleiro[i][coluna]='r';
            // percorre a coluna que possui peão novamente, a fim de colocar mais uma rainha nessa coluna
            if(verificar_se_existe_peao_na_coluna(tabuleiro, tamanho, coluna)==1) {
                solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, coluna,r+1);
            } else {
                solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, coluna+1, r+1);
            }
            tabuleiro[i][coluna]= '.';
        }


    }

    // caso ele percorra a coluna que possui peão novamente e não encontre nenhuma solução, obrigamos a ir para a próxima coluna
    if(verificar_se_existe_peao_na_coluna(tabuleiro, tamanho, coluna)== 1){
        solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, coluna+1, r);
    }


}

// A função posiciona 0, 1, 2, 3, 4 ou 5 peões no tabuleiro em total as posições
// forem necessárias para encontrar a solução utilizando backtracking
// Parâmetros -> qtd_peoes(int): número de peões que estamos fazendo a repetição na função main
// qtd_rainhas(int): quantidade de rainhas que precisam ser colocadas
void peoes_possiveis(char **tabuleiro, int tamanho, int qtd_peoes, int qtd_rainhas){
    int p1_linha, p1_coluna, p2_linha, p2_coluna, p3_linha, p3_coluna, p4_linha, p4_coluna, p5_linha, p5_coluna;

    if(qtd_peoes == 0 && tamanho==qtd_rainhas){
        solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
    } else if(qtd_peoes == 1){
        for(int a = 0; a < (tamanho * tamanho); a++){
            p1_linha = a / tamanho;
            p1_coluna = a % tamanho;
            tabuleiro[p1_linha][p1_coluna] = 'p';
            solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
            tabuleiro[p1_linha][p1_coluna] = '.';
        }
    } else if (qtd_peoes == 2){

        for (int a = 0; a < (tamanho * tamanho) - 1; a++){
            p1_linha = a / tamanho;
            p1_coluna = a % tamanho;
            tabuleiro[p1_linha][p1_coluna] = 'p';
            for (int b = a + 1; b < (tamanho * tamanho); b++){
                p2_linha = b / tamanho;
                p2_coluna = b % tamanho;
                tabuleiro[p2_linha][p2_coluna] = 'p';
                solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
                tabuleiro[p2_linha][p2_coluna] = '.';
            }
            tabuleiro[p1_linha][p1_coluna] = '.';
        }

    } else if (qtd_peoes == 3){
        for (int a = 0; a < (tamanho * tamanho) - 2; a++){
            p1_linha = a / tamanho;
            p1_coluna = a % tamanho;
            tabuleiro[p1_linha][p1_coluna] = 'p';
            for (int b = a + 1; b < (tamanho * tamanho) - 1; b++){
                p2_linha = b / tamanho;
                p2_coluna = b % tamanho;
                tabuleiro[p2_linha][p2_coluna] = 'p';
                for (int c = b + 1; c < (tamanho * tamanho); c++){
                    p3_linha = c / tamanho;
                    p3_coluna = c % tamanho;
                    tabuleiro[p3_linha][p3_coluna] = 'p';
                    solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
                    tabuleiro[p3_linha][p3_coluna] = '.';
                }
                tabuleiro[p2_linha][p2_coluna] = '.';
            }
            tabuleiro[p1_linha][p1_coluna] = '.';
        }
    } else if (qtd_peoes == 4){
        for (int a = 0; a < (tamanho * tamanho) - 3; a++){
            p1_linha = a / tamanho;
            p1_coluna = a % tamanho;
            tabuleiro[p1_linha][p1_coluna] = 'p';
            for (int b = a + 1; b < (tamanho * tamanho) - 2; b++){
                p2_linha = b / tamanho;
                p2_coluna = b % tamanho;
                tabuleiro[p2_linha][p2_coluna] = 'p';
                for (int c = b + 1; c < (tamanho * tamanho) - 1; c++){
                    p3_linha = c / tamanho;
                    p3_coluna = c % tamanho;
                    tabuleiro[p3_linha][p3_coluna] = 'p';
                    for ( int d = c + 1; d < (tamanho * tamanho); d++){
                        p4_linha = d / tamanho;
                        p4_coluna = d % tamanho;
                        tabuleiro[p4_linha][p4_coluna] = 'p';
                        solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
                        tabuleiro[p4_linha][p4_coluna] = '.';
                    }
                    tabuleiro[p3_linha][p3_coluna] = '.';
                }
                tabuleiro[p2_linha][p2_coluna] = '.';
            }
            tabuleiro[p1_linha][p1_coluna] = '.';
        }
    } else if (qtd_peoes == 5){
        for (int a = 0; a < (tamanho * tamanho) - 4; a++){
            p1_linha = a / tamanho;
            p1_coluna = a % tamanho;
            tabuleiro[p1_linha][p1_coluna] = 'p';
            for (int b = a + 1; b < (tamanho * tamanho) - 3; b++){
                p2_linha = b / tamanho;
                p2_coluna = b % tamanho;
                tabuleiro[p2_linha][p2_coluna] = 'p';
                for (int c = b + 1; c < (tamanho * tamanho) - 2; c++){
                    p3_linha = c / tamanho;
                    p3_coluna = c % tamanho;
                    tabuleiro[p3_linha][p3_coluna] = 'p';
                    for (int d = c + 1; d < (tamanho * tamanho) - 1; d++){
                        p4_linha = d / tamanho;
                        p4_coluna = d % tamanho;
                        tabuleiro[p4_linha][p4_coluna] = 'p';
                        for (int e = d + 1; e < (tamanho * tamanho); e++){
                            p5_linha = e / tamanho;
                            p5_coluna = e % tamanho;
                            tabuleiro[p5_linha][p5_coluna] = 'p';
                            solucao(tabuleiro, tamanho, qtd_rainhas, qtd_peoes, 0, 0);
                            tabuleiro[p5_linha][p5_coluna] = '.';
                        }
                        tabuleiro[p4_linha][p4_coluna] = '.';
                    }
                    tabuleiro[p3_linha][p3_coluna] = '.';
                }
                tabuleiro[p2_linha][p2_coluna] = '.';
            }
            tabuleiro[p1_linha][p1_coluna] = '.';
        }
    }
}


// A função verifica matematicamente se a solução existe com base nas quantidades de rainhas.
// Caso o tamanho do tabuleiro seja par, ele não terá solução ser a quantidade de rainhas
// que precisam ser colocadas for maior que o tamanho do tabuleiro ao quadrado dividido por quatro.
// Caso o tamanho do tabuleiro for ímpar, não terá solução caso a quantidade rainhas for maior que
// ((tamanho+1)^2)/4
// Parâmetro: tamanho (int): extensão de casas do tabuleiro
// qtd_rainhas(int): quantidade de rainhas que precisam ser colocadas
int verificar_se_solucao_existe(int tamanho, int qtd_rainhas){
    if(tamanho%2==0){
        if(qtd_rainhas>(tamanho*tamanho)/4){
            printf("-1");
            return 0;
            //exit(0);
        }
    } else{
        if(qtd_rainhas>(tamanho+1)*(tamanho+1)/4){
            printf("-1");
            return 0;
            //exit(0);
        }
    }
    return 1;
}

int main(){
    int qtd_rainhas, tamanho;
    // recebe as entradas
    scanf("%d %d", &qtd_rainhas, &tamanho);

    //cria o tabuleiro
    char **tabuleiro;
    tabuleiro = malloc(tamanho *sizeof(char*));
    for(int i=0; i<tamanho;i++){
        tabuleiro[i] = malloc(tamanho * sizeof(char));
    }
    // coloca pontos em todas as posições do tabuleiro
    for (int i=0;i<tamanho;i++){
        for (int j=0;j<tamanho;j++){
            tabuleiro[i][j] = '.';
        }
    }

    if(verificar_se_solucao_existe(tamanho, qtd_rainhas)==0){
        free_array(tamanho, tabuleiro);
        free(tabuleiro);
        exit(0);
    }

    // iteração que coloca determinada quantidade de peões no tabuleiro
    for(int qtd_peoes=0; qtd_peoes<=5; qtd_peoes++){
        peoes_possiveis(tabuleiro, tamanho, qtd_peoes, qtd_rainhas);
    }


}

