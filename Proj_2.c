#include <stdio.h>
int main(){
    printf("%c\n",'%');
    int x = 0, y = 0;
    scanf("%d", &x);
    scanf("%d", &y);
    if(x%y == 0){
        x /= y;
    }
    else if(x%y != 0){
        x = x/y + 1;
    }
    printf("%d\n",x);    
}
