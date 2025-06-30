#include "register.h"

void initialize(Register *reg)
{
    reg->AF = 0;
    reg->BC = 0;
    reg->DE = 0;
    reg->HL = 0;

    reg->SP = 0;
    reg->PC = 0x104;
}