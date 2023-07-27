#include <stdio.h>
#include <math.h>

#define TAM 3

void swap_rows(float matriz[TAM][TAM + 1], int row1, int row2)
{
    int i;
    float temp;
    for (i = 0; i < TAM + 1; i++) {
        temp = matriz[row1][i];
        matriz[row1][i] = matriz[row2][i];
        matriz[row2][i] = temp;
    }
}

void eliminacao(float matriz[TAM][TAM + 1])
{
    int i, j, k, max_row;
    float max_val, factor;

    // Eliminação com pivoteamento parcial
    for (i = 0; i < TAM - 1; i++) {
        max_row = i;
        max_val = fabs(matriz[i][i]);

        // Encontra a linha com o maior valor absoluto na coluna atual
        for (j = i + 1; j < TAM; j++) {
            if (fabs(matriz[j][i]) > max_val) {
                max_row = j;
                max_val = fabs(matriz[j][i]);
            }
        }

        // Troca de linhas, se necessário
        if (max_row != i) {
            swap_rows(matriz, i, max_row);
        }

        // Eliminação, zerar os elementos abaixo do pivo
        for (j = i + 1; j < TAM; j++) {
            factor = matriz[j][i] / matriz[i][i];
            for (k = i; k < TAM + 1; k++) {
                matriz[j][k] -= factor * matriz[i][k]; 
            }
        }
    }

    // Retrosubstituição serve para encontrar as soluções do sistema
    float solution[TAM];
    for (i = TAM - 1; i >= 0; i--) {
        solution[i] = matriz[i][TAM];
        for (j = i + 1; j < TAM; j++) {
            solution[i] -= matriz[i][j] * solution[j];
        }
        solution[i] /= matriz[i][i];
    }

    // Exibição do resultado
    printf("Solucao:\n");
    for (i = 0; i < TAM; i++) {
        printf("x%d = %f\n", i + 1, solution[i]);
    }
}

int main()
{
    float matriz[TAM][TAM + 1] = {
        {2, 1, -1, 8},
        {-3, -1, 2, -11},
        {-2, 1, 2, -3}
    };

    eliminacao(matriz);

    return 0;
}
