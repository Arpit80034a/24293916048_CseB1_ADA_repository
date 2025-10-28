#include<stdio.h> 
#include<time.h> 
#include<stdlib.h> 
int iter(int n){ 
    if(n==0){ 
        return 0;  
    } 
    else if(n==1){ 
        return 1; 
    } 
    int a=0; 
    int b=1; 
    int ans=0; 
    for(int i=2;i<=n;i++){ 
        ans=a+b; 
        a=b; 
        b=ans; 
    } 
    return ans; 
     
} 
int main(){ 
    for(int i=20;i<=55;i+=5){ 
        int x=0; 
        clock_t start=clock(); 
        for(int j=0;j<1000;j++){ 
            x=iter(i); 
        } 
        clock_t end=clock(); 
        double t=(double)(end-start)/CLOCKS_PER_SEC/1000; 
        printf("fibonacci no %d is equal to %d\ntime taken=%e sec\n\n",i,x,t); 
 
    } 
} 