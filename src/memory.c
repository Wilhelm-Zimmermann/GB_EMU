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
    // TODO: make mallocs safer
    mem->romBank0Size = (1024 * 16);
    mem->romBankNSize = (1024 * 16);
    mem->extRamSize = (1024 * 8);

    mem->vRamSize = (1024 * 8);
    mem->wramSize = (1024 * 8);

    mem->oamSize = (160);
    mem->ioRegsSize = (128);
    mem->hRamSize = 127;

    mem->interrupt_enable_register = 0;

    mem->romBank0 = malloc(mem->romBank0Size);
    mem->vRam = malloc(mem->vRamSize);
    mem->romBankN = malloc(mem->romBankNSize);
    mem->extRam = malloc(mem->extRamSize);
    mem->wram = malloc(mem->wramSize);
    mem->oam = malloc(mem->oamSize);
    mem->ioRegs = malloc(mem->ioRegsSize);
    mem->hRam = malloc(mem->hRamSize);

    if (mem->romBank0 == NULL || mem->romBankN == NULL || mem->extRam == NULL || mem->vRam == NULL || mem->wram == NULL || mem->oam == NULL || mem->ioRegs == NULL || mem->hRam == NULL)
    {
        fprintf(stderr, "RAM could not be allocated!!");
        return;
    }
}

void freeMemory(Memory *mem)
{
    free(mem->romBank0);
    free(mem->vRam);
    free(mem->romBankN);
    free(mem->extRam);
    free(mem->wram);
    free(mem->oam);
    free(mem->ioRegs);
    free(mem->hRam);
    free(mem->fullRom);
}

uint8_t memoryRead(Memory *mem, uint16_t address)
{
    if (address <= 0x3FFF)
    {
        return mem->romBank0[address];
    }
    else if (address <= 0x7FFF)
    {
        return mem->romBankN[address - 0x4000];
    }
    else if (address <= 0x9FFF)
    {
        return mem->vRam[address - 0x8000];
    }
    else if (address <= 0xBFFF)
    {
        return mem->extRam[address - 0xA000];
    }
    else if (address <= 0xDFFF)
    {
        return mem->wram[address - 0xC000];
    }
    else if (address <= 0xFDFF)
    {
        return mem->wram[address - 0xE000];
    }
    else if (address <= 0xFE9F)
    {
        return mem->oam[address - 0xFE00];
    }
    else if (address <= 0xFEFF)
    {
        return 0xFF;
    }
    else if (address <= 0xFF7F)
    {
        return mem->ioRegs[address - 0xFF00];
    }
    else if (address <= 0xFFFE)
    {
        return mem->hRam[address - 0xFF80];
    }
    else if (address == 0xFFFF)
    {
        return mem->interrupt_enable_register;
    }

    return 0;
}

uint16_t memoryRead16t(Memory *mem, uint16_t address)
{
    uint8_t lowByte = memoryRead(mem, address);
    uint8_t highByte = memoryRead(mem, address + 1);

    return (highByte << 8) | lowByte;
}

void memoryWrite(Memory *mem, uint16_t address, uint8_t value)
{
    // ROM MEMORY - cannot write on this area (read - only - memory)
    if (address <= 0x7FFF)
    {
        return;
    }
    // VIDEO RAM
    if (address >= 0x8000 && address <= 0x9FFF)
    {
        mem->vRam[address - 0x8000] = value;
        return;
    }

    // EXT RAM
    if (address >= 0xA000 && address <= 0xBFFF)
    {
        mem->extRam[address - 0xA000] = value;
        return;
    }

    // WORK RAM
    if (address >= 0xC000 && address <= 0xDFFF)
    {
        mem->wram[address - 0xC000] = value;
        return;
    }

    // Object Attribute Memory
    if (address >= 0xFE00 && address <= 0xFE9F)
    {
        mem->oam[address - 0xFE00] = value;
        return;
    }

    // IO REGISTERS
    if (address >= 0xFF00 && address <= 0xFF7F)
    {
        if (address == 0xFF01)
        {
            mem->ioRegs[address] = value;
            return;
        }

        if (address == 0xFF02 && value == 0x81)
        {
            printf("%c", mem->ioRegs[0xFF01]);
            mem->ioRegs[address] = 0;
            return;
        }

        mem->ioRegs[address - 0xFF00] = value;
        return;
    }

    // HIGH RAM
    if (address >= 0xFF80 && address <= 0xFFFE)
    {
        mem->hRam[address - 0xFF80] = value;
        return;
    }

    if (address == 0xFFFF)
    {
        mem->interrupt_enable_register = value;
    }
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