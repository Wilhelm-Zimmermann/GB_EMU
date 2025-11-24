#pragma once
#include <stdint.h>
#include "./register.h"

typedef struct
{
    int romBank0Size;
    int romBankNSize;
    int vRamSize;
    int extRamSize;
    int wramSize;
    int oamSize;
    int ioRegsSize;
    int hRamSize;
    int romSize;

    uint8_t *romBank0;
    uint8_t *romBankN;
    uint8_t *vRam;
    uint8_t *extRam;
    uint8_t *wram;
    uint8_t *oam;
    uint8_t *ioRegs;
    uint8_t *hRam;
    uint8_t *fullRom;
    uint8_t interrupt_enable_register;
} Memory;

void init_memory(Memory *mem);
uint8_t memory_read(Memory *mem, uint16_t address);
uint16_t memory_read_16t(Memory *mem, uint16_t address);
void memory_write(Memory *mem, uint16_t address, uint8_t value);

void stack_push16(Register *reg, Memory *mem, uint16_t value);
uint16_t stack_pop16(Register *reg, Memory *mem);

void free_memory(Memory *mem);