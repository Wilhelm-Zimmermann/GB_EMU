#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"

void initRegisters(Register *reg)
{
    initialize(reg);
}

// 0x00 to 0x0F Instructions
void opcode_x0(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
        // NOP operation
        incrementPC(reg);
        break;
    case 0x01:
    {
        // LD BC, n16
        uint8_t lowByte = memoryRead(mem, reg->PC + 1);
        uint8_t highByte = memoryRead(mem, reg->PC + 2);

        uint16_t value = (highByte << 8) | lowByte;
        reg->BC = value;
        reg->PC += 3;
        break;
    }
    case 0x02:
        // LD [BC], A
        memoryWrite(mem, reg->BC, reg->A);
        incrementPC(reg);
        break;
    case 0x03:
        // INC BC
        reg->BC++;
        incrementPC(reg);
        break;
    case 0x04:
        // INC B
        reg->B++;
        unset_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->B);
        checkIfHasCarryAndSetH8b(reg, reg->B);
        incrementPC(reg);
        break;
    case 0x05:
        // DEC B
        checkIfHasCarryAndSetH8b(reg, reg->B);
        reg->B--;
        set_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->B);
        incrementPC(reg);
        break;
    case 0x06:
        // LD B, n8
        uint8_t byteValue = memoryRead(mem, reg->PC + 1);
        reg->B = byteValue;
        reg->PC += 2;
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
        incrementPC(reg);
        break;
    case 0x08:
    {
        // LD [a16], SP
        uint8_t lowByte = memoryRead(mem, reg->PC + 1);
        uint8_t highByte = memoryRead(mem, reg->PC + 2);
        uint16_t address = (highByte << 8) | lowByte;

        uint16_t spValue = reg->SP;

        memoryWrite(mem, address, spValue & 0xFF);
        memoryWrite(mem, address + 1, spValue >> 8);
        reg->PC += 3;
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
        incrementPC(reg);
        break;
    case 0x0A:
    {
        // LD A, [BC]
        uint8_t value = memoryRead(mem, reg->BC);
        reg->A = value;
        incrementPC(reg);
        break;
    }
    case 0x0B:
        // DEC BC
        reg->BC--;
        incrementPC(reg);
        break;
    case 0x0C:
        // INC C
        reg->C++;
        unset_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->C);
        checkIfHasCarryAndSetH8b(reg, reg->C);
        incrementPC(reg);
        break;
    case 0x0D:
        // DEC C
        checkIfHasCarryAndSetH8b(reg, reg->C);
        reg->C--;
        set_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->C);
        incrementPC(reg);
        break;
    case 0x0E:
    {
        // LD C, n8
        uint8_t value = memoryRead(mem, reg->PC + 1);
        reg->C = value;
        reg->PC += 2;
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
        incrementPC(reg);
        break;
    default:
        break;
    }
}

void opcode_x1(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x10:
        // STOP n8
        // Implement this after
        incrementPC(reg);
        break;
    case 0x11:
    {
        // LD DE, n16
        uint16_t value = memoryRead16t(mem, reg->PC + 1);
        reg->DE = value;
        reg->PC += 3;
        break;
    }
    case 0x12:
    {
        // LD [DE], A
        memoryWrite(mem, reg->DE, reg->A);
        incrementPC(reg);
        break;
    }
    case 0x13:
    {
        // INC DE
        reg->DE++;
        incrementPC(reg);
        break;
    }
    case 0x14:
    {
        // INC D
        reg->D++;
        unset_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->D);
        checkIfHasCarryAndSetH8b(reg, reg->D);
        incrementPC(reg);
        break;
    }
    case 0x15:
    {
        // DEC D
        checkIfHasCarryAndSetH8b(reg, reg->D);
        reg->D--;
        set_NFlag(reg);
        checkIfOpZeroAndSetZ(reg, reg->D);
        incrementPC(reg);
        break;
    }
    case 0x16:
    {
        // LD D, n8
        uint8_t value = memoryRead(mem, reg->PC + 1);
        reg->D = value;
        reg->PC += 2;
        break;
    }
    case 0x17:
    {
        // RLA
        uint8_t carryBit = (reg->F >> 4) & 1;
        uint8_t accMSB = (reg->A >> 7) & 1;

        reg->A = reg->A << 1;
        reg->A |= carryBit;

        reg->F = 0;

        if (accMSB)
        {
            set_CFlag(reg);
        }
        incrementPC(reg);
        break;
    }
    case 0x18:
    {
        // JR e8
        uint8_t unsignedValue = memoryRead(mem, reg->PC + 1);
        int8_t signedValue = (int8_t) unsignedValue;
        uint16_t newPCAddr = reg->PC + 2 + signedValue;
        reg->PC += newPCAddr;
        break;
    }
    default:
        break;
    }
}

void cpu_cycle(Register *reg, Memory *mem)
{
    uint8_t opcode = mem->ram[reg->PC];
    printf("Getting opcode: %x\n", opcode);

    switch (opcode & 0xF0)
    {
    case 0x00:
        opcode_x0(reg, mem, opcode);
        break;
    case 0x10:
        opcode_x1(reg, mem, opcode);
        break;
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