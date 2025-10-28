#include <stdio.h> 
#include <windows.h>  // For QueryPerformanceCounter & Frequency 
 
long long bottom_up(int n,long long arr[]){ 
    arr[0]=0; 
    arr[1]=1; 
     
        for(int i=2;i<=n;i++){ 
            arr[i]=arr[i-1]+arr[i-2]; 
        } 
    return arr[n];  
     
} 
 
int main() { 
    LARGE_INTEGER freq, start, end; 
    QueryPerformanceFrequency(&freq); // ticks per second 
 
    for (int i = 25; i <= 60; i += 5) { 
        long long arr[i + 1]; 
        long long x = 0; 
 
        QueryPerformanceCounter(&start); 
 
        for (int j = 0; j < 1000; j++) {   // run 1000 times for averaging 
            for (int k = 0; k <= i; k++) arr[k] = -1; 
            x = bottom_up(i, arr); 
        } 
 
        QueryPerformanceCounter(&end); 
 
        long long elapsed_ticks = end.QuadPart - start.QuadPart; 
        long long elapsed_ns = (elapsed_ticks * 1000000000LL) / freq.QuadPart; 
        double avg_ns = (double)elapsed_ns / 1000.0; 
 
        printf("fibonacci no %d is equal to %lld\n", i, x); 
        printf("average time per run = %.5f ns\n", avg_ns); 
        printf("average time per run = %e s\n\n", avg_ns/1e9); 
 
    } 
    return 0; 
}