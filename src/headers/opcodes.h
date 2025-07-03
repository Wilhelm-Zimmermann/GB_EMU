#pragma once
#include <stdint.h>
#include "register.h"

void instr_ld8b();
void instr_ldAddr16b();
void instr_inc8b(Register *reg, uint8_t *value);
void instr_dec8b(Register *reg, uint8_t *value);