#include <stdio.h>
int countbit(unsigned int x);
int main(void) {
    unsigned x = 0xffff0000;
    int count = countbit(x);
    printf("%d", count);
}

int countbit(unsigned int x){
    unsigned mask = 0x00000001;
    int count = 0;
    for(int i=0; i<sizeof(unsigned)*8; i++){
        count += (x & mask); 
        x = x >> 1;
    }
    return count;
}

int countbit_2(unsigned int x ){
    int count = 0;
    while(x) {
        x &= x-1;
        count++;
    }
    return count;
}