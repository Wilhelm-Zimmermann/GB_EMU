#include "register.h"

const int Z_FLAG_BIT = 7;
const int N_FLAG_BIT = 6;
const int H_FLAG_BIT = 5;
const int C_FLAG_BIT = 4;

void initialize(Register *reg)
{
    // reg->AF = 0;
    // reg->BC = 0;
    // reg->DE = 0;
    // reg->HL = 0;

    reg->A = 0x01;
    reg->F = 0xB0;
    reg->B = 0x00;
    reg->C = 0x13;
    reg->D = 0x00;
    reg->E = 0xD8;
    reg->H = 0x01;
    reg->L = 0x4D;

    reg->IME = 0;           
    reg->ime_scheduled = 0;
    reg->halted = 0;
    reg->stopped = 0;

    reg->SP = 0xFFFE;
    reg->PC = 0x100;
}

void set_z_flag(Register *reg)
{
    reg->F |= (1 << Z_FLAG_BIT);
}

void set_c_flag(Register *reg)
{
    reg->F |= (1 << C_FLAG_BIT);
}

void set_n_flag(Register *reg)
{
    reg->F |= (1 << N_FLAG_BIT);
}

void set_HFlag(Register *reg)
{
    reg->F |= (1 << H_FLAG_BIT);
}

void unset_z_flag(Register *reg)
{
    reg->F &= ~(1 << Z_FLAG_BIT);
}

void unset_c_flag(Register *reg)
{
    reg->F &= ~(1 << C_FLAG_BIT);
}

void unset_n_flag(Register *reg)
{
    reg->F &= ~(1 << N_FLAG_BIT);
}

void unset_h_flag(Register *reg)
{
    reg->F &= ~(1 << H_FLAG_BIT);
}

// Todo: implement better functions for H flag, specially for addition and subtraction
// H FLAGS
void check_if_has_carry_and_set_8b(Register *reg, uint8_t value1, uint8_t value2)
{
    if ((value1 & 0x0F) + (value2 & 0x0F) > 0xF)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }
}

void check_if_has_borrow_and_set_8b(Register *reg, uint8_t value1, uint8_t value2)
{
    if ((value1 & 0x0F) < (value2 & 0x0F))
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }
}

void check_if_has_carry_and_set_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry)
{
    if (((value1 & 0x0F) + (value2 & 0x0F) + carry) > 0x0F)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }
}
void check_if_has_borrow_and_set_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry)
{
    int16_t result = (value1 & 0x0F) - (value2 & 0x0F) - carry;

    if (result < 0)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }
}

void check_if_has_carry_and_set_h_16b(Register *reg, uint16_t value)
{
    if (value > 0x0FFF)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }
}

// Z FLAG
void check_if_op_zero_and_set_z(Register *reg, uint8_t value)
{
    if (value == 0)
    {
        set_z_flag(reg);
    }
    else
    {
        unset_z_flag(reg);
    }
}

// C FLAG
void set_c_flag_if_add_op_gt_FF(Register *reg, uint16_t value)
{
    if (value > 0xFF)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}
void set_c_flag_if_add_op_gt_FFFF(Register *reg, uint32_t value)
{
    if (value > 0xFFFF)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}

void check_if_has_borrow_and_set_c_8b(Register *reg, uint8_t value1, uint8_t value2)
{
    if (value1 < value2)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}

void check_if_has_borrow_and_set_c_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry)
{
    int16_t result = (value1 & 0x0F) - (value2 & 0x0F) - carry;

    if (result < 0)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}

void set_c_flag_if_add_lt_0(Register *reg, uint16_t value)
{
    int16_t signedValue = (int16_t)value;
    if (signedValue < 0)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}

void increment_pc(Register *reg)
{
    reg->PC++;
}

uint8_t get_c_flag(Register *reg)
{
    return (reg->F >> C_FLAG_BIT) & 1;
}

uint8_t get_z_flag(Register *reg)
{
    return (reg->F >> Z_FLAG_BIT) & 1;
}

uint8_t get_n_flag(Register *reg)
{
    return (reg->F >> N_FLAG_BIT) & 1;
}

uint8_t get_h_flag(Register *reg)
{
    return (reg->F >> H_FLAG_BIT) & 1;
}
