#include <stdio.h>
#include "./headers/cpu.h"
#include "./headers/register.h"
#include "./headers/memory.h"
#include "./headers/opcodes.h"

void initRegisters(Register *reg)
{
    initialize(reg);
}

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
        instr_ldNxt16bAddrInReg(reg, mem, &reg->BC);
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
        instr_inc8b(reg, &reg->B);
        break;
    case 0x05:
        // DEC B
        instr_dec8b(reg, &reg->B);
        break;
    case 0x06:
        // LD B, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->B);
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
        instr_add16b(reg, &reg->HL, reg->BC);
        break;
    case 0x0A:
    {
        // LD A, [BC]
        instr_ldAddr8bInReg(reg, mem, reg->BC, &reg->A);
        break;
    }
    case 0x0B:
        // DEC BC
        reg->BC--;
        incrementPC(reg);
        break;
    case 0x0C:
        // INC C
        instr_inc8b(reg, &reg->C);
        break;
    case 0x0D:
        // DEC C
        instr_dec8b(reg, &reg->C);
        break;
    case 0x0E:
    {
        // LD C, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->C);
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
        incrementPC(reg);
        break;
    }
}

void opcode_x1(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x10:
        // STOP n8 - IDLE EMU
        // Implement this after
        incrementPC(reg);
        break;
    case 0x11:
    {
        // LD DE, n16
        instr_ldNxt16bAddrInReg(reg, mem, &reg->DE);
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
        instr_inc8b(reg, &reg->D);
        break;
    }
    case 0x15:
    {
        // DEC D
        instr_dec8b(reg, &reg->D);
        break;
    }
    case 0x16:
    {
        // LD D, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->D);
        break;
    }
    case 0x17:
    {
        // RLA
        uint8_t carryBit = get_CFlag(reg) & 1;
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
        int8_t signedValue = (int8_t)unsignedValue;
        uint16_t newPCAddr = reg->PC + 2 + signedValue;
        reg->PC = newPCAddr;
        break;
    }
    case 0x19:
    {
        // ADD HL, DE
        instr_add16b(reg, &reg->HL, reg->DE);
        break;
    }
    case 0x1A:
    {
        // LD A, [DE]
        instr_ldAddr8bInReg(reg, mem, reg->DE, &reg->A);
        break;
    }
    case 0x1B:
    {
        // DEC DE
        reg->DE--;
        incrementPC(reg);
        break;
    }
    case 0x1C:
    {
        // INC E
        instr_inc8b(reg, &reg->E);
        break;
    }
    case 0x1D:
    {
        // DEC E
        instr_dec8b(reg, &reg->E);
        break;
    }
    case 0x1E:
    {
        // LD E, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->E);
        break;
    }
    case 0x1F:
    {
        // RRA
        uint8_t accLSB = reg->A & 1;
        uint8_t carryBit = get_CFlag(reg) & 1;
        reg->A = reg->A >> 1;
        reg->A |= (carryBit << 7);
        reg->F = 0;

        if (accLSB)
        {
            set_CFlag(reg);
        }

        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x2(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x20:
    {
        // JR NZ, e8
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 0)
        {
            uint8_t unsignedValue = memoryRead(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
        }
        else
        {
            reg->PC += 2;
        }
        break;
    }
    case 0x21:
    {
        // LD HL, n16
        instr_ldNxt16bAddrInReg(reg, mem, &reg->HL);
        break;
    }
    case 0x22:
    {
        // LD [HL+], A
        memoryWrite(mem, reg->HL, reg->A);
        reg->HL++;
        incrementPC(reg);
        break;
    }
    case 0x23:
    {
        // INC HL
        reg->HL++;
        incrementPC(reg);
        break;
    }
    case 0x24:
    {
        // INC H
        instr_inc8b(reg, &reg->H);
        break;
    }
    case 0x25:
    {
        // DEC H
        instr_dec8b(reg, &reg->H);
        break;
    }
    case 0x26:
    {
        // LD H, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->H);
        break;
    }
    case 0x27:
    {
        // DAA
        uint8_t a = reg->A;
        uint8_t nFlagValue = get_NFlag(reg);
        uint8_t hFlagValue = get_HFlag(reg);
        uint8_t cFlagValue = get_CFlag(reg);
        if (nFlagValue == 0)
        {
            if (cFlagValue == 1 || a > 0x99)
            {
                a += 0x60;
                set_CFlag(reg);
            }
            if (hFlagValue == 1 || (a & 0x0F) > 0x09)
            {
                a += 0x06;
            }
        }
        else
        {
            if (cFlagValue == 1)
            {
                a -= 0x60;
            }
            if (hFlagValue == 1)
            {
                a -= 0x06;
            }
        }
        reg->A = a;
        checkIfOpZeroAndSetZ(reg, reg->A);
        unset_HFlag(reg);
        if (nFlagValue == 0 && get_CFlag(reg) != 1)
        {
            unset_CFlag(reg);
        }
        break;
    }
    case 0x28:
    {
        // JR Z, e8
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 1)
        {
            uint8_t unsignedValue = memoryRead(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
        }
        else
        {
            reg->PC += 2;
        }
        break;
    }
    case 0x29:
    {
        // ADD HL, HL
        instr_add16b(reg, &reg->HL, reg->HL);
        break;
    }
    case 0x2A:
    {
        // LD A, [HL+]
        instr_ldAddr8bInReg(reg, mem, reg->HL, &reg->A);
        reg->HL++;
        break;
    }
    case 0x2B:
    {
        // DEC HL
        reg->HL--;
        break;
    }
    case 0x2C:
    {
        // INC L
        instr_inc8b(reg, &reg->L);
        break;
    }
    case 0x2D:
    {
        // DEC L
        instr_dec8b(reg, &reg->L);
        break;
    }
    case 0x2E:
    {
        // LD L, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->L);
        break;
    }
    case 0x2F:
    {
        // CPL
        reg->A = ~reg->A;
        set_NFlag(reg);
        set_HFlag(reg);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x3(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x30:
    {
        // JR NC, e8
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 0)
        {
            uint8_t unsignedValue = memoryRead(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
        }
        else
        {
            reg->PC += 2;
        }
        break;
    }
    case 0x31:
    {
        // LD SP, n16
        instr_ldNxt16bAddrInReg(reg, mem, &reg->SP);
        break;
    }
    case 0x32:
    {
        // LD [HL-], A
        memoryWrite(mem, reg->HL, reg->A);
        reg->HL--;
        incrementPC(reg);
        break;
    }
    case 0x33:
    {
        // INC SP
        reg->SP++;
        incrementPC(reg);
        break;
    }
    case 0x34:
    {
        // INC [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_inc8b(reg, &memValue);
        break;
    }
    case 0x35:
    {
        // DEC [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_dec8b(reg, &memValue);
        break;
    }
    case 0x36:
    {
        // LD [HL], n8
        uint8_t memValue = memoryRead(mem, reg->PC + 1);
        memoryWrite(mem, reg->HL, memValue);
        reg->PC += 2;
        break;
    }
    case 0x37:
    {
        // SCF
        set_CFlag(reg);
        unset_HFlag(reg);
        unset_NFlag(reg);
        incrementPC(reg);
    }
    case 0x38:
    {
        // JR C, e8
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 1)
        {
            uint8_t unsignedValue = memoryRead(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
        }
        else
        {
            reg->PC += 2;
        }
        break;
    }
    case 0x39:
    {
        // ADD HL, SP
        instr_add16b(reg, &reg->HL, reg->SP);
        break;
    }
    case 0x3A:
    {
        // LD A, [HL-]
        instr_ldAddr8bInReg(reg, mem, reg->HL, &reg->A);
        reg->HL--;
        break;
    }
    case 0x3B:
    {
        // DEC HL
        reg->SP--;
        incrementPC(reg);
        break;
    }
    case 0x3C:
    {
        // INC A
        instr_inc8b(reg, &reg->A);
        break;
    }
    case 0x3D:
    {
        // INC A
        instr_dec8b(reg, &reg->A);
        break;
    }
    case 0x3E:
    {
        // LD A, n8
        instr_ldNxt8bAddrInReg(reg, mem, &reg->A);
        break;
    }
    case 0x3F:
    {
        // CCF
        unset_HFlag(reg);
        unset_NFlag(reg);

        if (get_CFlag(reg) == 1)
        {
            unset_CFlag(reg);
        }
        else
        {
            set_CFlag(reg);
        }
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x4(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x40:
    {
        // LD B, B
        instr_ld8bIn8b(reg, &reg->B, &reg->B);
        break;
    }
    case 0x41:
    {
        // LD B, C
        instr_ld8bIn8b(reg, &reg->B, &reg->C);
        break;
    }
    case 0x42:
    {
        // LD B, D
        instr_ld8bIn8b(reg, &reg->B, &reg->D);
        break;
    }
    case 0x43:
    {
        // LD B, E
        instr_ld8bIn8b(reg, &reg->B, &reg->E);
        break;
    }
    case 0x44:
    {
        // LD B, H
        instr_ld8bIn8b(reg, &reg->B, &reg->H);
        break;
    }
    case 0x45:
    {
        // LD B, L
        instr_ld8bIn8b(reg, &reg->B, &reg->L);
        break;
    }
    case 0x46:
    {
        // LD B, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->B, &memValue);
        break;
    }
    case 0x47:
    {
        // LD B, A
        instr_ld8bIn8b(reg, &reg->B, &reg->A);
        break;
    }
    case 0x48:
    {
        // LD C, B
        instr_ld8bIn8b(reg, &reg->C, &reg->B);
        break;
    }
    case 0x49:
    {
        // LD C, C
        instr_ld8bIn8b(reg, &reg->C, &reg->C);
        break;
    }
    case 0x4A:
    {
        // LD C, D
        instr_ld8bIn8b(reg, &reg->C, &reg->D);
        break;
    }
    case 0x4B:
    {
        // LD C, E
        instr_ld8bIn8b(reg, &reg->C, &reg->E);
        break;
    }
    case 0x4C:
    {
        // LD C, H
        instr_ld8bIn8b(reg, &reg->C, &reg->H);
        break;
    }
    case 0x4D:
    {
        // LD C, L
        instr_ld8bIn8b(reg, &reg->C, &reg->L);
        break;
    }
    case 0x4E:
    {
        // LD C, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->C, &memValue);
        break;
    }
    case 0x4F:
    {
        // LD C, A
        instr_ld8bIn8b(reg, &reg->C, &reg->A);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x5(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x50:
    {
        // LD D, B
        instr_ld8bIn8b(reg, &reg->D, &reg->B);
        break;
    }
    case 0x51:
    {
        // LD D, C
        instr_ld8bIn8b(reg, &reg->D, &reg->C);
        break;
    }
    case 0x52:
    {
        // LD D, D
        instr_ld8bIn8b(reg, &reg->D, &reg->D);
        break;
    }
    case 0x53:
    {
        // LD D, E
        instr_ld8bIn8b(reg, &reg->D, &reg->E);
        break;
    }
    case 0x54:
    {
        // LD D, H
        instr_ld8bIn8b(reg, &reg->D, &reg->H);
        break;
    }
    case 0x55:
    {
        // LD D, L
        instr_ld8bIn8b(reg, &reg->D, &reg->L);
        break;
    }
    case 0x56:
    {
        // LD D, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->D, &memValue);
        break;
    }
    case 0x57:
    {
        // LD D, A
        instr_ld8bIn8b(reg, &reg->D, &reg->A);
        break;
    }
    case 0x58:
    {
        // LD E, B
        instr_ld8bIn8b(reg, &reg->E, &reg->B);
        break;
    }
    case 0x59:
    {
        // LD E, C
        instr_ld8bIn8b(reg, &reg->E, &reg->C);
        break;
    }
    case 0x5A:
    {
        // LD E, D
        instr_ld8bIn8b(reg, &reg->E, &reg->D);
        break;
    }
    case 0x5B:
    {
        // LD E, E
        instr_ld8bIn8b(reg, &reg->E, &reg->E);
        break;
    }
    case 0x5C:
    {
        // LD E, H
        instr_ld8bIn8b(reg, &reg->E, &reg->H);
        break;
    }
    case 0x5D:
    {
        // LD E, L
        instr_ld8bIn8b(reg, &reg->E, &reg->L);
        break;
    }
    case 0x5E:
    {
        // LD E, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->E, &memValue);
        break;
    }
    case 0x5F:
    {
        // LD E, A
        instr_ld8bIn8b(reg, &reg->E, &reg->A);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x6(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x60:
    {
        // LD H, B
        instr_ld8bIn8b(reg, &reg->H, &reg->B);
        break;
    }
    case 0x61:
    {
        // LD H, C
        instr_ld8bIn8b(reg, &reg->H, &reg->C);
        break;
    }
    case 0x62:
    {
        // LD H, D
        instr_ld8bIn8b(reg, &reg->H, &reg->D);
        break;
    }
    case 0x63:
    {
        // LD H, E
        instr_ld8bIn8b(reg, &reg->H, &reg->E);
        break;
    }
    case 0x64:
    {
        // LD H, H
        instr_ld8bIn8b(reg, &reg->H, &reg->H);
        break;
    }
    case 0x65:
    {
        // LD H, L
        instr_ld8bIn8b(reg, &reg->H, &reg->L);
        break;
    }
    case 0x66:
    {
        // LD H, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->H, &memValue);
        break;
    }
    case 0x67:
    {
        // LD H, A
        instr_ld8bIn8b(reg, &reg->H, &reg->A);
        break;
    }
    case 0x68:
    {
        // LD L, B
        instr_ld8bIn8b(reg, &reg->L, &reg->B);
        break;
    }
    case 0x69:
    {
        // LD L, C
        instr_ld8bIn8b(reg, &reg->L, &reg->C);
        break;
    }
    case 0x6A:
    {
        // LD L, D
        instr_ld8bIn8b(reg, &reg->L, &reg->D);
        break;
    }
    case 0x6B:
    {
        // LD L, E
        instr_ld8bIn8b(reg, &reg->L, &reg->E);
        break;
    }
    case 0x6C:
    {
        // LD L, H
        instr_ld8bIn8b(reg, &reg->L, &reg->H);
        break;
    }
    case 0x6D:
    {
        // LD L, L
        instr_ld8bIn8b(reg, &reg->L, &reg->L);
        break;
    }
    case 0x6E:
    {
        // LD L, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->L, &memValue);
        break;
    }
    case 0x6F:
    {
        // LD L, A
        instr_ld8bIn8b(reg, &reg->L, &reg->A);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x7(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x70:
    {
        // LD [HL], B
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->B);
        break;
    }
    case 0x71:
    {
        // LD [HL], C
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->C);
        break;
    }
    case 0x72:
    {
        // LD [HL], D
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->D);
        break;
    }
    case 0x73:
    {
        // LD [HL], E
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->E);
        break;
    }
    case 0x74:
    {
        // LD [HL], H
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->H);
        break;
    }
    case 0x75:
    {
        // LD [HL], L
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->L);
        break;
    }
    case 0x76:
    {
        // HALT - Only CPU STOPS - IDLE
        incrementPC(reg);
        break;
    }
    case 0x77:
    {
        // LD [HL], A
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &memValue, &reg->A);
        break;
    }
    case 0x78:
    {
        // LD A, B
        instr_ld8bIn8b(reg, &reg->A, &reg->B);
        break;
    }
    case 0x79:
    {
        // LD A, C
        instr_ld8bIn8b(reg, &reg->A, &reg->C);
        break;
    }
    case 0x7A:
    {
        // LD A, D
        instr_ld8bIn8b(reg, &reg->A, &reg->D);
        break;
    }
    case 0x7B:
    {
        // LD A, E
        instr_ld8bIn8b(reg, &reg->A, &reg->E);
        break;
    }
    case 0x7C:
    {
        // LD A, H
        instr_ld8bIn8b(reg, &reg->A, &reg->H);
        break;
    }
    case 0x7D:
    {
        // LD A, L
        instr_ld8bIn8b(reg, &reg->A, &reg->L);
        break;
    }
    case 0x7E:
    {
        // LD A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->A, &memValue);
        break;
    }
    case 0x7F:
    {
        // LD A, A
        instr_ld8bIn8b(reg, &reg->A, &reg->A);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x8(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x80:
    {
        // ADD A, B
        instr_add8b(reg, &reg->A, reg->B);
        break;
    }
    case 0x81:
    {
        // ADD A, C
        instr_add8b(reg, &reg->A, reg->C);
        break;
    }
    case 0x82:
    {
        // ADD A, D
        instr_add8b(reg, &reg->A, reg->D);
        break;
    }
    case 0x83:
    {
        // ADD A, E
        instr_add8b(reg, &reg->A, reg->E);
        break;
    }
    case 0x84:
    {
        // ADD A, H
        instr_add8b(reg, &reg->A, reg->H);
        break;
    }
    case 0x85:
    {
        // ADD A, L
        instr_add8b(reg, &reg->A, reg->L);
        break;
    }
    case 0x86:
    {
        // ADD A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_add8b(reg, &reg->A, memValue);
        break;
    }
    case 0x87:
    {
        // ADD A, A
        instr_add8b(reg, &reg->A, reg->A);
        break;
    }
    case 0x88:
    {
        // ADC A, B
        instr_add8bWithCarry(reg, &reg->A, reg->B);
        break;
    }
    case 0x89:
    {
        // ADC A, C
        instr_add8bWithCarry(reg, &reg->A, reg->C);
        break;
    }
    case 0x8A:
    {
        // ADC A, D
        instr_add8bWithCarry(reg, &reg->A, reg->D);
        break;
    }
    case 0x8B:
    {
        // ADC A, E
        instr_add8bWithCarry(reg, &reg->A, reg->E);
        break;
    }
    case 0x8C:
    {
        // ADC A, H
        instr_add8bWithCarry(reg, &reg->A, reg->H);
        break;
    }
    case 0x8D:
    {
        // ADC A, L
        instr_add8bWithCarry(reg, &reg->A, reg->L);
        break;
    }
    case 0x8E:
    {
        // ADC A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_add8bWithCarry(reg, &reg->A, memValue);
        break;
    }
    case 0x8F:
    {
        // ADC A, A
        instr_add8bWithCarry(reg, &reg->A, reg->A);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_x9(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x90:
    {
        // SUB A, B
        instr_sub8b(reg, &reg->A, reg->B);
        break;
    }
    case 0x91:
    {
        // SUB A, C
        instr_sub8b(reg, &reg->A, reg->C);
        break;
    }
    case 0x92:
    {
        // SUB A, D
        instr_sub8b(reg, &reg->A, reg->D);
        break;
    }
    case 0x93:
    {
        // SUB A, E
        instr_sub8b(reg, &reg->A, reg->E);
        break;
    }
    case 0x94:
    {
        // SUB A, H
        instr_sub8b(reg, &reg->A, reg->H);
        break;
    }
    case 0x95:
    {
        // SUB A, L
        instr_sub8b(reg, &reg->A, reg->L);
        break;
    }
    case 0x96:
    {
        // SUB A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_sub8b(reg, &reg->A, memValue);
        break;
    }
    case 0x97:
    {
        // SUB A, A
        instr_sub8b(reg, &reg->A, reg->A);
        set_ZFlag(reg);
        set_NFlag(reg);
        unset_HFlag(reg);
        unset_CFlag(reg);
        break;
    }
    case 0x98:
    {
        // SBC A, B
        instr_sub8bWithCarry(reg, &reg->A, reg->B);
        break;
    }
    case 0x99:
    {
        // SBC A, C
        instr_sub8bWithCarry(reg, &reg->A, reg->C);
        break;
    }
    case 0x9A:
    {
        // SBC A, D
        instr_sub8bWithCarry(reg, &reg->A, reg->D);
        break;
    }
    case 0x9B:
    {
        // SBC A, E
        instr_sub8bWithCarry(reg, &reg->A, reg->E);
        break;
    }
    case 0x9C:
    {
        // SBC A, H
        instr_sub8bWithCarry(reg, &reg->A, reg->H);
        break;
    }
    case 0x9D:
    {
        // SBC A, L
        instr_sub8bWithCarry(reg, &reg->A, reg->L);
        break;
    }
    case 0x9E:
    {
        // SBC A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_sub8bWithCarry(reg, &reg->A, memValue);
        break;
    }
    case 0x9F:
    {
        // SBC A, A
        uint8_t originalCarry = get_CFlag(reg);
        instr_sub8bWithCarry(reg, &reg->A, reg->A);
        if (originalCarry == 1)
        {
            set_CFlag(reg);
        }
        else
        {
            unset_CFlag(reg);
        }
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_xA(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xA0:
    {
        // AND A, B
        instr_and(reg, &reg->A, reg->B);
        break;
    }
    case 0xA1:
    {
        // AND A, C
        instr_and(reg, &reg->A, reg->C);
        break;
    }
    case 0xA2:
    {
        // AND A, D
        instr_and(reg, &reg->A, reg->D);
        break;
    }
    case 0xA3:
    {
        // AND A, E
        instr_and(reg, &reg->A, reg->E);
        break;
    }
    case 0xA4:
    {
        // AND A, H
        instr_and(reg, &reg->A, reg->H);
        break;
    }
    case 0xA5:
    {
        // AND A, L
        instr_and(reg, &reg->A, reg->L);
        break;
    }
    case 0xA6:
    {
        // AND A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_and(reg, &reg->A, memValue);
        break;
    }
    case 0xA7:
    {
        // AND A, A
        instr_and(reg, &reg->A, reg->A);
        break;
    }
    case 0xA8:
    {
        // XOR A, B
        instr_xor(reg, &reg->A, reg->B);
        break;
    }
    case 0xA9:
    {
        // XOR A, C
        instr_xor(reg, &reg->A, reg->C);
        break;
    }
    case 0xAA:
    {
        // XOR A, D
        instr_xor(reg, &reg->A, reg->D);
        break;
    }
    case 0xAB:
    {
        // XOR A, E
        instr_xor(reg, &reg->A, reg->E);
        break;
    }
    case 0xAC:
    {
        // XOR A, H
        instr_xor(reg, &reg->A, reg->H);
        break;
    }
    case 0xAD:
    {
        // XOR A, L
        instr_xor(reg, &reg->A, reg->L);
        break;
    }
    case 0xAE:
    {
        // XOR A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_xor(reg, &reg->A, memValue);
        break;
    }
    case 0xAF:
    {
        // XOR A, A
        instr_xor(reg, &reg->A, reg->A);
        set_ZFlag(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void cpu_cycle(Register *reg, Memory *mem)
{
    uint8_t opcode = mem->ram[reg->PC];
    // printf("Getting opcode: %x\n", opcode);

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
        // opcode_xB(reg, mem, opcode);
        // break;
    case 0xC0:
        // opcode_xC(reg, mem, opcode);
        // break;
    case 0xD0:
        // opcode_xD(reg, mem, opcode);
        // break;
    case 0xE0:
        // opcode_xE(reg, mem, opcode);
        // break;
    case 0xF0:
        // opcode_xF(reg, mem, opcode);
        // break;
    default:
    UNKNOWN_OPCODE:
        // printf("Unknown opcode: %x\n", opcode);
        incrementPC(reg);
        break;
    }
}