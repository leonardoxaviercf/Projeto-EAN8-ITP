#include "ean8_geracao.h"

ImagemPBM *gerar_imagem_ean8(const char *identificador, int espacamento, int ppa, int altura) {
    // Monta string binária
    char binario[68] = "";
    strcat(binario, "101");
    for (int i = 0; i < 4; i++) strcat(binario, L_CODE[identificador[i] - '0']);
    strcat(binario, "01010");
    for (int i = 4; i < 8; i++) strcat(binario, R_CODE[identificador[i] - '0']);
    strcat(binario, "101");

    int largura_total = (67 * ppa) + (2 * espacamento);
    int altura_total = altura + (2 * espacamento);

    ImagemPBM *img = criar_imagem(largura_total, altura_total);

    for (int i = espacamento; i < altura_total - espacamento; i++) {
        int pos_bit = 0;
        int pixel_counter = 0;
        for (int j = espacamento; j < largura_total - espacamento; j++) {
            img->dados[i][j] = (binario[pos_bit] == '1') ? 1 : 0;
            pixel_counter++;
            if (pixel_counter == ppa) {
                pixel_counter = 0;
                pos_bit++;
            }
        }
    }
    return img;
}