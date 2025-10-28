#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define REPEAT 100 // repeat to get measurable average time
	// Merge function used in Merge Sort

	void merge(int arr[], int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// create temp arrays
	int L[n1], R[n2];

	// copy data
	for (i = 0; i < n1; i++)
	L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
	R[j] = arr[mid + 1 + j];

	// merge temp arrays back into arr[]
	i = 0; j = 0; k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	// copy remaining elements
	while (i < n1)
	arr[k++] = L[i++];
	while (j < n2)
	arr[k++] = R[j++];
	}

	// Recursive Merge Sort
	void mergeSort(int arr[], int left, int right) {
	if (left < right) {
	int mid = left + (right - left) / 2;

	// sort halves
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	// merge halves
	merge(arr, left, mid, right);
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
	mergeSort(temp, 0, n - 1);
	}
	end = clock();

	cpu_time = ((double)(end - start)) /CLOCKS_PER_SEC / REPEAT;

	printf("%5d\t%lf\n", n, cpu_time);
	}

	return 0;
	}
