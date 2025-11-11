#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"
#include "./headers/instructions.h"
#include "./headers/logger.h"

#define DEBUG

void initRegisters(Register *reg)
{
    initialize(reg);
}

uint8_t cpu_cycle(Register *reg, Memory *mem)
{
    uint8_t opcode = memoryRead(mem, reg->PC);

#ifdef DEBUG
    writeCPULogs(reg, mem, reg->PC, opcode);
#endif
    switch (opcode & 0xF0)
    {
    case 0x00:
        return opcode_x0(reg, mem, opcode);
        break;
    case 0x10:
        return opcode_x1(reg, mem, opcode);
        break;
    case 0x20:
        return opcode_x2(reg, mem, opcode);
        break;
    case 0x30:
        return opcode_x3(reg, mem, opcode);
        break;
    case 0x40:
        return opcode_x4(reg, mem, opcode);
        break;
    case 0x50:
        return opcode_x5(reg, mem, opcode);
        break;
    case 0x60:
        return opcode_x6(reg, mem, opcode);
        break;
    case 0x70:
        return opcode_x7(reg, mem, opcode);
        break;
    case 0x80:
        return opcode_x8(reg, mem, opcode);
        break;
    case 0x90:
        return opcode_x9(reg, mem, opcode);
        break;
    case 0xA0:
        return opcode_xA(reg, mem, opcode);
        break;
    case 0xB0:
        return opcode_xB(reg, mem, opcode);
        break;
    case 0xC0:
        return opcode_xC(reg, mem, opcode);
        break;
    case 0xD0:
        return opcode_xD(reg, mem, opcode);
        break;
    case 0xE0:
        return opcode_xE(reg, mem, opcode);
        break;
    case 0xF0:
        return opcode_xF(reg, mem, opcode);
        break;
    default:
    UNKNOWN_OPCODE:
        // printf("Unknown opcode: 0x%02X at PC=0%04X\n", opcode, reg->PC);
        incrementPC(reg);
        return 4;
        break;
    }

    return 4;
}