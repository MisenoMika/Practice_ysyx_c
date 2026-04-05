#include <include/minirvEMU.h>

void test1() {
    print_bin(R[10], 32, "R[10]");
    print_bin(R[1], 32, "R[1]");
    print_bin(PC, 32, "PC");
    if(cnt >= 20) {
        check(R[10] == 30, "x10 != 30");
        check(R[1] == 0x0c, "x1 != 0x0c");
        check(PC == 0x0c, "PC != 0x0c");
        printf("\n HIT GOOD TRAP!\n");
        ebreak();
    }
    return;
error:
    ebreak();
    return;
}