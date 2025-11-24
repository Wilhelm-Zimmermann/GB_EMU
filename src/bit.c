#include <stdint.h>
#include "./headers/bitwise.h"
#include "./headers/bit.h"
#include "./headers/register.h"

void rotate_left_circular_8b(Register *reg, uint8_t *value)
{
    uint8_t msb = get_msb(*value);
    *value = (*value << 1) | msb;
    if (msb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }

    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void rotate_right_circular_8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = get_lsb(*value);
    *value = (*value >> 1) | (lsb << 7);
    if (lsb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void rotate_left_8b(Register *reg, uint8_t *value)
{
    uint8_t msb = get_msb(*value);
    uint8_t cFlag = get_c_flag(reg);
    *value = (*value << 1) | cFlag;
    if (msb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }

    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void rotate_right_8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = get_lsb(*value);
    uint8_t cFlag = get_c_flag(reg);
    *value = (*value >> 1) | (cFlag << 7);
    if (lsb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void shift_left_arithmetic_8b(Register *reg, uint8_t *value)
{
    uint8_t msb = get_msb(*value);
    if (msb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
    *value = *value << 1;
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void shift_right_arithmetic_8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = get_lsb(*value);
    uint8_t msb = get_msb(*value);
    if (lsb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
    *value = (*value >> 1) | (msb << 7);
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void swap_8b(Register *reg, uint8_t *value)
{
    uint8_t lowerNibble = *value & 0x0F;
    uint8_t highNibble = (*value >> 4);
    *value = (lowerNibble << 4) | highNibble;
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
    unset_c_flag(reg);
}

void shift_right_logical_8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = get_lsb(*value);
    if (lsb)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }

    *value = *value >> 1;
    check_if_op_zero_and_set_z(reg, *value);
    unset_h_flag(reg);
    unset_n_flag(reg);
}

void check_bit(Register *reg, uint8_t *value, uint8_t bitPos)
{
    uint8_t extractedBit = (*value >> bitPos) & 1;
    check_if_op_zero_and_set_z(reg, extractedBit);
    unset_n_flag(reg);
    set_HFlag(reg);
}

void reset_bit(Register *reg, uint8_t *value, uint8_t bitPos)
{
    *value &= ~(1 << bitPos);
}

void set_bit(Register *reg, uint8_t *value, uint8_t bitPos)
{
    *value |= (1 << bitPos);
}