#pragma once
#include <stdint.h>
#include "register.h"
#include "memory.h"

// LD
void instr_ld_8b_in_8b(Register *reg, uint8_t *fromValue, uint8_t *toValue);
void instr_ld_nxt_8b_addr_reg(Register *reg, Memory *mem, uint8_t *value);

void instr_ld_addr_8b_reg(Register *reg, Memory *mem, uint16_t memAddr, uint8_t *value);
void instr_ld_nxt_16b_addr_reg(Register *reg, Memory *mem, uint16_t *regValue);

// INC/DEC
void instr_inc_8b(Register *reg, uint8_t *value);
void instr_dec_8b(Register *reg, uint8_t *value);

// ADD/SUBTR
void instr_add_8b(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd);
void instr_add_8b_with_carry(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd);
void instr_sub_8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub);
void instr_sub_8b_with_carry(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub);

void instr_add_16b(Register *reg, uint16_t *regToAdd, uint16_t valueToAdd);

// Normal Bitwise
void instr_and(Register *reg, uint8_t *from, uint8_t to);
void instr_xor(Register *reg, uint8_t *from, uint8_t to);
void instr_or(Register *reg, uint8_t *from, uint8_t to);

// CP
void instr_cp_8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub);

// Stack Instructions
void instr_callAddr16(Register *reg, Memory *mem);
void instr_jp_nxt16(Register *reg, Memory *mem);
void instr_ret(Register *reg, Memory *mem);
void instr_rst(Register *reg, Memory *mem, uint16_t rstAddr);