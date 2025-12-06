# Projeto EAN-8: Gerador e Extrator de Código de Barras

Este projeto consiste na implementação de dois programas em C para manipulação de códigos de barras no padrão **EAN-8** utilizando o formato de imagem **PBM (Portable Bitmap)**.

O projeto foi desenvolvido como requisito da 3ª unidade da disciplina de ITP (Introdução às Técnicas de Programação), seguindo a arquitetura modular exigida.

## 📂 Estrutura de Arquivos

O código foi organizado seguindo o princípio de *Separação de Preocupações* para evitar redundância e facilitar a manutenção:

* **Núcleo Compartilhado:**
    * `ean8_core.h` / `ean8_core.c`: Contém as estruturas de dados (`ImagemPBM`), tabelas de codificação (L-code/R-code), cálculo de dígito verificador e funções de I/O de arquivos PBM.
* **Módulo de Geração:**
    * `ean8_geracao.h` / `ean8_geracao.c`: Lógica específica para converter uma string numérica em uma matriz de pixels (barras).
* **Módulo de Extração:**
    * `ean8_extracao.h` / `ean8_extracao.c`: Lógica de processamento de imagem, detecção de padrões e decodificação binária.
* **Programas Principais:**
    * `gerador.c`: Interface de linha de comando para criar códigos de barras.
    * `extrator.c`: Interface de linha de comando para ler códigos de barras.

## 🚀 Como Compilar

Como o projeto é modular, é necessário vincular os arquivos objeto correspondentes. Utilize o `gcc` conforme abaixo:

### 1. Compilar o Gerador
```bash
gcc gerador.c ean8_geracao.c ean8_core.c -o gerador
```

### Sintaxe para execução:

```bash
./gerador <identificador> [espacamento] [pixels_por_area] [altura] [nome_arquivo]
```

### Exemplo simples:
```bash
./gerador 40170725
```

### Exemplo personalizado:
```bash
./gerador 40170725 10 5 100 meu_codigo.pbm
```

### 2. Compilar o Extrator
```bash
gcc extrator.c ean8_extracao.c ean8_core.c -o extrator
```

### Exemplo
```bash
./extrator meu_codigo.pbm
```