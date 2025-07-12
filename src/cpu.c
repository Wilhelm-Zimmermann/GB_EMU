#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"
#include "./headers/instructions.h"

void initRegisters(Register *reg)
{
    initialize(reg);
}

void cpu_cycle(Register *reg, Memory *mem)
{
    uint8_t opcode = mem->ram[reg->PC];
    switch (opcode & 0xF0)
    {
    case 0x00:
        opcode_x0(reg, mem, opcode);
        break;
    case 0x10:
        opcode_x1(reg, mem, opcode);
        break;
    case 0x20:
        opcode_x2(reg, mem, opcode);
        break;
    case 0x30:
        opcode_x3(reg, mem, opcode);
        break;
    case 0x40:
        opcode_x4(reg, mem, opcode);
        break;
    case 0x50:
        opcode_x5(reg, mem, opcode);
        break;
    case 0x60:
        opcode_x6(reg, mem, opcode);
        break;
    case 0x70:
        opcode_x7(reg, mem, opcode);
        break;
    case 0x80:
        opcode_x8(reg, mem, opcode);
        break;
    case 0x90:
        opcode_x9(reg, mem, opcode);
        break;
    case 0xA0:
        opcode_xA(reg, mem, opcode);
        break;
    case 0xB0:
        opcode_xB(reg, mem, opcode);
        break;
    case 0xC0:
        opcode_xC(reg, mem, opcode);
        break;
    case 0xD0:
        opcode_xD(reg, mem, opcode);
        break;
    case 0xE0:
        opcode_xE(reg, mem, opcode);
        break;
    case 0xF0:
        opcode_xF(reg, mem, opcode);
        break;
    default:
    UNKNOWN_OPCODE:
        // printf("Unknown opcode: %x\n", opcode);
        incrementPC(reg);
        break;
    }
}