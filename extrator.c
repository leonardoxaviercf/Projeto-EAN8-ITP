#include <stdio.h>
#include "ean8_core.h"
#include "ean8_extracao.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.pbm>\n", argv[0]);
        return 1;
    }

    ImagemPBM *img = ler_imagem(argv[1]);
    if (!img) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    char resultado[9];
    if (extrair_ean8(img, resultado)) {
        printf("%s\n", resultado);
    } else {
        printf("Erro: Nao foi possivel identificar um codigo valido.\n");
    }

    liberar_imagem(img);
    return 0;
}