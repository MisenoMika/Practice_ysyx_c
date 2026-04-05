#include <include/minirvEMU.h>

void test2() { //add & lui
    print_bin(R[1], 32, "R[1]");
    print_bin(R[2], 32, "R[2]");
    print_bin(R[3], 32, "R[3]");
    print_bin(R[4], 32, "R[4]");
    print_bin(PC, 32, "PC");
    if(cnt >= 20) {
        check(R[1] == 5, "R[1] != 5");
        check(R[2] == 0x12345000, "R[2] != 0x12345000");
        check(R[3] == 10, "R[3] != 10");
        check(R[4] == 0x1234500A, "R[4] == 0x1234500A");
        printf("\n HIT GOOD TRAP!\n");
        ebreak();
    }
    return;
error:
    ebreak();
    return;
}