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
        // STOP n8
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
        // LD D, B
        instr_ld8bIn8b(reg, &reg->D, &reg->B);
        break;
    }
    case 0x61:
    {
        // LD D, C
        instr_ld8bIn8b(reg, &reg->D, &reg->C);
        break;
    }
    case 0x62:
    {
        // LD D, D
        instr_ld8bIn8b(reg, &reg->D, &reg->D);
        break;
    }
    case 0x63:
    {
        // LD D, E
        instr_ld8bIn8b(reg, &reg->D, &reg->E);
        break;
    }
    case 0x64:
    {
        // LD D, H
        instr_ld8bIn8b(reg, &reg->D, &reg->H);
        break;
    }
    case 0x65:
    {
        // LD D, L
        instr_ld8bIn8b(reg, &reg->D, &reg->L);
        break;
    }
    case 0x66:
    {
        // LD D, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->D, &memValue);
        break;
    }
    case 0x67:
    {
        // LD D, A
        instr_ld8bIn8b(reg, &reg->D, &reg->A);
        break;
    }
    case 0x68:
    {
        // LD E, B
        instr_ld8bIn8b(reg, &reg->E, &reg->B);
        break;
    }
    case 0x69:
    {
        // LD E, C
        instr_ld8bIn8b(reg, &reg->E, &reg->C);
        break;
    }
    case 0x6A:
    {
        // LD E, D
        instr_ld8bIn8b(reg, &reg->E, &reg->D);
        break;
    }
    case 0x6B:
    {
        // LD E, E
        instr_ld8bIn8b(reg, &reg->E, &reg->E);
        break;
    }
    case 0x6C:
    {
        // LD E, H
        instr_ld8bIn8b(reg, &reg->E, &reg->H);
        break;
    }
    case 0x6D:
    {
        // LD E, L
        instr_ld8bIn8b(reg, &reg->E, &reg->L);
        break;
    }
    case 0x6E:
    {
        // LD E, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_ld8bIn8b(reg, &reg->E, &memValue);
        break;
    }
    case 0x6F:
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
        // opcode_x7(reg, mem, opcode);
        // break;
    case 0x80:
        // opcode_x8(reg, mem, opcode);
        // break;
    case 0x90:
        // opcode_x9(reg, mem, opcode);
        // break;
    case 0xA0:
        // opcode_xA(reg, mem, opcode);
        // break;
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