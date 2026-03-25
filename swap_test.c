#include <stdio.h>

void xor_swap_ptr(int *a, int *b) {
    // 不检查别名的版本 —— 如果 a==b，会把值变成 0
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

void add_swap_ptr(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main(void) {
    int x = 50;
    int y = 50;

    // 情形1：不同变量但数值相同
    xor_swap_ptr(&x, &y);
    printf("x = %d, y = %d  (different addresses, same value)\n", x, y);

    // 情形2：同一个地址（alias）
    int z = 5;
    xor_swap_ptr(&z, &z);
    printf("z after xor_swap_ptr(&z,&z) = %d  (same address)\n", z);

    z = 5;
    add_swap_ptr(&z, &z);
    printf("z after add_swap_ptr(&z,&z) = %d  (same address)\n", z);

    return 0;
}