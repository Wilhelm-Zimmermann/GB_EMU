#include "./headers/bitwise.h"

uint8_t getMsb(uint8_t value)
{
    return (value >> 7) & 1;
}

uint8_t getLsb(uint8_t value)
{
    return value & 1;
}