#include <stdio.h>
int euclid(int x, int y){
    int r = x%y;
    int temp = y;
    while (r != 0)
    {
        temp = r; 
        r = x%r;
    }
    return temp;
}

int fibonacci(int n){
    if(n == 0)return 1;
    else if(n == 1)return 1;
    int count = 0, flb_n = 0, a = 0,  b = 1;
    while (count != n){
        flb_n = a + b;
        a = b;
        b = flb_n;
        count = count + 1;
    }   
    return flb_n;
}

int swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}
int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    if(x < y) swap(&x, &y);
    printf("GCD = %d\n", euclid(x, y));
    int n;
    scanf("%d", &n);
    printf("Fib(n) = %d\n", fibonacci(n));
}