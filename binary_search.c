#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary search function
int binarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int n, *arr, x, i, result;
    clock_t start, end;
    double time_taken;
    int repeat = 100000;

    printf("Binary Search time analysis:\n");

    for (n = 10000; n <= 100000; n += 10000) {
        arr = (int*)malloc(n * sizeof(int));

        for (i = 0; i < n; i++) {
            arr[i] = i + 1; 
        }
        x = n; 

        start = clock();
        for (int r = 0; r < repeat; r++) {
            result = binarySearch(arr, n, x);
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("n = %d, Time taken = %f seconds\n", n, time_taken);

        free(arr);
    }

    return 0;
}
