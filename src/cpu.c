#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"

const int Z_FLAG_BIT = 7;
const int N_FLAG_BIT = 6;
const int H_FLAG_BIT = 5;
const int C_FLAG_BIT = 4;

void initRegisters(Register *reg)
{
    initialize(reg);
}

void set_ZFlag(Register *reg, int value)
{
    if (value == 0)
    {
        reg->F |= (1 << Z_FLAG_BIT);
    }
    else
    {
        reg->F &= ~(1 << Z_FLAG_BIT);
    }
}

void set_CFlag8Bit(Register *reg, uint8_t value)
{
    if (value > 0xFF)
    {
        reg->F |= (1 << C_FLAG_BIT);
    }
    else
    {
        reg->F &= ~(1 << C_FLAG_BIT);
    }
}

void set_CFlag16Bit(Register *reg, uint16_t value)
{
    if (value > 0xFFFF)
    {
        reg->F |= (1 << C_FLAG_BIT);
    }
    else
    {
        reg->F &= ~(1 << C_FLAG_BIT);
    }
}

void set_CFlag16BitSubtr(Register *reg, int value)
{
    if (value < 0)
    {
        reg->F |= (1 << C_FLAG_BIT);
    }
    else
    {
        reg->F &= ~(1 << C_FLAG_BIT);
    }
}

// TODO: Implement 1 bit validation of C flag
void set_CFlagBitShift(Register *reg)
{
    reg->F |= (1 << C_FLAG_BIT);
}

// TODO: Implement NH flags later
// void set_NHFlags()
// {

// }

// TODO: Review opcodes to implement the flags logic
// Flags order -> Z N H C
void opcode_x0(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
        // NOP operation
        break;
    case 0x01:
        // LD BC, n16
        printf("Loading 16 bit value to BC\n");
        uint8_t lowByte = readByte(mem, reg->PC);
        uint8_t highByte = readByte(mem, reg->PC + 1);

        uint16_t value = (highByte << 8) | lowByte;
        reg->BC = value;
        reg->PC += 2;
        break;
    case 0x02:
        // LD [BC], A
        writeByte(mem, reg->BC, reg->A);
        break;
    case 0x03:
        // INC BC
        reg->BC++;
        break;
    case 0x04:
        // INC B
        reg->B++;
        break;
    case 0x05:
        // DEC B
        reg->B--;
        break;
    case 0x06:
        // LD B, n8
        uint8_t byteValue = readByte(mem, reg->PC);
        reg->B = byteValue;
        break;
    case 0x07:
        // RLCA
        uint8_t accMsb = (reg->A >> 7) & 1;
        reg->A = (reg->A << 1) | accMsb;
        reg->F = 0;

        if (accMsb)
        {
            set_CFlagBitShift(reg);
        }
        break;

    case 0x08:
     // LD [a16], SP
    default:
        break;
    }
}

void cpu_cycle(Register *reg, Memory *mem)
{
    uint8_t opcode = mem->ram[reg->PC];
    printf("Getting opcode: %x\n", opcode);
    reg->PC += 1;

    switch (opcode & 0xF0)
    {
    case 0x00:
        opcode_x0(reg, mem, opcode);
        break;
    case 0xCE:
        printf("Adding next 8 bit value to Accumulator\n");
        reg->A = mem->ram[reg->PC] + reg->A;
        break;
    default:
    UNKNOWN_OPCODE:
        printf("Unknown opcode: %x\n", opcode);
        break;
    }
}