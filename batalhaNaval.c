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
#define HABILIDADE_SIZE 5 // Tamanho fixo das matrizes de habilidade (5x5)

// Enum para orientação dos navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_DESC,  // Diagonal descendente
    DIAGONAL_ASC    // Diagonal ascendente
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
                    coluna >= 0 && coluna + SHIP_SIZE <= TAB_SIZE);
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

// Função para construir a matriz de habilidade "Cone" (5x5)
// O cone aponta para baixo, com o topo no centro da primeira linha
void constroi_cone(int cone[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    // Inicializa tudo com 0
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            cone[i][j] = 0;
        }
    }
    // Construção do cone:
    // Linha 0: centro
    cone[0][HABILIDADE_SIZE/2] = 1;
    // Linha 1: centro e um à esquerda e um à direita
    cone[1][HABILIDADE_SIZE/2 - 1] = 1;
    cone[1][HABILIDADE_SIZE/2] = 1;
    cone[1][HABILIDADE_SIZE/2 + 1] = 1;
    // Linha 2: toda a linha
    for (int j = 0; j < HABILIDADE_SIZE; j++) {
        cone[2][j] = 1;
    }
    // As demais linhas permanecem 0
}

// Função para construir a matriz de habilidade "Cruz" (5x5)
// Cruz com ponto de origem no centro
void constroi_cruz(int cruz[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    // Inicializa tudo com 0
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            cruz[i][j] = 0;
        }
    }
    int centro = HABILIDADE_SIZE / 2;
    // Linha central toda preenchida
    for (int j = 0; j < HABILIDADE_SIZE; j++) {
        cruz[centro][j] = 1;
    }
    // Coluna central toda preenchida
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        cruz[i][centro] = 1;
    }
}

// Função para construir a matriz de habilidade "Octaedro" (5x5)
// Losango com ponto de origem no centro
void constroi_octaedro(int octaedro[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    // Inicializa tudo com 0
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            octaedro[i][j] = 0;
        }
    }
    int centro = HABILIDADE_SIZE / 2;
    // Para cada linha, marca as posições que formam o losango
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        int dist = abs(centro - i);
        // Marca as posições entre centro-dist e centro+dist
        for (int j = centro - dist; j <= centro + dist; j++) {
            octaedro[i][j] = 1;
        }
    }
}

// Função para sobrepor a matriz de habilidade ao tabuleiro
// Marca as posições afetadas com valor 5, sem sobrescrever navios (3)
void sobrepoe_habilidade(int tabuleiro[TAB_SIZE][TAB_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int origem_linha, int origem_coluna) {
    int meio = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int tab_linha = origem_linha - meio + i;
                int tab_coluna = origem_coluna - meio + j;
                // Verifica limites do tabuleiro
                if (tab_linha >= 0 && tab_linha < TAB_SIZE && tab_coluna >= 0 && tab_coluna < TAB_SIZE) {
                    // Marca área afetada somente se não for navio
                    if (tabuleiro[tab_linha][tab_coluna] == 0) {
                        tabuleiro[tab_linha][tab_coluna] = 5;
                    }
                }
            }
        }
    }
}

// Função para exibir o tabuleiro formatado com símbolos
void exibe_tabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval com Áreas de Habilidade:\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            char simbolo;
            switch (tabuleiro[i][j]) {
                case 0:
                    simbolo = '.'; // Água
                    break;
                case 3:
                    simbolo = 'N'; // Navio
                    break;
                case 5:
                    simbolo = '*'; // Área afetada pela habilidade
                    break;
                default:
                    simbolo = '?'; // Valor inesperado
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Definição dos navios: linha, coluna, orientação
    int navio1_linha = 1, navio1_coluna = 2;
    Orientacao navio1_orientacao = HORIZONTAL;

    int navio2_linha = 5, navio2_coluna = 7;
    Orientacao navio2_orientacao = VERTICAL;

    int navio3_linha = 0, navio3_coluna = 0;
    Orientacao navio3_orientacao = DIAGONAL_DESC;

    int navio4_linha = 9, navio4_coluna = 0;
    Orientacao navio4_orientacao = DIAGONAL_ASC;

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

    // Matrizes de habilidade
    int cone[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int cruz[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int octaedro[HABILIDADE_SIZE][HABILIDADE_SIZE];

    // Constroi as matrizes dinamicamente
    constroi_cone(cone);
    constroi_cruz(cruz);
    constroi_octaedro(octaedro);

    // Define pontos de origem das habilidades no tabuleiro
    int origem_cone_linha = 3, origem_cone_coluna = 3;
    int origem_cruz_linha = 6, origem_cruz_coluna = 6;
    int origem_octaedro_linha = 8, origem_octaedro_coluna = 2;

    // Sobrepõe as áreas de efeito no tabuleiro
    sobrepoe_habilidade(tabuleiro, cone, origem_cone_linha, origem_cone_coluna);
    sobrepoe_habilidade(tabuleiro, cruz, origem_cruz_linha, origem_cruz_coluna);
    sobrepoe_habilidade(tabuleiro, octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    // Exibe o tabuleiro final
    exibe_tabuleiro(tabuleiro);

    return 0;
}





















