#include <stdio.h>
#include "ean8_core.h"
#include "ean8_geracao.h"

int main(int argc, char *argv[]) {
    // Argumentos padrão
    char *id = NULL;
    int esp = 4, ppa = 3, alt = 50;
    char *arquivo = "codigo.pbm";

    if (argc < 2) {
        printf("Uso: %s <id> [esp] [ppa] [alt] [arquivo]\n", argv[0]);
        return 1;
    }
    id = argv[1];
    if (argc > 2) esp = atoi(argv[2]);
    if (argc > 3) ppa = atoi(argv[3]);
    if (argc > 4) alt = atoi(argv[4]);
    if (argc > 5) arquivo = argv[5];

    if (!validar_identificador(id)) {
        printf("Erro: ID invalido.\n");
        return 1;
    }

    // Verifica existencia
    FILE *f = fopen(arquivo, "r");
    if (f) {
        fclose(f);
        char r;
        printf("Arquivo existe. Sobrescrever? (s/n): ");
        scanf(" %c", &r);
        if (r != 's') return 1;
    }

    ImagemPBM *img = gerar_imagem_ean8(id, esp, ppa, alt);
    salvar_imagem(img, arquivo);
    liberar_imagem(img);
    
    printf("Gerado com sucesso em '%s'.\n", arquivo);
    return 0;
}