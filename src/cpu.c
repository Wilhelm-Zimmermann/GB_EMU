#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"

void initRegisters(Register *reg)
{
    initialize(reg);
}

// 0x00 to 0x0F Instructions
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
        unset_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->B);
        checkIfHasCarryAndSetH8b(reg, reg->B);
        break;
    case 0x05:
        // DEC B
        reg->B--;
        set_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->B);
        checkIfHasCarryAndSetH8b(reg, reg->B);
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
        uint32_t sumValue = (uint32_t)reg->HL + (uint32_t)reg->BC;
        unset_NFlag(reg);
        if (((reg->HL & 0x0FFF) + (reg->BC & 0x0FFF)) > 0x0FFF)
        {
            set_HFlag(reg);
        }
        else
        {
            unset_HFlag(reg);
        }

        setCFlagIfAddOpGtThanFFFF(reg, sumValue);
        reg->HL = (uint16_t)sumValue;
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
        unset_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->C);
        checkIfHasCarryAndSetH8b(reg, reg->C);
        break;
    case 0x0D:
        // DEC c
        reg->C--;
        set_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->C);
        checkIfHasCarryAndSetH8b(reg, reg->C);
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
    case 0x10:
    case 0x20:
    case 0x30:
    case 0x40:
    case 0x50:
    case 0x60:
    case 0x70:
    case 0x80:
    case 0x90:
    case 0xA0:
    case 0xB0:
    case 0xC0:
    case 0xD0:
    case 0xE0:
    case 0xF0:
    default:
    UNKNOWN_OPCODE:
        printf("Unknown opcode: %x\n", opcode);
        break;
    }
}