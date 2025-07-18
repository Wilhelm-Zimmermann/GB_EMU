#pragma once
#include <stdint.h>
#include "./register.h"
#include "./memory.h"

uint8_t execPrefix(Register *reg, Memory *mem, uint8_t opcode);
uint8_t opcode_xp0(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp1(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp2(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp3(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp4(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp5(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp6(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp7(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp8(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xp9(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpA(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpB(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpC(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpD(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpE(Register *reg, Memory *mem,uint8_t opcode);
uint8_t opcode_xpF(Register *reg, Memory *mem,uint8_t opcode);