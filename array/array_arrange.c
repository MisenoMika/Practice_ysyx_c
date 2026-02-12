#include <stdio.h>
#define N 3 // 总共多少数
#define M 2 // 取多少数进行全排列
void swap(int* a, int index1, int index2){
    int temp = a[index1];
    a[index1] = a[index2];
    a[index2] = temp;

}
void printArrange(int* a, int max){
    for(int i=0; i<max; i++){
        printf("%d  ", a[i]);
    }
    printf("\n");
}

void arrangement(int *a, int start, int depth){
    if(start == depth){
        printArrange(a, depth);
        return;
    }

    for(int i = start; i < N; i++){
        swap(a, start, i);
        arrangement(a, start + 1, M);
        swap(a, start, i);
    }
}

int main(void){
    int a[N];
    for(int i = 0; i < N; i++){
        a[i] = i+1;
    }
    arrangement(a, 0, M);
}