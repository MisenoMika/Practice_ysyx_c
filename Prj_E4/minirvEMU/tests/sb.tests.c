#include <include/minirvEMU.h>

void test5() {
    print_bin(R[1], 32, "R[1]");
    print_bin(R[2], 32, "R[2]");
    print_bin(R[3], 32, "R[3]");
    print_bin(R[4], 32, "R[4]");
    print_bin(R[5], 32, "R[5]");
    print_bin(R[6], 32, "R[6]");
    print_bin(R[7], 32, "R[7]");
    print_bin(R[8], 32, "R[8]");
    print_bin(RAM[0x10000], 32, "RAM[0x10000]");
    printf("RAM_addr = %#x\n", RAM_addr);
    printf("RAM_sel = %#x\n", RAM_sel);
    printf("rd = %u\n", rd);
    printf("rs1 = %u\n", rs1);
    if(cnt >= 30) {
        check(R[1] == 0x00010000, "x1 != 0x00010000");
        check(R[2] == 0x12345678, "x2 != 0x12345678");
        check(R[3] == 0x12345678, "x3 != 0x12345678");
        check(R[4] == 0xef, "x4 != 0xef");
        check(R[5] == 0xcd, "x5 != 0xcd");
        check(R[6] == 0xab, "x6 != 0xab");
        check(R[7] == 0x90, "x7 != 0x90");
        check(R[8] == 0x90abcdef, "x7 != 0x90abcdef");
        printf("\n HIT GOOD TRAP!\n");
        ebreak();
    }
    return;
error:
    ebreak();
    return;
}