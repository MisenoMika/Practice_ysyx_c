#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "dbg.h"
#define BITS_WIDTH 32
#define ADDR_WIDTH 24
#define DEBUG
uint32_t ROM[1 << ADDR_WIDTH];
uint32_t RAM[1 << ADDR_WIDTH];
uint32_t R[16];

uint32_t PC = 0;
int cnt = 0;
int stop = 0;

uint32_t opcode, funct3, funct7, rs1, rs2, rd, cmd, imm5, imm7, imm12, imm20;

uint32_t Fetch() {
    return ROM[PC];
}

uint32_t Decode(uint32_t inst, int high, int low) {
    return (inst >> low) & ((1 << (high - low + 1)) - 1);
}

void init_ROM(uint32_t *ROM) {
    ROM[0] = 0x01400513;
    ROM[4] = 0x010000e7;
    ROM[8] = 0x00c000e7;
    ROM[12] = 0x00c00067;
    ROM[16] = 0x00a50513;
    ROM[20] = 0x00008067;
}

void print_bin(const uint32_t x, int width, char *name) {
    printf("<%s>: ", name);
    for (int i = width - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if(i % 4 == 0 && i != 0) printf("_");
    }
    printf("\n\n");

    return;
}

void print_inst(const uint32_t *inst, int depth, char *name) {
    check_mem(inst);
    printf("<%s>\n", name);
    for(int i = 0; i < depth; i++) {
        //printf("ROM[%d] :\n", i);
        print_bin(ROM[i], 32, name);
    }

    return;
error:
    return;
}

void load_bin(char *filename, uint32_t *mem) {
    check(filename, "Empty filename !");
    FILE *fp = fopen(filename, "r");
    check(fp, "%s dosen't exist!", filename);
    uint8_t buf[4];

    int i = 0;
    while (fread(buf, 1, 4, fp) == 4) {
        mem[i] = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
        i++;
    }

    fclose(fp);

    return;
error:  
    return;
}

uint32_t sign_extendsion(uint32_t imm, int bits) {
    signed int sign_bit = (unsigned int)(imm << (32 - bits));
    uint32_t result = imm | (sign_bit >> (32 - bits));
    //print_bin(result, 32, "result");
    return result;
}


void add() {
    R[rd] = R[rs1] + R[rs2];
    return;
}

void lui(){
    R[rd] = (imm20 << 12);
}

void addi() {
    if(rd != 0)R[rd] = R[rs1] + sign_extendsion(imm12, 12);
    return;
}

void jalr() {
    uint32_t addr = ((sign_extendsion(imm12, 12) + R[rs1])) & 0xfffffffe;
    if(rd != 0)R[rd] = PC + 4;
    PC = addr;

    return;
}

void ebreak() {
    stop = 1;
}

void sb(){
    uint32_t imm7_5 = (imm7 << 5) | imm5;
    uint32_t addr = R[rs1] + sign_extendsion(imm7_5, 12);
    uint32_t offset = addr % 4;
    uint32_t val = R[rs2];
    switch(offset)
    {
        case 0:
            
            break;

        case 1:
        case 2:
        case 3:
        default:
            break;
    }
}

void lbu(){
    uint32_t addr = R[rs1] + sign_extendsion(imm12, 12);
    uint32_t offset = addr % 4;
    R[rd] = (uint32_t)(uint8_t)(Decode(RAM[addr - offset], (offset + 1) * 8, offset * 8));
}

void sw(){
    uint32_t imm7_5 = (imm7 << 5) | imm5;
    uint32_t addr = R[rs1] + sign_extendsion(imm7_5, 12);
    RAM[addr] = R[rs2];
    
}

void lw(){
    uint32_t addr = sign_extendsion(imm12, 12) + R[rs1];
    R[rd] = RAM[addr];
}

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

void test2() {
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
void inst_cycle() {
    R[0] = 0;

    cmd = Fetch();
    funct3 = Decode(cmd, 14, 12);
    funct7 = Decode(cmd, 31, 25);
    opcode = Decode(cmd, 6, 0);
    rs1 = Decode(cmd, 19, 15);
    rs2 = Decode(cmd, 24, 20);
    rd = Decode(cmd, 11, 7);
    imm5 = Decode(cmd, 11, 7);
    imm7 = Decode(cmd, 31, 25);
    imm12 = Decode(cmd, 31, 20);
    imm20 = Decode(cmd, 31, 12);

    PC += 4;
    switch (opcode)
    {
    case 0b0010011:
        switch (funct3)
            {
            case 0b000:
                addi();
                break;
            
            default:
                break;
            }
            break;
        break;

    case 0b0110011:
            add();
            break;
    case 0b0110111:
            lui();
    case 0b0100011:
        switch (funct3)
        {
        case 0b000:
            sb();
            break;
        case 0b010:
            sw();
        default:
            break;
        }
        break;

    case 0b1100111:
        //jalr();
        switch (funct3)
        {
        case 0b000:
            jalr();
            break;
    case 0b0000011:
            switch (funct3)
            {
            case 0b100:
                lbu();
                break;
            case 0b000:
                lw();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    //usleep(500000);
    cnt += 1;
    return;
}

int main(int argc, char **argv) {
    //print_bin(0xf80, 32, "test");

    //char *test_func;
    if(argc > 2) {
        printf("Usage: minirvEMU.exe <file.bin> \n");
        return 1;
    } else if(argc == 2) {
        char *file = argv[1];
        load_bin(file, ROM);
        load_bin(file, RAM);
    } else {
        init_ROM(ROM);
    }

    while(!stop){inst_cycle();}
    
    return 0;
}