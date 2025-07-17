#include "register.h"

const int Z_FLAG_BIT = 7;
const int N_FLAG_BIT = 6;
const int H_FLAG_BIT = 5;
const int C_FLAG_BIT = 4;

void initialize(Register *reg)
{
    reg->AF = 0;
    reg->BC = 0;
    reg->DE = 0;
    reg->HL = 0;

    reg->SP = 0;
    reg->PC = 0x100;
}

void set_ZFlag(Register *reg)
{
    reg->F |= (1 << Z_FLAG_BIT);
}

void set_CFlag(Register *reg)
{
    reg->F |= (1 << C_FLAG_BIT);
}

void set_NFlag(Register *reg)
{
    reg->F |= (1 << N_FLAG_BIT);
}

void set_HFlag(Register *reg)
{
    reg->F |= (1 << H_FLAG_BIT);
}

void unset_ZFlag(Register *reg)
{
    reg->F &= ~(1 << Z_FLAG_BIT);
}

void unset_CFlag(Register *reg)
{
    reg->F &= ~(1 << C_FLAG_BIT);
}

void unset_NFlag(Register *reg)
{
    reg->F &= ~(1 << N_FLAG_BIT);
}

void unset_HFlag(Register *reg)
{
    reg->F &= ~(1 << H_FLAG_BIT);
}


// Todo: implement better functions for H flag, specially for addition and subtraction
void checkIfHasCarryIncAndSetH8b(Register *reg, uint8_t value)
{
    if ((value & 0x0F) == 0x00)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }
}

void checkIfHasCarryAndSetH16b(Register *reg, uint16_t value)
{
    if (value > 0x0FFF)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }
}

void checkIfOpZeroAndSetZ(Register *reg, uint8_t value)
{
    if (value == 0)
    {
        set_ZFlag(reg);
    }
    else
    {
        unset_ZFlag(reg);
    }
}

// TODO: revise these c flags logic
void setCFlagIfAddOpGtThanFF(Register *reg, uint16_t value)
{
    if (value > 0xFF)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
}
void setCFlagIfAddOpGtThanFFFF(Register *reg, uint32_t value)
{
    if (value > 0xFFFF)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
}

void checkIfHasCarryAddAndSetH8b(Register *reg, uint8_t nibbleSum)
{
    if (nibbleSum > 0x0F)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }
}

void checkIfHasCarrySubAndSetH8b(Register *reg, uint8_t value)
{
    int8_t signedValue = (int8_t) value;

    if (signedValue < 0)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_HFlag(reg);
    }
}

void setCFlagIfAddOpLtThan0(Register *reg, uint16_t value)
{
    int16_t signedValue = (int16_t) value;
    if (signedValue < 0)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
}

void incrementPC(Register *reg)
{
    reg->PC++;
}

uint8_t get_CFlag(Register *reg)
{
    return reg->F >> C_FLAG_BIT;
}

uint8_t get_ZFlag(Register *reg)
{
    return reg->F >> Z_FLAG_BIT;
}

uint8_t get_NFlag(Register *reg)
{
    return reg->F >> N_FLAG_BIT;
}

uint8_t get_HFlag(Register *reg)
{
    return reg->F >> H_FLAG_BIT;
}
