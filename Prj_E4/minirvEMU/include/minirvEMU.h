#ifndef MINIRVEMU_H
#define MINIRVEMU_H

#include <stdint.h>
#include "dbg.h"

#ifndef BITS_WIDTH
#define BITS_WIDTH 32
#endif

#ifndef ADDR_WIDTH
#define ADDR_WIDTH 24
#endif

extern uint32_t ROM[1 << ADDR_WIDTH];
extern uint32_t RAM[1 << ADDR_WIDTH];
extern uint32_t R[16];

extern uint32_t PC;
extern int cnt;
extern int stop;

extern uint32_t opcode;
extern uint32_t funct3;
extern uint32_t funct7;
extern uint32_t rs1;
extern uint32_t rs2;
extern uint32_t rd;
extern uint32_t cmd;
extern uint32_t imm5;
extern uint32_t imm7;
extern uint32_t imm12;
extern uint32_t imm20;
extern uint32_t RAM_addr;
extern uint32_t RAM_sel;

uint32_t Fetch(void);
uint32_t Decode(uint32_t inst, int high, int low);

void init_ROM(uint32_t *ROM);
void print_bin(uint32_t x, int width, char *name);
void print_inst(const uint32_t *inst, int depth, char *name);
void load_bin(char *filename, uint32_t *mem);
uint32_t sign_extendsion(uint32_t imm, int bits);

void add(void);
void lui(void);
void addi(void);
void jalr(void);
void ebreak(void);
void sb(void);
void lbu(void);
void sw(void);
void lw(void);
void inst_cycle(void);

#endif
