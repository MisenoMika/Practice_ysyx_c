#include <stdio.h>
long long bit_multiply (unsigned x, unsigned y) {
    long long result = 0;
    while(y) {
        if( (y & 0x00000001) != 0) {
            result += x;
        }
        x <<= 1;
        y >>= 1;
    }
    return result;
}

int main(void) {
    unsigned x = 0x000123a0;
    unsigned y = 0x00112233;
    long long count = bit_multiply(x, y);
    printf("%lld\n", count);
    long long int correct_answ = x * y;
    printf("%lld\n", correct_answ);
}