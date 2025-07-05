#pragma once
#include <stdint.h>
#include "register.h"
#include "memory.h"

// LD
void instr_ld8bIn8b(Register *reg, uint8_t *fromValue, uint8_t *toValue);
void instr_ldNxt8bAddrInReg(Register *reg, Memory *mem, uint8_t *value);
void instr_ldReg8bInAddr(Register *reg, Memory *mem, uint8_t *value);

void instr_ldAddr8bInReg(Register *reg, Memory *mem, uint16_t memAddr, uint8_t *value);
void instr_ldNxt16bAddrInReg(Register *reg, Memory *mem, uint16_t *regValue);

// INC/DEC
void instr_inc8b(Register *reg, uint8_t *value);
void instr_dec8b(Register *reg, uint8_t *value);

// ADD/SUBTR
void instr_add8b(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd);
void instr_add8bWithCarry(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd);
void instr_sub8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub);
void instr_sub8bWithCarry(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub);

void instr_add16b(Register *reg, uint16_t *regToAdd, uint16_t valueToAdd);