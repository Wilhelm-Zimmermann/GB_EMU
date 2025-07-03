#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/memory.h"

// INC and DEC 8 bit instr
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

// LD 8 bit instr

void instr_ld8b(Register *reg, uint8_t *fromValue, uint8_t *toValue)
{
    *fromValue = *toValue;
    incrementPC(reg);
}

void instr_ldn8bAddr(Register *reg, Memory *mem, uint8_t *value)
{
    uint8_t addrValue = memoryRead(mem, reg->PC + 1);
    *value = addrValue;
    reg->PC += 2;
}

void instr_ldAddr8b(Register *reg, Memory *mem, uint16_t memAddr, uint8_t *value)
{
    uint8_t addrValue = memoryRead(mem, memAddr);
    *value = addrValue;
    incrementPC(reg);
}

// LD 16 bit instr
void instr_ldAddr16bToReg(Register *reg, Memory *mem, uint16_t *regValue)
{
    uint16_t value = memoryRead16t(mem, reg->PC + 1);
    (*regValue) = value;
    reg->PC += 3;
}