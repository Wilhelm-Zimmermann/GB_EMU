#include <stdint.h>
#include "./headers/bitwise.h"
#include "./headers/bit.h"
#include "./headers/register.h"

void rotateLeftCircular8b(Register *reg, uint8_t *value)
{
    uint8_t msb = getMsb(*value);
    *value = (*value << 1) | msb;
    if (msb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }

    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}

void rotateRightCircular8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = getLsb(*value);
    *value = (*value >> 1) | (lsb << 7);
    if (lsb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}

void rotateLeft8b(Register *reg, uint8_t *value)
{
    uint8_t msb = getMsb(*value);
    uint8_t cFlag = get_CFlag(reg);
    *value = (*value << 1) | cFlag;
    if (msb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }

    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}

void rotateRight8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = getLsb(*value);
    uint8_t cFlag = get_CFlag(reg);
    *value = (*value >> 1) | (cFlag << 7);
    if (lsb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}

void shiftLeftArithmetic8b(Register *reg, uint8_t *value)
{
    uint8_t msb = getMsb(*value);
    if (msb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
    *value = *value << 1;
    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}

void shiftRightArithmetic8b(Register *reg, uint8_t *value)
{
    uint8_t lsb = getLsb(*value);
    uint8_t msb = getMsb(*value);
    if (lsb)
    {
        set_CFlag(reg);
    }
    else
    {
        unset_CFlag(reg);
    }
    *value = (*value >> 1) | (msb << 7);
    checkIfOpZeroAndSetZ(reg, *value);
    unset_HFlag(reg);
    unset_NFlag(reg);
}