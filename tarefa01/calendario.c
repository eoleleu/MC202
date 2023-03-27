#include <stdio.h>
#include <math.h>

int main() {
    int dia, mes, ano;
    int diaMes, NmesesAno;
    int diasrest;
    int salvarDia;
    scanf("%d/%d/%d", &dia, &mes, &ano);

    scanf("%d %d", &diaMes, &NmesesAno);

    scanf("%d", &diasrest);

    int decimal = 0;
    int resto;
    salvarDia = diasrest;

    if(diasrest != 0){
        for (int i = 0; i < 8; i++) {
            resto = diasrest - ((diasrest / 10) * 10);
            diasrest = diasrest / 10;
            decimal = decimal + resto * pow(6, i);
        }
    }

    //printf("%d\n", decimal);

    if (decimal != 0){
        decimal = decimal + dia;
        //printf("%d\n", decimal);
        if (decimal % diaMes == 0 && diaMes != NmesesAno){
            decimal = diaMes;
        } else {
            do {
                decimal = decimal - diaMes;
                mes += 1;
            } while (decimal > diaMes);
        }
        //printf("%d\n", decimal);
        if (diaMes == NmesesAno && diaMes<9999) {
            ano = decimal;
        }


        //printf("%d\n", decimal);
        //printf("%d\n", mes);
        do {

            if (mes>NmesesAno){
                mes = mes - NmesesAno;
                ano +=1;
            }

        } while (mes>NmesesAno);
    }
    //printf("%d\n", decimal);
    //printf("%d\n", diasrest);
    if (salvarDia==0){
        printf("%d/%d/%d", dia, mes, ano);
    }else {
        printf("%d/%d/%d", decimal, mes, ano);
    }


}

