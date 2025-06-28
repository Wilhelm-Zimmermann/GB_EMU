#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t *memory;
} Memory;

void initMemory(Memory *mem);