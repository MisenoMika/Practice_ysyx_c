#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <include/dbg.h>
#define BITS_WIDTH 32
#define ADDR_WIDTH 24
#define MEM_SUM_CHECK 1
uint32_t ROM[1 << ADDR_WIDTH];
uint32_t RAM[1 << ADDR_WIDTH];
uint32_t R[16];

uint32_t PC = 0;
int cnt = 0;
int stop = 0;
uint32_t RAM_addr = 0;
uint32_t RAM_sel = 0;
uint32_t opcode, funct3, funct7, rs1, rs2, rd, cmd, imm5, imm7, imm12, imm20;

uint32_t Fetch() {
    return ROM[PC >> 2];
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
    //if(rd != 0)R[rd] = PC + ((MEM_SUM_CHECK)? 1 : 4);//+1or+4取决于是否是一个地址存一个字节
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
    uint32_t sel = addr % 4;
    uint32_t val = R[rs2] & 0xff;
    uint32_t tmp = RAM[(addr - sel) >> 2];
    uint32_t byte1 = Decode(tmp, 7, 0);
    uint32_t byte2 = Decode(tmp, 15, 8);
    uint32_t byte3 = Decode(tmp, 23, 16);
    uint32_t byte4 = Decode(tmp, 31, 24);
    switch(sel)
    {
        case 0:
            RAM[(addr - sel) >> 2] = byte4 << 24 | byte3 << 16 | byte2 << 8 | val;
            break;

        case 1:
            RAM[(addr - sel) >> 2] = byte4 << 24 | byte3 << 16 | val << 8 | byte1;
            break;

        case 2:
            RAM[(addr - sel) >> 2] = byte4 << 24 | val << 16 | byte2 << 8 | byte1;
            break;

        case 3:
            RAM[(addr - sel) >> 2] = val << 24 | byte3 << 16 | byte2 << 8 | byte1;
            break;

        default:
            break;
    }

    RAM_addr = addr;
    RAM_sel = sel;
}

void lbu(){
    uint32_t addr = sign_extendsion(imm12, 12) + R[rs1];
    uint32_t sel = addr % 4;
    R[rd] = Decode(RAM[(addr - sel) >> 2], (sel + 1) * 8 - 1, sel * 8);

    RAM_addr = addr;
    RAM_sel = sel;
}

void sw(){
    uint32_t imm7_5 = (imm7 << 5) | imm5;
    uint32_t addr = R[rs1] + sign_extendsion(imm7_5, 12);
    RAM[addr >> 2] = R[rs2];
    
    RAM_addr = addr;
}

void lw(){
    uint32_t addr = sign_extendsion(imm12, 12) + R[rs1];
    R[rd] = RAM[addr >> 2];
    RAM_addr = addr;
}

void inst_cycle() {
    int is_jalr = 0;
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
            break;

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
            is_jalr = 1;
            break;
        default:
            break;
        }
        break;

    case 0b0000011:
            switch (funct3)
            {
            case 0b100:
                lbu();
                break;
            case 0b010:
                lw();
                break;
            default:
                break;
            }
            break;
        
        break;

    default:
        break;
    }

    PC += (is_jalr)? 0 : 4; 
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