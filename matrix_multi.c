#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate matrix
int** create_matrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)calloc(n, sizeof(int));
    return mat;
}

// Free matrix
void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

// Normal multiplication (used for small cases)
void normal_multiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

// Add matrices
void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract matrices
void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen recursive multiplication
void strassen(int** A, int** B, int** C, int n) {
    if (n <= 64) {  // base case threshold
        normal_multiply(A, B, C, n);
        return;
    }

    int mid = n / 2;

    // Allocate submatrices
    int** A11 = create_matrix(mid);
    int** A12 = create_matrix(mid);
    int** A21 = create_matrix(mid);
    int** A22 = create_matrix(mid);
    int** B11 = create_matrix(mid);
    int** B12 = create_matrix(mid);
    int** B21 = create_matrix(mid);
    int** B22 = create_matrix(mid);

    // Divide input matrices into submatrices
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Allocate temporary matrices
    int** M1 = create_matrix(mid);
    int** M2 = create_matrix(mid);
    int** M3 = create_matrix(mid);
    int** M4 = create_matrix(mid);
    int** M5 = create_matrix(mid);
    int** M6 = create_matrix(mid);
    int** M7 = create_matrix(mid);
    int** T1 = create_matrix(mid);
    int** T2 = create_matrix(mid);

    // Strassen’s 7 multiplications
    add_matrix(A11, A22, T1, mid);
    add_matrix(B11, B22, T2, mid);
    strassen(T1, T2, M1, mid); // M1 = (A11 + A22)(B11 + B22)

    add_matrix(A21, A22, T1, mid);
    strassen(T1, B11, M2, mid); // M2 = (A21 + A22)B11

    sub_matrix(B12, B22, T2, mid);
    strassen(A11, T2, M3, mid); // M3 = A11(B12 - B22)

    sub_matrix(B21, B11, T2, mid);
    strassen(A22, T2, M4, mid); // M4 = A22(B21 - B11)

    add_matrix(A11, A12, T1, mid);
    strassen(T1, B22, M5, mid); // M5 = (A11 + A12)B22

    sub_matrix(A21, A11, T1, mid);
    add_matrix(B11, B12, T2, mid);
    strassen(T1, T2, M6, mid); // M6 = (A21 - A11)(B11 + B12)

    sub_matrix(A12, A22, T1, mid);
    add_matrix(B21, B22, T2, mid);
    strassen(T1, T2, M7, mid); // M7 = (A12 - A22)(B21 + B22)

    // Combine results into C
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + mid] = M3[i][j] + M5[i][j];
            C[i + mid][j] = M2[i][j] + M4[i][j];
            C[i + mid][j + mid] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Free all allocated matrices
    free_matrix(A11, mid); free_matrix(A12, mid);
    free_matrix(A21, mid); free_matrix(A22, mid);
    free_matrix(B11, mid); free_matrix(B12, mid);
    free_matrix(B21, mid); free_matrix(B22, mid);
    free_matrix(M1, mid); free_matrix(M2, mid);
    free_matrix(M3, mid); free_matrix(M4, mid);
    free_matrix(M5, mid); free_matrix(M6, mid);
    free_matrix(M7, mid);
    free_matrix(T1, mid); free_matrix(T2, mid);
}

// Main function
int main() {
    int sizes[] = {101, 200, 305, 400, 509};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int padded_n = (n % 2 == 0) ? n : n + 1;

        int** A = create_matrix(padded_n);
        int** B = create_matrix(padded_n);
        int** C = create_matrix(padded_n);

        // Fill matrices with random values
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start = clock();
        strassen(A, B, C, padded_n);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Original size: %dx%d, Used size: %dx%d, Time: %.6f sec\n",
               n, n, padded_n, padded_n, time_taken);

        free_matrix(A, padded_n);
        free_matrix(B, padded_n);
        free_matrix(C, padded_n);
    }
    return 0;
}
