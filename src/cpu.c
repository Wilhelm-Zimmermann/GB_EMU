#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"
#include "./headers/instructions.h"
#include "./headers/logger.h"

#define DEBUG

void init_registers(Register *reg)
{
    initialize(reg);
}

int handle_interrupts(Register *reg, Memory *mem)
{

    uint8_t IE = memory_read(mem, 0xFFFF);
    uint8_t IF = memory_read(mem, 0xFF0F);

    uint8_t fired = IE & IF;

    if (fired > 0)
    {

        if (reg->halted)
        {
            reg->halted = 0;
        }

        if (reg->IME == 0)
        {
            return 0;
        }

        uint8_t interrupt_bit = 0;
        uint16_t vector_addr = 0x0000;

        if (fired & 0x01)
        {
            interrupt_bit = 0;
            vector_addr = 0x0040;
        }

        else if (fired & 0x02)
        {
            interrupt_bit = 1;
            vector_addr = 0x0048;
        }

        else if (fired & 0x04)
        {
            interrupt_bit = 2;
            vector_addr = 0x0050;
        }

        else if (fired & 0x08)
        {
            interrupt_bit = 3;
            vector_addr = 0x0058;
        }

        else if (fired & 0x10)
        {
            interrupt_bit = 4;
            vector_addr = 0x0060;
        }

        reg->IME = 0;

        uint8_t current_IF = memory_read(mem, 0xFF0F);
        memory_write(mem, 0xFF0F, current_IF & ~(1 << interrupt_bit));

        stack_push16(reg, mem, reg->PC);

        reg->PC = vector_addr;

        return 20;
    }

    return 0;
}

uint8_t cpu_cycle(Register *reg, Memory *mem)
{
    int interrupt_cycles = handle_interrupts(reg, mem);

    if (interrupt_cycles > 0)
    {
        return interrupt_cycles;
    }

    if (reg->halted)
    {
        return 4;
    }

    uint8_t opcode = memory_read(mem, reg->PC);

#ifdef DEBUG
    write_cpu_logs(reg, mem, reg->PC, opcode);
#endif

    int was_EI = (opcode == 0xFB);
    if (reg->ime_scheduled)
    {
        if (!was_EI)
        {
            reg->IME = 1;
            reg->ime_scheduled = 0;
        }
    }
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
        increment_pc(reg);
        return 4;
        break;
    }

    return 4;
}