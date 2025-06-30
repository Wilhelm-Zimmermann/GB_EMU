#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./headers/memory.h"
#define DEBUG

void initMemory(Memory *mem)
{
#ifdef DEBUG
    printf("Allocating RAM...\n");
#endif
    mem->vRamSize = (1024 * 8);
    mem->ramSize = (1024 * 64);
    mem->ram = malloc(sizeof(uint8_t) * mem->ramSize);
    mem->vRam = malloc(sizeof(uint8_t) * mem->vRamSize);

    if (mem->ram == NULL)
    {
        fprintf(stderr, "RAM could not be allocated!!");
        return;
    }
}

uint8_t read_byte(Memory *mem, uint16_t address)
{
    return mem->ram[address];
}