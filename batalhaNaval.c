#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}

// ------------------------------------------- Jogo de Batalha naval----------------------------------------------------------- //


#include <stdio.h>
#include <stdbool.h>

#define TAB_SIZE 10      // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3      // Tamanho fixo dos navios

// Enum para orientação dos navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_DESC,  // Diagonal descendente: linha e coluna aumentam simultaneamente
    DIAGONAL_ASC    // Diagonal ascendente: linha aumenta e coluna diminui simultaneamente
} Orientacao;

// Função para validar se o navio cabe no tabuleiro, considerando orientação
bool valida_posicao(int linha, int coluna, Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            return (linha >= 0 && linha < TAB_SIZE &&
                    coluna >= 0 && coluna + SHIP_SIZE <= TAB_SIZE);
        case VERTICAL:
            return (linha >= 0 && linha + SHIP_SIZE <= TAB_SIZE &&
                    coluna >= 0 && coluna < TAB_SIZE);
        case DIAGONAL_DESC:
            return (linha >= 0 && linha + SHIP_SIZE <= TAB_SIZE &&
                    coluna >= 0 && coluna + SHIP_SIZE <= TAB_SIZE);
        case DIAGONAL_ASC:
            return (linha - SHIP_SIZE + 1 >= 0 && linha < TAB_SIZE &&
                    coluna >= 0 && coluna + 1 <= TAB_SIZE);
        default:
            return false;
    }
}

// Função para verificar sobreposição do navio no tabuleiro
bool verifica_sobreposicao(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, Orientacao orientacao) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        int l, c;
        switch (orientacao) {
            case HORIZONTAL:
                l = linha;
                c = coluna + i;
                break;
            case VERTICAL:
                l = linha + i;
                c = coluna;
                break;
            case DIAGONAL_DESC:
                l = linha + i;
                c = coluna + i;
                break;
            case DIAGONAL_ASC:
                l = linha - i;
                c = coluna + i;
                break;
            default:
                return true; // Orientação inválida
        }
        if (tabuleiro[l][c] == 3) {
            return true; // Posição já ocupada
        }
    }
    return false;
}

// Função para posicionar o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, Orientacao orientacao) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        int l, c;
        switch (orientacao) {
            case HORIZONTAL:
                l = linha;
                c = coluna + i;
                break;
            case VERTICAL:
                l = linha + i;
                c = coluna;
                break;
            case DIAGONAL_DESC:
                l = linha + i;
                c = coluna + i;
                break;
            case DIAGONAL_ASC:
                l = linha - i;
                c = coluna + i;
                break;
            default:
                return; // Orientação inválida
        }
        tabuleiro[l][c] = 3; // Marca posição do navio
    }
}

// Função para exibir o tabuleiro formatado
void exibe_tabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval (0 = água, 3 = navio):\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Definição dos navios: linha, coluna, orientação
    // Dois navios horizontais/verticais
    int navio1_linha = 1, navio1_coluna = 2;
    Orientacao navio1_orientacao = HORIZONTAL;

    int navio2_linha = 5, navio2_coluna = 7;
    Orientacao navio2_orientacao = VERTICAL;

    // Dois navios diagonais
    int navio3_linha = 0, navio3_coluna = 0; // diagonal descendente
    Orientacao navio3_orientacao = DIAGONAL_DESC;

    int navio4_linha = 9, navio4_coluna = 0; // diagonal ascendente
    Orientacao navio4_orientacao = DIAGONAL_ASC;

    // Array para facilitar iteração
    int linhas[4] = {navio1_linha, navio2_linha, navio3_linha, navio4_linha};
    int colunas[4] = {navio1_coluna, navio2_coluna, navio3_coluna, navio4_coluna};
    Orientacao orientacoes[4] = {navio1_orientacao, navio2_orientacao, navio3_orientacao, navio4_orientacao};

    // Posiciona os navios com validação
    for (int i = 0; i < 4; i++) {
        if (!valida_posicao(linhas[i], colunas[i], orientacoes[i])) {
            printf("Posição do navio %d inválida!\n", i + 1);
            return 1;
        }
        if (verifica_sobreposicao(tabuleiro, linhas[i], colunas[i], orientacoes[i])) {
            printf("Navio %d sobrepõe outro navio!\n", i + 1);
            return 1;
        }
        posiciona_navio(tabuleiro, linhas[i], colunas[i], orientacoes[i]);
    }

    // Exibe o tabuleiro final
    exibe_tabuleiro(tabuleiro);

    return 0;
}



















