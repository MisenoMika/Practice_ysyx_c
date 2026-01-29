#include <stdio.h>

int euclid(int x, int y){
    int r = x%y;
    if(r == 0)return y;
    else {
        return euclid(x, r);
    }
}
int memo[1000];
long long int fibonacci(int n) {
    if (n == 0) return memo[n] = 0;
    if (n == 1) return memo[n] = 1;

    return memo[n] = fibonacci(n-1) + fibonacci(n-2);
}
int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    printf("GCD of %d and %d is %d\n", x, y, euclid(x, y));
    int n;
    scanf("%d", &n);
    printf("Fibonacci of %d is %lld\n", n, fibonacci(n));
    return 0;
}
