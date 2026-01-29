#include <stdio.h>
#define N 3
#define M 2
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

void arrangement(int *a, int start, int last){
    if(start == last){
        printArrange(a, last);
        return;
    }

    for(int i = start; i < last; i++){
        swap(a, start, i);
        arrangement(a, start + 1, last);
        swap(a, start, i);
    }
}

int main(void){
    int a[N];
    for(int i = 0; i < N; i++){
        a[i] = i+1;
    }
    arrangement(a, 0, N);
}