#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to multiply two square matrices of size n
void multiply_matrices(int n) {
    int padded_n = (n % 2 == 0) ? n : n + 1; // Pad to next even size if odd
    int **A, **B, **C;
    int i, j, k;

    // Allocate memory
    A = (int **)malloc(padded_n * sizeof(int *));
    B = (int **)malloc(padded_n * sizeof(int *));
    C = (int **)malloc(padded_n * sizeof(int *));
    for (i = 0; i < padded_n; i++) {
        A[i] = (int *)calloc(padded_n, sizeof(int)); // calloc initializes to 0
        B[i] = (int *)calloc(padded_n, sizeof(int));
        C[i] = (int *)calloc(padded_n, sizeof(int));
    }

    // Initialize only n x n portion with random values (padding remains 0)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Record start time
    clock_t start = clock();

    // Matrix multiplication (iterative)
    for (i = 0; i < padded_n; i++) {
        for (j = 0; j < padded_n; j++) {
            for (k = 0; k < padded_n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Record end time
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Original size: %dx%d, Used size (after padding): %dx%d, Time taken: %.6f seconds\n",
           n, n, padded_n, padded_n, time_taken);

    // Free memory
    for (i = 0; i < padded_n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main() {
    srand(time(NULL)); // Random seed

    int sizes[] = {101, 200, 305, 400, 509}; // Example sizes (odd + even)
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("------------------------------------------------------------\n");
    printf("%-15s %-20s %-20s\n", "Matrix Size", "Padded Size", "Time (seconds)");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        multiply_matrices(sizes[i]);
    }

    printf("------------------------------------------------------------\n");
    printf("Time Complexity   ~ O(n^3)\n");
    printf("Space Complexity  ~ O(n^2)\n");
    printf("------------------------------------------------------------\n");

    return 0;
}
