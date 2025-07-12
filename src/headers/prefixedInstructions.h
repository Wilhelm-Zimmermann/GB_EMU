#pragma once
#include <stdint.h>
#include "./register.h"
#include "./memory.h"

void opcode_xp0(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp1(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp2(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp3(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp4(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp5(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp6(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp7(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp8(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xp9(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpA(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpB(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpC(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpD(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpE(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xpF(Register *reg, Memory *mem,uint8_t opcode);