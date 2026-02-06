#include <stdio.h>
#include <math.h>
#define LEN 8

double sqrtSearch(double y, int num){
    double tmp = 1;
    double x = 0;
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

int main(void)
{
	printf("%3f\n", sqrtSearch(8, 3));
	return 0;
}