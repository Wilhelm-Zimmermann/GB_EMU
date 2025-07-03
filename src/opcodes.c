#include "./headers/opcodes.h"
#include "./headers/register.h"

void instr_inc8b(Register *reg, uint8_t *value)
{
    (*value)++;
    unset_NFlag(reg);
    checkIfOpZeroAndSetZ(reg, *value);
    checkIfHasCarryAndSetH8b(reg, *value);
    incrementPC(reg);
}

void instr_dec8b(Register *reg, uint8_t *value)
{
    checkIfHasCarryAndSetH8b(reg, *value);
    (*value)--;
    set_NFlag(reg);
    checkIfOpZeroAndSetZ(reg, *value);
    incrementPC(reg);
}