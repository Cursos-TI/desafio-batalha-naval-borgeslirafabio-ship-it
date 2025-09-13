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

// Função para verificar se o navio cabe no tabuleiro e não ultrapassa os limites
bool valida_posicao(int linha, int coluna, bool horizontal) {
    if (horizontal) {
        // Verifica se o navio horizontal cabe na linha
        return (coluna >= 0 && coluna + SHIP_SIZE <= TAB_SIZE && linha >= 0 && linha < TAB_SIZE);
    } else {
        // Verifica se o navio vertical cabe na coluna
        return (linha >= 0 && linha + SHIP_SIZE <= TAB_SIZE && coluna >= 0 && coluna < TAB_SIZE);
    }
}

// Função para verificar se o navio não se sobrepõe a outro já posicionado
bool verifica_sobreposicao(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, bool horizontal) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (tabuleiro[l][c] == 3) {
            return true; // Já existe navio nessa posição
        }
    }
    return false;
}

// Função para posicionar o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, bool horizontal) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = 3; // Marca posição do navio com 3
    }
}

// Função para exibir o tabuleiro no console
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

    // Define coordenadas iniciais dos navios (linha, coluna)
    // Navio 1: horizontal
    int navio1_linha = 2;
    int navio1_coluna = 3;
    bool navio1_horizontal = true;

    // Navio 2: vertical
    int navio2_linha = 5;
    int navio2_coluna = 7;
    bool navio2_horizontal = false;

    // Valida e posiciona navio 1
    if (!valida_posicao(navio1_linha, navio1_coluna, navio1_horizontal)) {
        printf("Posição do navio 1 inválida!\n");
        return 1;
    }

    if (verifica_sobreposicao(tabuleiro, navio1_linha, navio1_coluna, navio1_horizontal)) {
        printf("Navio 1 sobrepõe outro navio!\n");
        return 1;
    }

    posiciona_navio(tabuleiro, navio1_linha, navio1_coluna, navio1_horizontal);

    // Valida e posiciona navio 2
    if (!valida_posicao(navio2_linha, navio2_coluna, navio2_horizontal)) {
        printf("Posição do navio 2 inválida!\n");
        return 1;
    }

    if (verifica_sobreposicao(tabuleiro, navio2_linha, navio2_coluna, navio2_horizontal)) {
        printf("Navio 2 sobrepõe outro navio!\n");
        return 1;
    }

    posiciona_navio(tabuleiro, navio2_linha, navio2_coluna, navio2_horizontal);

    // Exibe o tabuleiro com os navios posicionados
    exibe_tabuleiro(tabuleiro);

    return 0;
}



















