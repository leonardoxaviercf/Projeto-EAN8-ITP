#ifndef EAN8_GERACAO_H
#define EAN8_GERACAO_H

#include "ean8_core.h"

// Gera a imagem completa baseada nos parâmetros
ImagemPBM *gerar_imagem_ean8(const char *identificador, int espacamento, int ppa, int altura);

#endif