#pragma once
#include <stdint.h>
#include "./register.h"
#include "./memory.h"

void opcode_x0(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x1(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x2(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x3(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x4(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x5(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x6(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x7(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x8(Register *reg, Memory *mem,uint8_t opcode);
void opcode_x9(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xA(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xB(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xC(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xD(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xE(Register *reg, Memory *mem,uint8_t opcode);
void opcode_xF(Register *reg, Memory *mem,uint8_t opcode);