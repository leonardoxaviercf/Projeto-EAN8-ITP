#ifndef EAN8_CORE_H
#define EAN8_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura da Imagem
typedef struct {
    int largura;
    int altura;
    int **dados; // 1=preto, 0=branco
} ImagemPBM;

// Tabelas globais
extern const char *L_CODE[10];
extern const char *R_CODE[10];

// Funções comuns
int calcular_digito_verificador(const char *identificador);
int validar_identificador(const char *identificador);
ImagemPBM *criar_imagem(int largura, int altura);
void liberar_imagem(ImagemPBM *img);
void salvar_imagem(ImagemPBM *img, const char *nome_arquivo);
ImagemPBM *ler_imagem(const char *nome_arquivo);

#endif