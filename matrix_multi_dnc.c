#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate a square matrix
double** allocate_matrix(int n) {
    double** mat = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        mat[i] = (double*)calloc(n, sizeof(double)); // initialize to 0
    }
    return mat;
}

// Standard iterative multiplication for small matrices
void multiply_iterative(double** A, double** B, double** C,
                        int n, int a_row, int a_col,
                        int b_row, int b_col,
                        int c_row, int c_col) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[a_row + i][a_col + k] * B[b_row + k][b_col + j];
            }
            C[c_row + i][c_col + j] += sum;
        }
    }
}

// Recursive divide-and-conquer multiplication
void multiply_dc(double** A, double** B, double** C,
                 int n, int a_row, int a_col,
                 int b_row, int b_col,
                 int c_row, int c_col) {
    if (n <= 64) { // base case: switch to iterative
        multiply_iterative(A, B, C, n, a_row, a_col,
                           b_row, b_col, c_row, c_col);
        return;
    }

    int mid = n / 2;

    // C11 = A11*B11 + A12*B21
    multiply_dc(A, B, C, mid, a_row, a_col, b_row, b_col, c_row, c_col);
    multiply_dc(A, B, C, mid, a_row, a_col + mid, b_row + mid, b_col, c_row, c_col);

    // C12 = A11*B12 + A12*B22
    multiply_dc(A, B, C, mid, a_row, a_col, b_row, b_col + mid, c_row, c_col + mid);
    multiply_dc(A, B, C, mid, a_row, a_col + mid, b_row + mid, b_col + mid, c_row, c_col + mid);

    // C21 = A21*B11 + A22*B21
    multiply_dc(A, B, C, mid, a_row + mid, a_col, b_row, b_col, c_row + mid, c_col);
    multiply_dc(A, B, C, mid, a_row + mid, a_col + mid, b_row + mid, b_col, c_row + mid, c_col);

    // C22 = A21*B12 + A22*B22
    multiply_dc(A, B, C, mid, a_row + mid, a_col, b_row, b_col + mid, c_row + mid, c_col + mid);
    multiply_dc(A, B, C, mid, a_row + mid, a_col + mid, b_row + mid, b_col + mid, c_row + mid, c_col + mid);
}

int main() {
    srand(time(NULL));

    int sizes[] = {101, 200, 305, 400, 509};  // example matrix sizes (odd + even)
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("------------------------------------------------------------\n");
    printf("%-15s %-20s %-20s\n", "Matrix Size", "Padded Size", "Time (seconds)");
    printf("------------------------------------------------------------\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int padded_n = (n % 2 == 0) ? n : n + 1;

        double** A = allocate_matrix(padded_n);
        double** B = allocate_matrix(padded_n);
        double** C = allocate_matrix(padded_n);

        // Fill with random values (only n x n portion)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        clock_t start = clock();
        multiply_dc(A, B, C, padded_n, 0, 0, 0, 0, 0, 0);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%-15dx%-15d %-20dx%-15d %-20.6f\n",
               n, n, padded_n, padded_n, time_taken);

        // Free allocated memory
        for (int i = 0; i < padded_n; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    printf("------------------------------------------------------------\n");
    printf("Time Complexity   ~ O(n^3)\n");
    printf("Space Complexity  ~ O(n^2)\n");
    printf("------------------------------------------------------------\n");

    return 0;
}
