#include <stdio.h>
int main(void){
    int x=0, y=0;
    scanf("%d", &x);
    scanf("%d", &y);
    int result = (-x)/(y);
    printf("%d\n", -result);
    return 0;
}
