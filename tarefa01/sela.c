#include <stdio.h>

int main() {
    int i, j;
    int matriz[100][100];

    scanf("%d %d", &i, &j);

    for (int linha = 0; linha < i; linha++) {
        for (int col = 0; col < j; col++) {
            scanf("%d", &matriz[linha][col]);
        }
    }
    int min_linha;
    int max_coluna;
    int coluna_min_linha;
    int verificador = 0;
    int indecex;
    for (int l = 0; l < i; l++) {
        min_linha = matriz[l][0];
        for (int k = 0; k < j; k++) {
            if (matriz[l][k] <= min_linha) {
                min_linha = matriz[l][k];
                coluna_min_linha = k;

            }
        }
        max_coluna = matriz[0][coluna_min_linha];
        for (int s = 0; s < i; s++) {
            if (matriz[s][coluna_min_linha] >= max_coluna) {
                max_coluna = matriz[s][coluna_min_linha];
                indecex = s;
            }
        }
        if (min_linha == max_coluna) {
            verificador = 1;
            //printf("(%d %d) eh ponto de sela com valor %d", indecex, coluna_min_linha,  min_linha);
            break;
        } else {
            verificador = -1;
        }


    }
    int a=0;
    for (int y=0;y<j;y++){
        if (matriz[indecex][coluna_min_linha]==matriz[indecex][y]){
            a+=1;
        }
    }
    int b=0;
    for (int z=0;z<i;z++){
        if (matriz[indecex][coluna_min_linha]==matriz[coluna_min_linha][z]){
            b+=1;
        }
    }
    //printf("%d\n", matriz[indecex][coluna_min_linha]);
    //printf("%d\n", a);
    //printf("%d\n", b);
    if (a>1){
        verificador =0;
    }
    if(b>1 && matriz[indecex][coluna_min_linha]>0){
        verificador=0;
    }
    if (verificador==1){
        printf("(%d, %d) eh ponto de sela com valor %d", indecex, coluna_min_linha,  min_linha);
    } else {
        printf("nao existe ponto de sela");
    }

}
