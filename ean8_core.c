#include "ean8_core.h"

const char *L_CODE[10] = {
    "0001101", "0011001", "0010011", "0111101", "0100011",
    "0110001", "0101111", "0111011", "0110111", "0001011"
};

const char *R_CODE[10] = {
    "1110010", "1100110", "1101100", "1000010", "1011100",
    "1001110", "1010000", "1000100", "1001000", "1110100"
};

int calcular_digito_verificador(const char *id) {
    int soma = 0;
    for (int i = 0; i < 7; i++) {
        int digito = id[i] - '0';
        if ((i + 1) % 2 != 0) soma += digito * 3;
        else soma += digito * 1;
    }
    int proximo = (soma % 10 == 0) ? soma : ((soma / 10) + 1) * 10;
    return proximo - soma;
}

int validar_identificador(const char *id) {
    if (strlen(id) != 8) return 0;
    for (int i = 0; i < 8; i++) if (!isdigit(id[i])) return 0;
    return calcular_digito_verificador(id) == (id[7] - '0');
}

ImagemPBM *criar_imagem(int largura, int altura) {
    ImagemPBM *img = (ImagemPBM *)malloc(sizeof(ImagemPBM));
    img->largura = largura;
    img->altura = altura;
    img->dados = (int **)malloc(altura * sizeof(int *));
    for (int i = 0; i < altura; i++) {
        img->dados[i] = (int *)calloc(largura, sizeof(int));
    }
    return img;
}

void liberar_imagem(ImagemPBM *img) {
    if (img) {
        for (int i = 0; i < img->altura; i++) free(img->dados[i]);
        free(img->dados);
        free(img);
    }
}

void salvar_imagem(ImagemPBM *img, const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "w");
    if (!f) { printf("Erro ao criar arquivo.\n"); exit(1); }
    fprintf(f, "P1\n%d %d\n", img->largura, img->altura);
    for (int i = 0; i < img->altura; i++) {
        for (int j = 0; j < img->largura; j++) fprintf(f, "%d", img->dados[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

ImagemPBM *ler_imagem(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) return NULL;
    char tipo[3];
    int w, h;
    fscanf(f, "%2s", tipo);
    if (strcmp(tipo, "P1") != 0) { fclose(f); return NULL; }
    fscanf(f, "%d %d", &w, &h);
    ImagemPBM *img = criar_imagem(w, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int p; fscanf(f, "%1d", &p); img->dados[i][j] = p;
        }
    }
    fclose(f);
    return img;
}