#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/memory.h"

// INC and DEC 8 bit instr
void instr_inc8b(Register *reg, uint8_t *value)
{
    (*value)++;
    unset_NFlag(reg);
    checkIfOpZeroAndSetZ(reg, *value);
    checkIfHasCarryIncAndSetH8b(reg, *value);
    incrementPC(reg);
}

void instr_dec8b(Register *reg, uint8_t *value)
{
    checkIfHasCarryIncAndSetH8b(reg, *value);
    (*value)--;
    set_NFlag(reg);
    checkIfOpZeroAndSetZ(reg, *value);
    incrementPC(reg);
}

// LD 8 bit instr

void instr_ld8bIn8b(Register *reg, uint8_t *fromValue, uint8_t *toValue)
{
    *fromValue = *toValue;
    incrementPC(reg);
}

void instr_ldNxt8bAddrInReg(Register *reg, Memory *mem, uint8_t *value)
{
    uint8_t addrValue = memoryRead(mem, reg->PC + 1);
    *value = addrValue;
    reg->PC += 2;
}

void instr_ldAddr8bInReg(Register *reg, Memory *mem, uint16_t memAddr, uint8_t *value)
{
    uint8_t addrValue = memoryRead(mem, memAddr);
    *value = addrValue;
    incrementPC(reg);
}

// LD 16 bit instr
void instr_ldNxt16bAddrInReg(Register *reg, Memory *mem, uint16_t *regValue)
{
    uint16_t value = memoryRead16t(mem, reg->PC + 1);
    (*regValue) = value;
    reg->PC += 3;
}

// ADD/SUBTR 16 bit instr
void instr_add16b(Register *reg, uint16_t *regToAdd, uint16_t valueToAdd)
{
    uint32_t sumValue = (uint32_t)(*regToAdd) + (uint32_t)valueToAdd;
    unset_NFlag(reg);
    checkIfHasCarryAndSetH16b(reg, (((*regToAdd) & 0x0FFF) + (valueToAdd & 0x0FFF)));
    setCFlagIfAddOpGtThanFFFF(reg, sumValue);
    *regToAdd = (uint16_t)sumValue;
    incrementPC(reg);
}

// ADD/SUBTR 8 bit instr
void instr_add8b(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd)
{
    uint16_t sumValue = (uint16_t)(*regToAdd) + (uint16_t)valueToAdd;
    unset_NFlag(reg);
    setCFlagIfAddOpGtThanFF(reg, sumValue);
    checkIfOpZeroAndSetZ(reg, (uint8_t)sumValue);
    checkIfHasCarryAddAndSetH8b(reg, (*regToAdd & 0x0F) + (valueToAdd & 0x0F));
    *regToAdd = (uint8_t)sumValue;
    incrementPC(reg);
}

void instr_add8bWithCarry(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd)
{
    uint8_t carry = get_CFlag(reg);
    uint16_t sumValue = (uint16_t)(*regToAdd) + (uint16_t)valueToAdd + (uint16_t)carry;
    unset_NFlag(reg);
    setCFlagIfAddOpGtThanFF(reg, sumValue);
    checkIfOpZeroAndSetZ(reg, (uint8_t)sumValue);
    checkIfHasCarryAddAndSetH8b(reg, (*regToAdd & 0x0F) + (valueToAdd & 0x0F) + carry);
    *regToAdd = (uint8_t)sumValue;
    incrementPC(reg);
}

void instr_sub8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_NFlag(reg);
    checkIfHasCarrySubAndSetH8b(reg, (originalValue & 0x0F) - (valueToSub & 0x0F));
    setCFlagIfAddOpLtThan0(reg, subrResult);

    *regToSubFrom = subrResult;

    checkIfOpZeroAndSetZ(reg, *regToSubFrom);
    incrementPC(reg);
}

void instr_sub8bWithCarry(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t carry = get_CFlag(reg);
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_NFlag(reg);
    checkIfHasCarrySubAndSetH8b(reg, (originalValue & 0x0F) - (valueToSub & 0x0F) - carry);
    setCFlagIfAddOpLtThan0(reg, subrResult);

    *regToSubFrom = subrResult;

    checkIfOpZeroAndSetZ(reg, *regToSubFrom);
    incrementPC(reg);
}

// Normal bitwise
void instr_and(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) & to;
    checkIfOpZeroAndSetZ(reg, *from);
    set_HFlag(reg);
    unset_NFlag(reg);
    unset_CFlag(reg);
    incrementPC(reg);
}
void instr_xor(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) ^ to;
    checkIfOpZeroAndSetZ(reg, *from);
    unset_HFlag(reg);
    unset_NFlag(reg);
    unset_CFlag(reg);
    incrementPC(reg);
}
void instr_or(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) | to;
    checkIfOpZeroAndSetZ(reg, *from);
    unset_HFlag(reg);
    unset_NFlag(reg);
    unset_CFlag(reg);
    incrementPC(reg);
}