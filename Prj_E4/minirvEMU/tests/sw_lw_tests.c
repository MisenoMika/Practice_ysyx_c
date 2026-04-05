#include <include/minirvEMU.h>

void test3() {
    print_bin(R[1], 32, "R[1]");
    print_bin(R[2], 32, "R[2]");
    print_bin(R[3], 32, "R[3]");
    print_bin(R[4], 32, "R[4]");
    print_bin(RAM[0x10000], 32, "RAM[0x10000]");
    printf("RAM_addr = %#x\n", RAM_addr);
    printf("rd = %u\n", rd);
    printf("rs1 = %u\n", rs1);
    if(cnt >= 20) {
        check(R[1] == 0x00010000, "x1 != 0x00010000");
        check(R[2] == 42, "x2 != 42");
        check(R[3] == 42, "x3 != 42");
        check(R[4] == 84, "x4 != 84");
        printf("\n HIT GOOD TRAP!\n");
        ebreak();
    }
    return;
error:
    ebreak();
    return;
}