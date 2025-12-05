#include "ean8_extracao.h"

// Auxiliar interna
int decodificar_padrao(const char *padrao, const char **tabela) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(padrao, tabela[i]) == 0) return i;
    }
    return -1;
}

int extrair_ean8(ImagemPBM *img, char *buffer_out) {
    int linha_meio = img->altura / 2;
    int *linha = img->dados[linha_meio];
    int inicio = -1;

    // Acha inicio
    for (int j = 0; j < img->largura; j++) {
        if (linha[j] == 1) { inicio = j; break; }
    }
    if (inicio == -1) return 0; // Não achou

    // Calcula PPA (Pixels por Area)
    int ppa = 0;
    while ((inicio + ppa) < img->largura && linha[inicio + ppa] == 1) ppa++;
    if (ppa == 0) return 0;

    // Extrai binário
    char binario[68]; binario[67] = '\0';
    for (int m = 0; m < 67; m++) {
        int pos = inicio + (m * ppa) + (ppa / 2);
        if (pos >= img->largura) return 0;
        binario[m] = linha[pos] ? '1' : '0';
    }

    // Valida marcadores
    if (strncmp(binario, "101", 3) != 0 || 
        strncmp(binario + 31, "01010", 5) != 0 ||
        strncmp(binario + 64, "101", 3) != 0) return 0;

    // Decodifica L-code
    char temp[8]; temp[7] = '\0';
    for (int i = 0; i < 4; i++) {
        strncpy(temp, binario + 3 + (i * 7), 7);
        int d = decodificar_padrao(temp, L_CODE);
        if (d == -1) return 0;
        buffer_out[i] = d + '0';
    }

    // Decodifica R-code
    for (int i = 0; i < 4; i++) {
        strncpy(temp, binario + 36 + (i * 7), 7);
        int d = decodificar_padrao(temp, R_CODE);
        if (d == -1) return 0;
        buffer_out[i + 4] = d + '0';
    }
    buffer_out[8] = '\0';
    
    return validar_identificador(buffer_out);
}