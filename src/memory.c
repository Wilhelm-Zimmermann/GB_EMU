#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./headers/memory.h"
#include "./headers/register.h"
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

uint8_t memoryRead(Memory *mem, uint16_t address)
{
    if (address == 0xFF44)
    {
        return 0x90;
    }
    return mem->ram[address];
}

uint16_t memoryRead16t(Memory *mem, uint16_t address)
{
    uint8_t lowByte = memoryRead(mem, address);
    uint8_t highByte = memoryRead(mem, address + 1);

    return (highByte << 8) | lowByte;
}

void memoryWrite(Memory *mem, uint16_t address, uint8_t value)
{
    if (address == 0xFF01)
    {
        mem->ram[address] = value;
        return;
    }

    if (address == 0xFF02 && value == 0x81)
    {
        printf("%c", mem->ram[0xFF01]);
        mem->ram[address] = 0;
        return;
    }
    mem->ram[address] = value;
}

// TODO: Review the stack implementation when implementing MMU
void stack_push16(Register *reg, Memory *mem, uint16_t value)
{
    reg->SP--;
    memoryWrite(mem, reg->SP, (uint8_t)(value >> 8));

    reg->SP--;
    memoryWrite(mem, reg->SP, (uint8_t)(value & 0xFF));
}

uint16_t stack_pop16(Register *reg, Memory *mem)
{
    uint8_t lowByte = memoryRead(mem, reg->SP);
    reg->SP++;

    uint8_t highByte = memoryRead(mem, reg->SP);
    reg->SP++;

    return (uint16_t)((highByte << 8) | lowByte);
}