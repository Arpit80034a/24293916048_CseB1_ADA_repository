#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10   

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int weights[], int values[], int n, int capacity) {
    int K[n+1][capacity+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (weights[i-1] <= w)
                K[i][w] = max(values[i-1] + K[i-1][w - weights[i-1]], K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    return K[n][capacity];
}

int main() {
    srand(time(0));

    int weights[N], values[N];
    int capacity = 20 + rand() % 31; 

    printf("Randomly generated items:\n");
    for (int i = 0; i < N; i++) {
        weights[i] = 1 + rand() % 15;
        values[i] = 10 + rand() % 91;
        printf("Item %d -> Weight = %d, Value = %d\n", i+1, weights[i], values[i]);
    }

    printf("\nKnapsack Capacity = %d\n", capacity);

    clock_t start, end;
    start = clock();

    int maxValue = knapsack(weights, values, N, capacity);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nMaximum Value in Knapsack = %d\n", maxValue);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}