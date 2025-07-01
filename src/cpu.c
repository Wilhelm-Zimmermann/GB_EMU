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
#pragma region // TODO: MOve this code later to register.h
void set_ZFlag(Register *reg)
{
    reg->F |= (1 << Z_FLAG_BIT);
}

void set_CFlag(Register *reg)
{
    reg->F |= (1 << C_FLAG_BIT);
}

void set_NFlag(Register *reg)
{
    reg->F |= (1 << N_FLAG_BIT);
}

void set_HFlag(Register *reg)
{
    reg->F |= (1 << H_FLAG_BIT);
}

#pragma endregion

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
    {
        // LD BC, n16
        uint8_t lowByte = memoryRead(mem, reg->PC);
        uint8_t highByte = memoryRead(mem, reg->PC + 1);

        uint16_t value = (highByte << 8) | lowByte;
        reg->BC = value;
        reg->PC += 2;
        break;
    }
    case 0x02:
        // LD [BC], A
        memoryWrite(mem, reg->BC, reg->A);
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
        uint8_t byteValue = memoryRead(mem, reg->PC);
        reg->B = byteValue;
        break;
    case 0x07:
        // RLCA
        uint8_t accMsb = (reg->A >> 7) & 1;
        reg->A = (reg->A << 1) | accMsb;
        reg->F = 0;

        if (accMsb)
        {
            set_CFlag(reg);
        }
        break;
    case 0x08:
    {
        // LD [a16], SP
        uint8_t lowByte = memoryRead(mem, reg->PC);
        uint8_t highByte = memoryRead(mem, reg->PC + 1);
        uint16_t address = (highByte << 8) | lowByte;

        uint16_t spValue = reg->SP;

        memoryWrite(mem, address, spValue & 0xFF);
        memoryWrite(mem, address + 1, spValue >> 8);
        reg->PC += 2;
        break;
    }
    case 0x09:
        // ADD HL, BC
        uint16_t sumValue = reg->HL + reg->BC;
        reg->HL = sumValue;
        break;
    case 0x0A:
    {
        // LD A, [BC]
        uint8_t value = memoryRead(mem, reg->BC);
        reg->A = value;
        break;
    }
    case 0x0B:
        // DEC BC
        reg->BC--;
        break;
    case 0x0C:
        // INC C
        reg->C++;
        break;
    case 0x0D:
        // DEC c
        reg->C--;
    case 0x0E:
    {
        // LD C, n8
        uint8_t value = memoryRead(mem, reg->PC);
        reg->C = value;
        reg->PC++;
        break;
    }
    case 0x0F:
        // RRCA
        uint8_t lsbByte = (reg->A << 7) & (1 << 7);
        reg->A = (reg->A >> 1) | lsbByte;
        reg->F = 0;
        if (lsbByte)
        {
            set_CFlag(reg);
        }
        break;
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
    default:
    UNKNOWN_OPCODE:
        printf("Unknown opcode: %x\n", opcode);
        break;
    }
}