#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 500

// ARMAZENA O NOME DOS PACIENTES, O DIAGNÓSTICO E O CRM DO MÉDICO QUE IRÁ ATENDÊ-LA
typedef struct {
    char nome[30];
    char cid[50];
    int crm;
} consulta;

// ARMAZENA O NOME DOS PACIENTE QUE PRECISAM SER REMOVIDOS
typedef struct {
    char nome_remover[30];
} consulta_removida;

// ARMAZENA OS NOMES E OS CRM'S DOS MÉDICOS QUE FORAM LIDOS NO ARQUIVO MEDICOS.TXT
typedef struct {
    char nome[30];
    int crm;
} medico;

// ARMAZENA O CÓDIGO DA DOENÇA E O NOME DA DOENÇA QUE FORAM LIDOS NO ARQUIVO DOENÇAS.TXT
typedef struct {
    char doenca[100];
    char cid[50];
} doencas;

// ARMAZENA OS NOMES E OS CÓDIGOS DA DOENÇA DOS PACIENTE QUE PRECISAM SER ALTERADOS
typedef struct{
    char nome[50];
    char cid[50];
} consulta_alterar;

// IMPRIME O TEXTO DE SAÍDA
void imprimir_saida(consulta_removida  *paciente_removido, consulta *paciente, medico *medicos, doencas *doenca, int n_doencas, int n_medico, int g, int m){
    for (int i=0;i<g;i++) {
        int contador = 0;
        for (int j = 0; j < m; j++) {
            if (strcmp(paciente_removido[j].nome_remover, paciente[i].nome) == 0) {
                contador += 1;
            }
        }
        if (contador == 0) {
            for (int c = 0; c < n_medico; c++) {
                if (paciente[i].crm == medicos[c].crm) {
                    for (int b = 0; b < n_doencas; b++) {
                        if (strcmp(paciente[i].cid, doenca[b].cid) == 0) {
                            printf("%s atendido por %s:%s\n", paciente[i].nome, medicos[c].nome, doenca[b].doenca);
                        }
                    }
                }
            }
        }
    }
}

// COMPARA CADA NOMES DOS PACIENTES, CASO O NOME DO PACIENTE REGISTRADO FOR IGUAL AO NOME DO PACIENTE QUE PRECISA SER ALTERAR, MUDA-SE O DIAGNÓSTICO DELE
void alterar_diagnostico_do_paciente(consulta *paciente, consulta_alterar  *paciente_alterado, int a, int g){
    for(int i=0; i<a;i++){
        for(int j=0;j<g;j++){
            if(strcmp(paciente[j].nome, paciente_alterado[i].nome)==0){
                strcpy(paciente[j].cid, paciente_alterado[i].cid);
            }
        }
    }
}

// ORDENA OS NOMES DOS PACIENTE QUE SERÃO CONSULTADOS COM BASE NA ORDEM ALFABÉTICA
void ordenar_nomes_dos_pacientes(consulta *paciente, int g){
    consulta temporario;
    for(int i=0;i<g;i++){
        for (int j=0; j<g-i-1;j++){
            if (strcmp(paciente[j].nome, paciente[j+1].nome)>0){
                temporario = paciente[j];
                paciente[j] = paciente[j+1];
                paciente[j+1]=temporario;
            }
        }
    }
}

// RECEBE TODAS AS ENTRADAS, E GUARDA CADA ENTRAR DEPENDENDO DO COMANDO EM SEUS RESPECTIVOS STRUCT'S
void receber_entradas(int *verificador, int *g, int *m, int *a, char *comando, consulta *paciente, consulta_removida *paciente_removido, consulta_alterar *paciente_alterado){

    while (*verificador==1){
        scanf("%s", comando);

        if(strcmp(comando, "fechar")==0){
            *verificador=0;
        }
        if(strcmp(comando, "registrar")==0){

            scanf("%s", paciente[*g].nome);
            scanf("%s", paciente[*g].cid);
            scanf("%d", &paciente[*g].crm);
            *g+=1;

        } else if(strcmp(comando, "remover")==0) {
            scanf("%s", paciente_removido[*m].nome_remover);
            *m+=1;
        } else if(strcmp(comando, "alterar")==0){
            scanf("%s", paciente_alterado[*a].nome);
            scanf("%s", paciente_alterado[*a].cid);
            *a+=1;
        }
    }

}

int main(){
    int n, g=0, m=0, a=0, verificador=1;

    char *abrir = malloc(MAX * sizeof(char));
    char *comando = malloc(MAX * sizeof(char));
    scanf("%s %d", abrir, &n);
    consulta *paciente = malloc(MAX*sizeof(consulta*));
    consulta_removida *paciente_removido = (consulta_removida*)malloc(MAX*sizeof(consulta_removida));
    consulta_alterar *paciente_alterado = (consulta_alterar *)malloc(MAX*sizeof(consulta_alterar));

    receber_entradas(&verificador, &g, &m, &a, comando, paciente, paciente_removido, paciente_alterado);

    ordenar_nomes_dos_pacientes(paciente, g);

    // LÊ O ARQUIVO MEDICO.TXT E ARMAZENA OS CRM'S E NOMES DOS MÉDICOS NA STRUCT 'MEDICOS'
    FILE *fp = fopen("dados/medicos.txt", "r");
    if (fp == NULL) {
        perror("Nao foi possivel abrir medicos.txt");
    }

    int n_medico;

    fscanf(fp, "%d", &n_medico);

    medico *medicos = (medico*)malloc(n_medico*sizeof(medico));

    for (int k = 0; k < n_medico; k++) {
        fscanf(fp, "%d", &medicos[k].crm);
        fscanf(fp, "%s", medicos[k].nome);
    }
    fclose(fp);

    // LÊ O ARQUIVO DOENÇAS.TXT E ARMAZENA O CÓDIGO DO DIAGNÓSTICO E O NOME DA DOENÇA EM UMA STRUCT
    FILE *fd = fopen("dados/doencas.txt", "r");
    if (fd == NULL) {
        perror("Nao foi possivel abrir medicos.txt");
    }

    int n_doencas;

    fscanf(fd, "%d", &n_doencas);

    doencas *doenca = (doencas*)malloc(n_doencas*sizeof(doencas));

    for (int k = 0; k < n_doencas; k++) {
        fscanf(fd, "%s", doenca[k].cid);
        fscanf(fd, "%[^\n]", doenca[k].doenca);
    }
    fclose(fd);

    alterar_diagnostico_do_paciente(paciente, paciente_alterado, a, g);

    imprimir_saida(paciente_removido, paciente, medicos, doenca, n_doencas, n_medico, g, m);

    //LIBERA A MEMÓRIA
    free(abrir);
    free(comando);
    free(paciente);
    free(paciente_removido);
    free(paciente_alterado);
    free(medicos);
    free(doenca);

    return 0;
}