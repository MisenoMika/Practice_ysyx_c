#include <stdio.h>

#include <stdio.h>
#include <math.h>
#define LEN 8

double sqrtSearch(double y, int num){
    double x = 0;
    double tmp = 1;
    for(int i = 0; i < num; i++){
        tmp *= x;
    }
    double high = y, low = 0;
    while(fabs(tmp - y) > 0.01){
        x = (high+low)/2;
        tmp = 1;
        for(int i = 0; i < num; i++){
        tmp *= x;
        }
        if(tmp - y < 0){
            low = x + 0.01; 
        } 
        else if (tmp - y > 0){
            high = x - 0.01;
        }
    }
    return x;
}

double myPow(double x, int numerator, int denominator){
    double base = x;
    if(denominator > 1){
        x = sqrtSearch(x, denominator);
    }
    while (numerator > 1){
        if(numerator % 2 == 0){
            x = x * x;
        }
        else {
            x = x * x * base;
        }
        numerator /= 2;
    }
    return x;
}


int main(void){
    printf("%3f", myPow(27, 1, 3));
}