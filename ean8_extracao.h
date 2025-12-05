#ifndef EAN8_EXTRACAO_H
#define EAN8_EXTRACAO_H

#include "ean8_core.h"

// Tenta extrair o ID. Retorna 1 se sucesso, 0 se falha.
// O resultado é copiado para 'buffer_out'
int extrair_ean8(ImagemPBM *img, char *buffer_out);

#endif