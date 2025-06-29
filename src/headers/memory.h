#pragma once
#include <stdint.h>

typedef struct
{
    int vRamSize;
    uint8_t *memory;
    uint8_t *vRam;
} Memory;

void initMemory(Memory *mem);