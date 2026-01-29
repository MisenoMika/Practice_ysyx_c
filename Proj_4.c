#include <stdio.h>
#include <math.h>
#include <stdbool.h>
int myround(&x);
bool isLeapYear(int year);
int selNum(int &x);
int main(void){
    int x = 0;
    printf("plz input nums");
    scanf("%d", &x);
    printf("%d", myround(x) );
    int y = 0;
    scanf("%d", &y);
    printf("%d", isLeapYear(y) );
    return 0;
}

bool isLeapYear(int year){
    if(year %400 == 0){
        return 1;
    }
    else if(year%4 == 0 && year %100 != 0){
        return 1;
    }
    else return 0;
}

int myround(int &x){
    if(x == 0){
        return 0;
    }
    else if(x > 0){
        return (selNum(x) >= 5)? ceil(x) : floor(x);
    }
    else if(x < 0){
        return (selNum(abs(x) >= 5)? floor(x) : ceil(x);
    }   
    else return 0;
}

int selNum(int &x){
    x*=10;
    return (x%10);
}
