#include <stdio.h>

void swap(int a, int b) {
    a = a ^ b;
    b = b ^ a; // b = b^b ^ a = 0^a = a
    a = a ^ b; // a = a^b^a = b
    printf("a = %d, b = %d\n", a, b);
}
void swap_2 (int a, int b){
    a = a + b; // a = a + a = 2a
    b = a - b; // a = 2a -a = a
    a = a - b; // a = 2a -a = a
    printf("a = %d, b = %d\n", a, b);
}
int main(void) {
    swap(50, 50);
    swap_2(10, 50);
}