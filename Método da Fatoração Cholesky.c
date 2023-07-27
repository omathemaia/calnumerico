#include <stdio.h>
#include <math.h>

#define N 3 //so trabalha com tamanho 3x3

int main() {

    double matriz[N][N];
    double G[N][N];
    double GT[N][N];
    double b[N]; // Vetor b
    double y[N]; // Vetor y
    double x[N]; // Vetor x
    double soma;
    int i, j, k;
    //variaveis declaradas
    
    printf ("Digite aqui os valores da matriz:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf ("%lf", &matriz[i][j]);
        }
    }
    printf ("\n");

    printf ("Digite aqui os valores do vetor b:\n");
    for (i = 0; i < N; i++) {
        scanf ("%lf", &b[i]);
    }
    printf ("\n");

    //verificar determinante da matriz
    double det = 1;
    for (i = 0; i < N; i++) {
        det *= matriz[i][i]; 
    }
    if (det == 0) {
        printf("A matriz nao e positiva definida\n");
        return 0;
    } //tem que ser maior que 0 pra poder fazer a fatoração de Cholesky1

    //verificar se a matriz é simetrica
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            if (matriz[i][j] != matriz[j][i]) {
                printf("A matriz nao e simetrica\n");
                return 0;
            }
        }
    } // se a matriz não for simetrica não pode fazer a fatoração de Cholesky

    // Fatoração de Cholesky
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            soma = 0;
            if (j == i) {
                for (k = 0; k < j; k++) {
                    soma += pow(G[j][k], 2); 
                } 
                G[j][j] = sqrt(matriz[j][j] - soma);
            } else {
                for (k = 0; k < j; k++) {
                    soma += G[i][k] * G[j][k]; 
                }
                G[i][j] = (matriz[i][j] - soma) / G[j][j]; 
            }
        }
    } 

    // Cálculo da transposta de G
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            GT[i][j] = G[j][i]; //troca a linha pela coluna.
        }
    }

    // Exibição da matriz G
    printf("Matriz G:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            printf("%.2lf ", G[i][j]);
        }
        printf("\n");
    }

    // Resolução do sistema Gy=b
    for (i = 0; i < N; i++) {
        soma = 0;
        for (j = 0; j < i; j++) {
            soma += G[i][j] * y[j];
        }
        y[i] = (b[i] - soma) / G[i][i];
    }
    printf("\n"); //igual aos metodos anteriores

    // Resolução do sistema Gtx=Y
    for (i = N - 1; i >= 0; i--) {
        soma = 0;
        for (j = i + 1; j < N; j++) {
            soma += GT[i][j] * x[j];
        }
        x[i] = (y[i] - soma) / GT[i][i];
    }
    printf("\n"); //igual aos metodos anteriores

    // Exibição da matriz GT
    printf("Matriz GT:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.2lf ", GT[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Exibição do vetor y
    printf("Vetor y:\n");
    for (i = 0; i < N; i++) {
        printf("%.2lf\n", y[i]);
    }
    printf("\n");

    // Exibição dos resultados
    printf("Solucao:\n");
    for (i = 0; i < N; i++) {
        printf("x%d = %.2lf\n", i+1, x[i]);
    }

    return 0;
}