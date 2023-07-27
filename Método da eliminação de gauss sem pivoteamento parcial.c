#include <stdio.h>

#define N 3

int main() {
    double matriz[N][N+1] = {
        {1, 1, 1, 4},
        {1, 4, 3, 8},
        {1, 6, 2, 6}
    };
    double solucao[N]; // Vetor de soluções
    int i, j, k;

    // Eliminação de Gauss
    for (k = 0; k < N-1; k++) {
        for (i = k + 1; i < N; i++) {
            double coeficiente = matriz[i][k] / matriz[k][k];
            for (j = k; j <= N; j++) {
                matriz[i][j] -= coeficiente * matriz[k][j];
            }
        }
    }

    // Substituição retroativa
    solucao[N-1] = matriz[N-1][N] / matriz[N-1][N-1];
    for (i = N - 2; i >= 0; i--) {
        float soma = 0;
        for (j = i + 1; j < N; j++) {
            soma += matriz[i][j] * solucao[j];
        }
        solucao[i] = (matriz[i][N] - soma) / matriz[i][i];
    }

    printf ("\n");
    // Exibição da solução
    printf("Solucao:\n");
    for (i = 0; i < N; i++) {
        printf("x%d = %.2lf\n", i+1, solucao[i]);
    }

    return 0;
}


//Neste código, a matriz matriz[N][N+1] representa a matriz estendida do sistema de equações lineares,
//onde a última coluna é reservada para o vetor de resultados.
//O algoritmo começa com a eliminação de Gauss. O loop externo k percorre as colunas da matriz, e o
//loop interno i percorre as linhas abaixo da diagonal principal. Para cada elemento abaixo da diagonal,
//calculamos o coeficiente de eliminação coeficiente e subtraímos o produto desse coeficiente pelos elementos
//correspondentes da linha pivô. Após a eliminação de Gauss, realizamos a substituição retroativa para
//encontrar as soluções do sistema. Começamos com a última linha, onde a solução correspondente é o resultado
//da última coluna dividido pelo elemento da diagonal principal. Em seguida, percorremos as linhas de
//baixo para cima, calculando a soma dos produtos dos elementos da linha pelos valores conhecidos das
//soluções. Subtraímos essa soma do valor do lado direito da equação e dividimos pelo elemento da diagonal
//principal correspondente para obter a solução da variável.
