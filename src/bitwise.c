#include "./headers/bitwise.h"

uint8_t get_msb(uint8_t value)
{
    return (value >> 7) & 1;
}

uint8_t get_lsb(uint8_t value)
{
    return value & 1;
}