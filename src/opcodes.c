#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/memory.h"

// INC and DEC 8 bit instr - must check half carry before incrementing
void instr_inc8b(Register *reg, uint8_t *value)
{
    if ((*value & 0x0F) == 0x0F)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }

    (*value)++;

    unset_NFlag(reg);

    checkIfOpZeroAndSetZ(reg, *value);
    incrementPC(reg);
}

void instr_dec8b(Register *reg, uint8_t *value)
{
    if ((*value & 0x0F) == 0x00)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }

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
    *regValue = value;
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
    checkIfHasCarryAndSet8b(reg, *regToAdd, valueToAdd);
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
    checkIfHasCarryAndSet8bWithCarry(reg, *regToAdd, valueToAdd, carry);
    *regToAdd = (uint8_t)sumValue;
    incrementPC(reg);
}

void instr_sub8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_NFlag(reg);
    checkIfHasBorrowAndSet8b(reg, originalValue, valueToSub);
    checkIfHasBorrowAndSetC8b(reg, originalValue, valueToSub);
    // setCFlagIfAddOpLtThan0(reg, subrResult);

    *regToSubFrom = subrResult;

    checkIfOpZeroAndSetZ(reg, *regToSubFrom);
    incrementPC(reg);
}

void instr_sub8bWithCarry(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t carry = get_CFlag(reg);
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub - carry;

    set_NFlag(reg);
    checkIfHasBorrowAndSet8bWithCarry(reg, originalValue, valueToSub, carry);
    checkIfHasBorrowAndSetC8bWithCarry(reg, originalValue, valueToSub, carry);
    // setCFlagIfAddOpLtThan0(reg, subrResult);

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

// CP
void instr_cp8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_NFlag(reg);
    checkIfHasBorrowAndSet8b(reg, originalValue, valueToSub);
    // setCFlagIfAddOpLtThan0(reg, subrResult);

    checkIfOpZeroAndSetZ(reg, subrResult);
    if (originalValue < valueToSub)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
    incrementPC(reg);
}

// Stack Instructions
void instr_callAddr16(Register *reg, Memory *mem)
{
    uint16_t stackPushAddr = reg->PC + 3;
    stack_push16(reg, mem, stackPushAddr);
    uint16_t callAddr = memoryRead16t(mem, reg->PC + 1);
    reg->PC = callAddr;
}
void instr_jpNxt16(Register *reg, Memory *mem)
{
    uint16_t jmpAddr = memoryRead16t(mem, reg->PC + 1);
    reg->PC = jmpAddr;
}

void instr_ret(Register *reg, Memory *mem)
{
    uint16_t stackAddr = stack_pop16(reg, mem);
    reg->PC = stackAddr;
}

void instr_rst(Register *reg, Memory *mem, uint16_t rstAddr)
{
    uint16_t stackPushAddr = reg->PC + 1;
    stack_push16(reg, mem, stackPushAddr);
    reg->PC = rstAddr;
}