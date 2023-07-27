#include <stdio.h>
#include <stdlib.h>

void swap_rows(double **matrix, int row1, int row2, int n) { 
    double *temp = matrix[row1]; //matriz temporaria
    matrix[row1] = matrix[row2];
    matrix[row2] = temp; 
}//nessa função é feita a troca de linhas na matriz

void print_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { //for serve pra imprimir a matriz
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}//nessa função é feita a impressão da matriz

void forward_elimination(double **matrix, double *b, int n) {
    for (int k = 0; k < n - 1; k++) {
        int max_row = k;
        double max_val = matrix[k][k];
        // nesse for é feita a busca pela linha com o maior valor na coluna atual

        for (int i = k + 1; i < n; i++) {
            if (matrix[i][k] > max_val) {
                max_row = i;
                max_val = matrix[i][k];
            }
        } 

        if (max_row != k) { //se o if for verdadeiro, é feita a troca de linhas
            swap_rows(matrix, k, max_row, n);
            double temp = b[k];
            b[k] = b[max_row];
            b[max_row] = temp;
        }

        for (int i = k + 1; i < n; i++) { // se o if for falso, é feita a eliminação de gauss
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k + 1; j < n; j++) {
                matrix[i][j] -= factor * matrix[k][j]; //calculo da matriz
            }
            b[i] -= factor * b[k];
        }
    }
}

void backward_substitution(double **matrix, double *b, double *x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / matrix[i][i];
    }
} //nessa função é feita a substituição retroativa na matriz

int main() { //nossa principal
    printf("Digite a ordem da matriz: ");
    int n;
    scanf("%d", &n);

    double **A = malloc(n * sizeof(double *)); //alocação dinamica de memoria
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
    }

    printf ("Digite os valores da matriz: \n");
    for (int i = 0; i < n; i++) { //for responsavel por atribuir os valores para a matriz A
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf ("Digite os valores do vetor b: \n");
    double *b = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) { //for responsavel por atribuir os valores para o vetor b
        scanf("%lf", &b[i]);
    }
    

    double **L = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        L[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            L[i][j] = (i == j) ? 1.0 : 0.0; 
            //aqui é feita a atribuição de valores para a matriz L
            //se a linha for igual a coluna, o valor é 1, se não, é 0
        }
    }

    double **U = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        U[i] = malloc(n * sizeof(double));
    } //aqui é feita a atribuição de valores para a matriz U

    forward_elimination(A, b, n); //chamada da função de eliminação de gauss

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = (j >= i) ? A[i][j] : 0.0;
            L[i][j] = (j < i) ? A[i][j] : L[i][j]; 
        } //for responsavel por atribuir os valores para as matrizes L e U
    }

    double *y = malloc(n * sizeof(double));
    backward_substitution(L, b, y, n); //chamada da função de substituição retroativa

    double *x = malloc(n * sizeof(double));
    backward_substitution(U, y, x, n); //chamada da função de substituição retroativa

    printf("Vetor y:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n\n");

    printf("Vetor x:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", x[i]);
    }
    printf("\n");


    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);

    return 0;
}
