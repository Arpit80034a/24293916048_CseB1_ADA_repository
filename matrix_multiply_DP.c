#include <stdio.h>
#include <limits.h>

// Function to multiply two matrices A and B
void multiply(int A[4][4], int B[4][4], int C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to print a 4x4 matrix
void printMatrix(int M[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

// Matrix Chain Multiplication using Dynamic Programming
int matrixChainOrder(int p[], int n, int s[5][5]) {
    int m[5][5] = {0};

    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n-1];
}

// Recursive function to multiply matrices according to optimal order
void matrixChainMultiply(int matrices[4][4][4], int s[5][5], int i, int j, int result[4][4]) {
    if (i == j) {
        // Copy the matrix
        for (int r = 0; r < 4; r++)
            for (int c = 0; c < 4; c++)
                result[r][c] = matrices[i-1][r][c];
        return;
    }
    int temp1[4][4], temp2[4][4];
    matrixChainMultiply(matrices, s, i, s[i][j], temp1);
    matrixChainMultiply(matrices, s, s[i][j]+1, j, temp2);
    multiply(temp1, temp2, result);
}

int main() {
    int matrices[4][4][4];
    int p[5]; // Dimensions array

    // Input 4 matrices of size 4x4
    printf("Enter 4 matrices of size 4x4:\n");
    for (int m = 0; m < 4; m++) {
        printf("Matrix %d:\n", m+1);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &matrices[m][i][j]);
    }

    // For 4x4 matrices, the dimension array is all 4s
    for (int i = 0; i < 5; i++)
        p[i] = 4;

    int s[5][5] = {0};
    int minCost = matrixChainOrder(p, 5, s);

    int result[4][4];
    matrixChainMultiply(matrices, s, 1, 4, result);

    printf("\nResultant matrix after optimal multiplication:\n");
    printMatrix(result);

    printf("\nMinimum number of multiplications: %d\n", minCost);

    return 0;
}