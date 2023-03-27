#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define PRETA 0
#define BRANCA 0xFFFFFF

struct imagem {
    int w, h;
    int **pix;
};

// função presume que não ocorrem erros e que
// máximo valor de valor de um canal de cor é 255
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
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b) == 3);
            img->pix[i][j] = (r << 16) + (g << 8) + b;
        }
    }
    return img;
}
void salvar_imagem(struct imagem *img, char *file) {
    int i, j;
    FILE *fp = fopen(file, "w");
    fprintf(fp, "P3\n%d %d %d\n", img->w, img->h, 255);
    for (i = 0; i < img->h; i++) {
        for (j = 0; j < img->w; j++) {
            int r, g, b;
            int pix = img->pix[i][j];
            r = pix >> 16 & 0xFF;
            g = pix >> 8 & 0xFF;
            b = pix & 0xFF;
            fprintf(fp, "%d %d %d\n", r, g, b);
        }
    }
    fclose(fp);
}
void liberar_imagem(struct imagem *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img);
}

// exemplo de como usar as funções:
// lê uma imagem e cria um novo
// arquivo com metade da imagem pintada
int main(int argc, char *argv[]) {
    int i, j;

    struct imagem *img = ler_imagem();
    for (i = 0; i < img->h; i++)
        for (j = 0; j < img->w / 2; j++)
            img->pix[i][j] = BRANCA;

    salvar_imagem(img, "pintada.ppm");
    liberar_imagem(img);
    return 0;
}
