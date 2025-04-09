#include <stdio.h>
#include <stdlib.h>

// Tamanho do tabuleiro
#define TAM 8

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Limpa o tabuleiro
void limparTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// TORRE – movimentos horizontais e verticais (for)
void moverTorre(int tabuleiro[TAM][TAM], int x, int y) {
    limparTabuleiro(tabuleiro);
    tabuleiro[x][y] = 1;

    for (int i = 0; i < TAM; i++) {
        tabuleiro[x][i] = 1; // linha
        tabuleiro[i][y] = 1; // coluna
    }
}

// BISPO – diagonais (while)
void moverBispo(int tabuleiro[TAM][TAM], int x, int y) {
    limparTabuleiro(tabuleiro);
    tabuleiro[x][y] = 1;

    int i, j;

    // diagonal ↘
    i = x; j = y;
    while (i < TAM && j < TAM) tabuleiro[i++][j++] = 1;

    // diagonal ↖
    i = x; j = y;
    while (i >= 0 && j >= 0) tabuleiro[i--][j--] = 1;

    // diagonal ↙
    i = x; j = y;
    while (i < TAM && j >= 0) tabuleiro[i++][j--] = 1;

    // diagonal ↗
    i = x; j = y;
    while (i >= 0 && j < TAM) tabuleiro[i--][j++] = 1;
}

// RAINHA – combina torre e bispo (do-while)
void moverRainha(int tabuleiro[TAM][TAM], int x, int y) {
    limparTabuleiro(tabuleiro);
    tabuleiro[x][y] = 1;

    // Torre
    for (int i = 0; i < TAM; i++) {
        tabuleiro[x][i] = 1;
        tabuleiro[i][y] = 1;
    }

    // Bispo (diagonais)
    int i, j;

    // ↘
    i = x; j = y;
    do { tabuleiro[i][j] = 1; i++; j++; } while (i < TAM && j < TAM);

    // ↖
    i = x; j = y;
    do { tabuleiro[i][j] = 1; i--; j--; } while (i >= 0 && j >= 0);

    // ↙
    i = x; j = y;
    do { tabuleiro[i][j] = 1; i++; j--; } while (i < TAM && j >= 0);

    // ↗
    i = x; j = y;
    do { tabuleiro[i][j] = 1; i--; j++; } while (i >= 0 && j < TAM);
}

// CAVALO – movimentos em L (loops aninhados)
void moverCavalo(int tabuleiro[TAM][TAM], int x, int y) {
    limparTabuleiro(tabuleiro);
    tabuleiro[x][y] = 1;

    int dx[] = { -2, -1, 1, 2,  2,  1, -1, -2 };
    int dy[] = {  1,  2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM) {
            tabuleiro[nx][ny] = 1;
        }
    }
}

// RAINHA RECURSIVA – avança em uma diagonal até o fim do tabuleiro
void moverRainhaDiagonalRecursiva(int tabuleiro[TAM][TAM], int x, int y) {
    if (x >= TAM || y >= TAM) return;
    tabuleiro[x][y] = 1;
    moverRainhaDiagonalRecursiva(tabuleiro, x + 1, y + 1); // ↘
}

// MENU para testar os movimentos
void menu() {
    int tabuleiro[TAM][TAM];
    int escolha, x, y;

    do {
        printf("\n=== MateCheck - Simulador de Movimentos ===\n");
        printf("1. Mover Torre\n2. Mover Bispo\n3. Mover Rainha\n4. Mover Cavalo\n5. Rainha Recursiva Diagonal\n0. Sair\nEscolha: ");
        scanf("%d", &escolha);

        if (escolha == 0) break;

        printf("Informe a posição inicial (linha e coluna de 0 a 7): ");
        scanf("%d %d", &x, &y);

        switch (escolha) {
            case 1: moverTorre(tabuleiro, x, y); break;
            case 2: moverBispo(tabuleiro, x, y); break;
            case 3: moverRainha(tabuleiro, x, y); break;
            case 4: moverCavalo(tabuleiro, x, y); break;
            case 5: limparTabuleiro(tabuleiro); moverRainhaDiagonalRecursiva(tabuleiro, x, y); break;
            default: printf("Opção inválida!\n"); continue;
        }

        imprimirTabuleiro(tabuleiro);

    } while (escolha != 0);
}

int main() {
    menu();
    return 0;
}
