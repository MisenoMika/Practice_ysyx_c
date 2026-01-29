#include <stdio.h>

int main(void)
{
	int x;
    char input;
    scanf("%d", &x);
    getchar();    
    input = getchar(); 
    int mid = (x+1)/2;
    if(x%2 == 0){
        printf("ERROR\n");
        return 0;
    }
    else {
        for(int i = 1; i <= x; i++){
            int left = (i <= mid)? mid - (i - 1) : mid - (x - i);
            int right = (i <= mid)? mid + (i - 1) : mid + (x - i);
            for(int j = 1; j <= x; j++){
                if(j >= left && j <= right){
                    printf("%c\t", input);
                }
                else{
                    printf(" \t");
                }
            }
            printf("\n");
        }
        return 0;
    }
}