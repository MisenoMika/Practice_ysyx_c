#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int stop = 0;
uint8_t PC = 0;
uint8_t R[4];
uint8_t M[16] = {
/*0*/    0b10001010,
/*1*/    0b10010000,
/*2*/    0b10100000,
/*3*/    0b10110001,
/*4*/    0b00010111,
/*5*/    0b00101001,
/*6*/    0b11010001,
/*7*/    0b01001001,
/*8*/    0b11100011
};

uint8_t Fetch() {
    return M[PC];
}

uint8_t Decode(uint8_t inst, int high, int low) {
    return (inst >> low) & ((1 << (high - low + 1)) - 1);
}

void print_bin(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");
}

void init_r0(int max){
    R[0] = (uint8_t)max;
}

void inst_cycle(int argc, int max) {
    uint8_t opcode, rs1, rs2, rd, imm, addr, cmd;
    cmd = Fetch();
    opcode = Decode(cmd, 7, 6);
    rs1 = Decode(cmd, 3, 2);
    rs2 = Decode(cmd, 1, 0);
    addr= Decode(cmd, 5, 2);
    imm = Decode(cmd, 3, 0);
    rd  = Decode(cmd, 5, 4);

    /*if(R[2] == 55) stop = 1;
    printf("rs1 is :");
    print_bin(rs1);
    printf("rs2 is :");
    print_bin(rs2);
    printf("imm is :");
    print_bin(imm);
    printf("addr is :");
    print_bin(addr);
    for (int i = 0; i <= 4; i++){
        printf("R[%d] is :", i);
        print_bin(R[i]);
    }

    printf("\n");
    //usleep(500000);*/

    if(PC == 1 && argc == 2)init_r0(max);
    switch (opcode)
    {
    case 0b00:
        R[rd] = R[rs1] + R[rs2];
        PC += 1;

        break;
    case 0b01:
        printf("\n<out>:\n");
        printf("R[%d] is :", (int)rs1);
        print_bin(R[rs1]);
        printf("R[%d] is :", (int)rs2);
        print_bin(R[rs2]);
        PC += 1;

        break;
    case 0b10:
        R[rd] = imm;
        PC += 1;
        break;
    case 0b11:
        if(R[0] != R[rs2]){
            PC = addr;
        } else {
            PC += 1;
        }      
        break;
    default:
        break;
    }
}



int main(int argc, char** argv) {
    int max = argc == 2 ? atoi(argv[1]) : 10;

    while (!stop) { inst_cycle(argc, max); }
    uint8_t test = Decode(0b10001010, 7, 0);
    print_bin(test);
    if(0b10 == 0b00000010) printf("yes\n");
    if(0b10 == 2)printf("well done\n");
    return 0;
}
// 1+2+...15 = 120 = 0b0111_1000
