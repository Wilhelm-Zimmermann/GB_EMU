#pragma once
#include "./register.h"
#include "./memory.h"

typedef struct
{
} CPU;

uint8_t cpu_cycle(Register* reg, Memory* mem);
void initRegisters(Register* reg);