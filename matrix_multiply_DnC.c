#include <stdio.h>

#define N 4

// Function to add two matrices
void add(int A[N][N], int B[N][N], int C[N][N], int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i + row][j + col] + B[i + row][j + col];
}

// Function to subtract two matrices
void subtract(int A[N][N], int B[N][N], int C[N][N], int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i + row][j + col] - B[i + row][j + col];
}

// Standard matrix multiplication for small matrices
void multiplyBase(int A[N][N], int B[N][N], int C[N][N], int aRow, int aCol, int bRow, int bCol, int cRow, int cCol, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            C[cRow + i][cCol + j] = 0;
            for (int k = 0; k < size; k++)
                C[cRow + i][cCol + j] += A[aRow + i][aCol + k] * B[bRow + k][bCol + j];
        }
}

// Divide and conquer matrix multiplication
void multiplyDnC(int A[N][N], int B[N][N], int C[N][N], int aRow, int aCol, int bRow, int bCol, int cRow, int cCol, int size) {
    if (size == 1) {
        C[cRow][cCol] = A[aRow][aCol] * B[bRow][bCol];
        return;
    }
    int newSize = size / 2;
    int temp1[N][N] = {0}, temp2[N][N] = {0};

    // C11 = A11*B11 + A12*B21
    multiplyDnC(A, B, temp1, aRow, aCol, bRow, bCol, 0, 0, newSize);
    multiplyDnC(A, B, temp2, aRow, aCol + newSize, bRow + newSize, bCol, 0, 0, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C[cRow + i][cCol + j] = temp1[i][j] + temp2[i][j];

    // C12 = A11*B12 + A12*B22
    multiplyDnC(A, B, temp1, aRow, aCol, bRow, bCol + newSize, 0, 0, newSize);
    multiplyDnC(A, B, temp2, aRow, aCol + newSize, bRow + newSize, bCol + newSize, 0, 0, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C[cRow + i][cCol + j + newSize] = temp1[i][j] + temp2[i][j];

    // C21 = A21*B11 + A22*B21
    multiplyDnC(A, B, temp1, aRow + newSize, aCol, bRow, bCol, 0, 0, newSize);
    multiplyDnC(A, B, temp2, aRow + newSize, aCol + newSize, bRow + newSize, bCol, 0, 0, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C[cRow + i + newSize][cCol + j] = temp1[i][j] + temp2[i][j];

    // C22 = A21*B12 + A22*B22
    multiplyDnC(A, B, temp1, aRow + newSize, aCol, bRow, bCol + newSize, 0, 0, newSize);
    multiplyDnC(A, B, temp2, aRow + newSize, aCol + newSize, bRow + newSize, bCol + newSize, 0, 0, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C[cRow + i + newSize][cCol + j + newSize] = temp1[i][j] + temp2[i][j];
}

// Function to print a matrix
void printMatrix(int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N] = {0};

    printf("Enter elements of first 4x4 matrix:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of second 4x4 matrix:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &B[i][j]);

    multiplyDnC(A, B, C, 0, 0, 0, 0, 0, 0, N);

    printf("Resultant matrix:\n");
    printMatrix(C);

    return 0;
}