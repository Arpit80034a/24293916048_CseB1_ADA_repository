#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define REPEAT 100 // repeat to get measurable average time

	// Insertion Sort function
	void insertionSort(int arr[], int n) {
	int i, key, j;
	for (i = 1; i < n; i++) {
	key = arr[i];
	j = i - 1;

	// Move elements greater than key to one position ahead
	while (j >= 0 && arr[j] > key) {
	arr[j + 1] = arr[j];
	j--;
	}
	arr[j + 1] = key;
	}
	}

	int main() {
	// array sizes to test
	int sizes[] = {1000, 2000, 3000, 4000, 5000, 6000,7000, 8000, 9000, 10000};
	int numSizes = sizeof(sizes) / sizeof(sizes[0]);

	srand(time(0));

	printf(" n\tTime (seconds)\n");
	printf("---------------------------\n");

	for (int s = 0; s < numSizes; s++) {
	int n = sizes[s];
	int arr[n], temp[n];

	// generate random numbers
	for (int i = 0; i < n; i++)
	arr[i] = rand() % 10000;

	clock_t start, end;
	double cpu_time;

	start = clock();
	for (int r = 0; r < REPEAT; r++) {
	// copy original array
	for (int i = 0; i < n; i++)
	temp[i] = arr[i];
	insertionSort(temp, n);
	}
	end = clock();

	cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC / REPEAT;

	printf("%5d\t%lf\n", n, cpu_time);
	};

	return 0;
	}
