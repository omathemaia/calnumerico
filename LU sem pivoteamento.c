#include <stdio.h>

#define N 3

int main() {
    printf("Digite os valores da matriz:\n");
    double matrix[N][N];
    for (int i = 0; i < N; i++) { //for responsavel por atribuir os valores para a matriz A
        for (int j = 0; j < N; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    printf("Digite os valores do vetor b:\n");
    double b[N];
    for (int i = 0; i < N; i++) { //for responsavel por atribuir os valores para o vetor b
        scanf("%lf", &b[i]);
    }

    double L[N][N] = {0}; // Matriz L triangular inferior
    double U[N][N] = {0}; // Matriz U triangular superior
    double y[N]; // Vetor y (solução Ly = b)
    double x[N]; // Vetor x (solução Ux = y)
    int i, j, k;

    // Fatoração LU sem pivoteamento parcial
    for (i = 0; i < N; i++) {
        L[i][i] = 1; // Preenche a diagonal principal de L com 1

        for (j = i; j < N; j++) {
            U[i][j] = matrix[i][j];
            for (k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }

        for (j = i + 1; j < N; j++) {
            L[j][i] = matrix[j][i];
            for (k = 0; k < i; k++) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }

    // Resolução do sistema Ly = b
    for (i = 0; i < N; i++) {
        float sum = 0;
        for (j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    //impresão L
    printf("L = \n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.2lf ", L[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //impresão U
    printf("U = \n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.2lf ", U[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Resolução do sistema Ux = y
    for (i = N - 1; i >= 0; i--) {
        float sum = 0;
        for (j = i + 1; j < N; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    // impressão Y
    printf("Y = ");
    for (i = 0; i < N; i++) {
        printf("%.2lf ", y[i]);
    }
    printf("\n");

    // impressão X
    printf("X = ");
    for (i = 0; i < N; i++) {
        printf("%.2lf ", x[i]);
    }
    printf("\n");

    return 0;
}
