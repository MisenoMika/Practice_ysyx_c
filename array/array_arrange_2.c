#include <stdio.h>
#define N 3
#define M 2
void swap(int* a, int index1, int index2){
    int temp = a[index1];
    a[index1] = a[index2];
    a[index2] = temp;

}
void printArrange(int* a, int start, int next, int last){
    printf("%d  ", a[start]);
    for(int i=next; i<last; i++){
        printf("%d  ", a[i]);
    }
    printf("\n");
}

void combination(int* a, int start, int last, int next,int depth){
    if(next + depth == last){
        return;
    }
    else {
        printArrange(a, start, next, last);
    }
    for(int i=0; i<last-1; i++){
        swap(a, start, i);
        combination(a, start, last, next+1, depth);
        swap(a, start, i);
    }
    
}

int main(void){
    int a[N];
    for(int i = 0; i < N; i++){
        a[i] = i+1;
    }
    combination(a, 0, N, M, M);
}