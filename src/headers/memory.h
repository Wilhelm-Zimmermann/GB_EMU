#pragma once
#include <stdint.h>

typedef struct
{
    int vRamSize;
    int ramSize;
    uint8_t *ram;
    uint8_t *vRam;
} Memory;

void initMemory(Memory *mem);
uint8_t readByte(Memory *mem, uint16_t address);
void writeByte(Memory *mem, uint16_t address, uint8_t value);