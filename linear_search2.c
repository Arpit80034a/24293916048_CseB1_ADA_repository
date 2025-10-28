#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Linear Search function
int linear_search(int a[], int x, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] == x) {
            return 1; 
        }
    }
    return -1;  
}

// Function to generate random array
void generateRandomArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    int *arr;
    int x;
    int repeat = 100000; //  for averaging
    clock_t start, end;
    double total_time, time;

    printf("Linear Search Time Analysis:\n");


    for (int n = 50000; n <= 110000; n += 10000) {
        arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed for n = %d!!\n", n);
            return 1;
        }

       
        generateRandomArr(arr, n);

        x = arr[rand() % n];

     
        start = clock();
        for (int i = 0; i < repeat; i++) {
            linear_search(arr, x, n);
        }
        end = clock();

        total_time = (double)(end - start) / CLOCKS_PER_SEC;
        time = total_time / repeat;

        printf("n = %d, Avg Time = %f seconds\n", n, time);

        free(arr);
    }

    return 0;
}
