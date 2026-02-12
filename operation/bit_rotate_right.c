#include <stdio.h>

unsigned int rotate_right (unsigned int bits, int x) {
    const unsigned int width = 8u * (unsigned int)sizeof(unsigned int);
    while(x) {
        x--;
        unsigned int tmp = (bits&1u);
        bits = (bits >> 1) | (tmp <<(width - 1));
    }
    return bits;
}

unsigned int rotate_right_2 (unsigned int bits, int x){
    return (bits >> x) | (bits << (sizeof(unsigned int)*8u - x));
}

int main(void) {
    unsigned int x = 0xdeadbeef;
    x = rotate_right(x, 16);
    printf("%x\n", x);
    x = rotate_right_2(x, 16);
    printf("%x\n", x);
}