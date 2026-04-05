#include <include/minirvEMU.h>

void test6(void) {
    if(cnt >= 7000){
        printf("PC: %#x\n", PC);
        check(R[10] == 0, "R[10] != 0")
        check(PC >= 0x224 && PC <= 0x228, "PC is out of <halt>");
        printf("\n HIT GOOD TRAP!\n");
        ebreak();
    }
    
    return;
error:
    ebreak();
    return;
}