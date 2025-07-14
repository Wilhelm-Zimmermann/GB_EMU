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
}

void rotateRight8b(Register *reg, uint8_t *value)
{
}