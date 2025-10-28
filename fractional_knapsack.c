#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int profit;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item2->ratio > item1->ratio) return 1;
    else if (item2->ratio < item1->ratio) return -1;
    else return 0;
}

double fractionalKnapsack(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare);
    double totalProfit = 0.0;
    int currWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currWeight + items[i].weight <= capacity) {
            currWeight += items[i].weight;
            totalProfit += items[i].profit;
        } else {
            int remain = capacity - currWeight;
            totalProfit += items[i].ratio * remain;
            break;
        }
    }
    return totalProfit;
}

int main() {
    srand(time(0));

    int sizes[] = {10, 50, 100, 200, 400, 800, 1600};
    int capacities[] = {50, 100, 200, 400, 800, 1600, 3200};

    printf("------------------------------------------------------------\n");
    printf("%-8s %-12s %-15s %-15s %-15s\n",
           "Items", "Capacity", "Max Profit", "Time(s)", "Memory(Bytes)");
    printf("------------------------------------------------------------\n");

    for (int t = 0; t < 7; t++) {
        int n = sizes[t];
        int capacity = capacities[t];
        Item *items = malloc(n * sizeof(Item));

        for (int i = 0; i < n; i++) {
            items[i].profit = rand() % 100 + 10;
            items[i].weight = rand() % 30 + 1;
            items[i].ratio = (double)items[i].profit / items[i].weight;
        }

        int runs = 1000;
        clock_t start = clock();
        double profit = 0.0;

        for (int r = 0; r < runs; r++) {
            profit = fractionalKnapsack(items, n, capacity);
        }

        clock_t end = clock();
        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_time = total_time / runs;
        size_t memory_used = sizeof(Item) * n;

        printf("%-8d %-12d %-15.2lf %-15.8lf %-15zu\n",
               n, capacity, profit, avg_time, memory_used);

        free(items);
    }

    printf("------------------------------------------------------------\n");
    printf("Time Complexity   ~ O(n log n)\n");
    printf("Space Complexity  ~ O(n)\n");
    printf("------------------------------------------------------------\n");

    return 0;
}
