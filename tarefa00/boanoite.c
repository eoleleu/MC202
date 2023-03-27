#include <stdio.h>
int main(){
    int n;
    char nome[30];
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }
}
