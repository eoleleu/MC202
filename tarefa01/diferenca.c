#include <stdio.h>

int main() {
    int a, b;
    int lista1[200];
    int lista2[200];
    int listaPrinc[200];

    for (int u=0; u<500;u++){
        listaPrinc[u] = -1;
    }
    scanf("%d %d", &a, &b);
    //printf("%d", a);
    for (int i=0; i<a; i++){
        scanf("%d", &lista1[i]);
        //printf("ENTROU");
    }
    for (int j=0; j<b; j++){
        scanf("%d", &lista2[j]);
    }
    int w;
    int index=0;
    int max1=0;
    for (int q=0; q<a;q++){
        if (lista1[q]>max1){
            max1 = lista1[q];
        }
        w = lista1[q];
        //printf("%d\n", w);
        listaPrinc[w]=w;
        index+=1;
    }
    //printf("%d", listaPrinc[0]);
//    for (int o=0; o<a;o++){
//        printf("%d ", listaPrinc[o]);
//    }
    int e;
    int max2 = 0;
    for (int r=0; r<b;r++){
        if (lista2[r]>max2){
            max2 = lista2[r];
        }
        e = lista2[r];
        //printf("%d ", e);
        if (listaPrinc[e] == e){
            listaPrinc[e] = -1;
        } else {
            listaPrinc[e]=e;
            index+=1;
        }

    }
    int maxPrinc;
    if (max1>max2){
        maxPrinc=max1;
    } else{
        maxPrinc=max2;
    }

    for (int o=0; o<maxPrinc+1;o++){
        if(listaPrinc[o]!= -1) {
            printf("%d ", listaPrinc[o]);
        }
    }

    //printf("alalal");
//    for (int p =0; p<50;p++){
//        printf("%d ", listaPrinc[p]);
//    }
}