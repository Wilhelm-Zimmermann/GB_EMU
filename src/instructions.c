#include "./headers/instructions.h"
#include "./headers/opcodes.h"

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

void opcode_xB(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xB0:
    {
        // OR A, B
        instr_or(reg, &reg->A, reg->B);
        break;
    }
    case 0xB1:
    {
        // OR A, C
        instr_or(reg, &reg->A, reg->C);
        break;
    }
    case 0xB2:
    {
        // OR A, D
        instr_or(reg, &reg->A, reg->D);
        break;
    }
    case 0xB3:
    {
        // OR A, E
        instr_or(reg, &reg->A, reg->E);
        break;
    }
    case 0xB4:
    {
        // OR A, H
        instr_or(reg, &reg->A, reg->H);
        break;
    }
    case 0xB5:
    {
        // OR A, L
        instr_or(reg, &reg->A, reg->L);
        break;
    }
    case 0xB6:
    {
        // OR A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_or(reg, &reg->A, memValue);
        break;
    }
    case 0xB7:
    {
        // OR A, A
        instr_or(reg, &reg->A, reg->A);
        break;
    }
    case 0xB8:
    {
        // CP A, B
        instr_cp8b(reg, &reg->A, reg->B);
        break;
    }
    case 0xB9:
    {
        // CP A, C
        instr_cp8b(reg, &reg->A, reg->C);
        break;
    }
    case 0xBA:
    {
        // CP A, D
        instr_cp8b(reg, &reg->A, reg->D);
        break;
    }
    case 0xBB:
    {
        // CP A, E
        instr_cp8b(reg, &reg->A, reg->E);
        break;
    }
    case 0xBC:
    {
        // CP A, H
        instr_cp8b(reg, &reg->A, reg->H);
        break;
    }
    case 0xBD:
    {
        // CP A, L
        instr_cp8b(reg, &reg->A, reg->L);
        break;
    }
    case 0xBE:
    {
        // CP A, [HL]
        uint8_t memValue = memoryRead(mem, reg->HL);
        instr_cp8b(reg, &reg->A, memValue);
        break;
    }
    case 0xBF:
    {
        // CP A, A
        instr_cp8b(reg, &reg->A, reg->A);
        set_ZFlag(reg);
        set_NFlag(reg);
        unset_HFlag(reg);
        unset_CFlag(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_xC(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xC0:
    {
        // RET NZ
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 0)
        {
            instr_ret(reg, mem);
        }
        else
        {
            incrementPC(reg);
        }
        break;
    }
    case 0xC1:
    {
        // POP BC
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->BC = stackValue;
        incrementPC(reg);
        break;
    }
    case 0xC2:
    {
        // JP NZ, a16
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 0)
        {
            instr_jpNxt16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xC3:
    {
        // JP a16
        instr_jpNxt16(reg, mem);
        break;
    }
    case 0xC4:
    {
        // CALL NZ, a16
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 0)
        {
            instr_callAddr16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xC5:
    {
        // PUSH BC
        stack_push16(reg, mem, reg->BC);
        incrementPC(reg);
        break;
    }
    case 0xC6:
    {
        // ADD A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_add8b(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xC7:
    {
        // RST $00
        instr_rst(reg, mem, 0x000);
        break;
    }
    case 0xC8:
    {
        // RET Z
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 1)
        {
            instr_ret(reg, mem);
        }
        else
        {
            incrementPC(reg);
        }
        break;
    }
    case 0xC9:
    {
        // RET
        instr_ret(reg, mem);
        break;
    }
    case 0xCA:
    {
        // JP Z, a16
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 1)
        {
            instr_jpNxt16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xCB:
    {
        // PREFIX -- TODO: this is more 256 instructions, implement this later
        incrementPC(reg);
        break;
    }
    case 0xCC:
    {
        // CALL Z, a16
        uint8_t zFlagValue = get_ZFlag(reg);
        if (zFlagValue == 1)
        {
            instr_callAddr16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xCD:
    {
        // CALL a16
        instr_callAddr16(reg, mem);
        break;
    }
    case 0xCE:
    {
        // ADC A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_add8bWithCarry(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xCF:
    {
        // RST $08
        instr_rst(reg, mem, 0x0008);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_xD(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xD0:
    {
        // RET NC
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 0)
        {
            instr_ret(reg, mem);
        }
        else
        {
            incrementPC(reg);
        }
        break;
    }
    case 0xD1:
    {
        // POP DE
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->DE = stackValue;
        incrementPC(reg);
        break;
    }
    case 0xD2:
    {
        // JP NC, a16
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 0)
        {
            instr_jpNxt16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xD3:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xD4:
    {
        // CALL NC, a16
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 0)
        {
            instr_callAddr16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xD5:
    {
        // PUSH DE
        stack_push16(reg, mem, reg->DE);
        incrementPC(reg);
        break;
    }
    case 0xD6:
    {
        // SUB A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_sub8b(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xD7:
    {
        // RST $10
        instr_rst(reg, mem, 0x0010);
        break;
    }
    case 0xD8:
    {
        // RET C
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 1)
        {
            instr_ret(reg, mem);
        }
        else
        {
            incrementPC(reg);
        }
        break;
    }
    case 0xD9:
    {
        // RETI -- TODO: revise when implementing the Interrupt
        instr_ret(reg, mem);
        incrementPC(reg);
        break;
    }
    case 0xDA:
    {
        // JP C, a16
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 1)
        {
            instr_ret(reg, mem);
        }
        else
        {
            incrementPC(reg);
        }
        break;
    }
    case 0xDB:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xDC:
    {
        // CALL C, a16
        uint8_t cFlagValue = get_CFlag(reg);
        if (cFlagValue == 1)
        {
            instr_callAddr16(reg, mem);
        }
        else
        {
            reg->PC += 3;
        }
        break;
    }
    case 0xDD:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xDE:
    {
        // SBC A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_sub8bWithCarry(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xDF:
    {
        // RST $18
        instr_rst(reg, mem, 0x0018);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_xE(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xE0:
    {
        // LDH [a8], A
        uint8_t offset = memoryRead(mem, reg->PC + 1);
        memoryWrite(mem, 0xFF00 + offset, reg->A);
        reg->PC += 2;
        break;
    }
    case 0xE1:
    {
        // POP HL
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->HL = stackValue;
        incrementPC(reg);
        break;
    }
    case 0xE2:
    {
        // LDH [C], A
        memoryWrite(mem, 0xFF00 + reg->C, reg->A);
        incrementPC(reg);
        break;
    }
    case 0xE3:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xE4:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xE5:
    {
        // PUSH HL
        stack_push16(reg, mem, reg->HL);
        incrementPC(reg);
        break;
    }
    case 0xE6:
    {
        // AND A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_and(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xE7:
    {
        // RST $20
        instr_rst(reg, mem, 0x0020);
        break;
    }
    case 0xE8:
    {
        // ADD SP, e8
        int8_t offset = (int8_t)memoryRead(mem, reg->PC + 1);

        unset_ZFlag(reg);
        unset_NFlag(reg);

        if (((reg->SP & 0x0F) + (offset & 0x0F)) > 0x0F)
        {
            set_HFlag(reg);
        }
        else
        {
            unset_HFlag(reg);
        }

        if (((reg->SP & 0xFF) + (offset & 0xFF)) > 0xFF)
        {
            set_CFlag(reg);
        }
        else
        {
            unset_CFlag(reg);
        }

        reg->SP = reg->SP + offset;

        reg->PC += 2;
        break;
    }
    case 0xE9:
    {
        // JP HL
        uint16_t hlAddr = reg->HL;
        reg->PC = hlAddr;
        break;
    }
    case 0xEA:
    {
        // LD [a16], A
        uint16_t memAddr = memoryRead16t(mem, reg->PC + 1);
        memoryWrite(mem, memAddr, reg->A);
        reg->PC += 3;
        break;
    }
    case 0xEB:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xEC:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xED:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xEE:
    {
        // XOR A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_xor(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xEF:
    {
        // RST $28
        instr_rst(reg, mem, 0x0028);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}

void opcode_xF(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xF0:
    {
        // LDH A, [a8]
        uint8_t offset = memoryRead(mem, reg->PC + 1);
        uint16_t source_address = 0xFF00 + offset;
        uint8_t value = memoryRead(mem, source_address);
        reg->A = value;
        reg->PC += 2;

        break;
    }
    case 0xF1:
    {
        // POP AF
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->AF = stackValue;
        incrementPC(reg);
        break;
    }
    case 0xF2:
    {
        // LDH A, [C]
        uint16_t offset = 0xFF00 + reg->C;
        uint8_t value = memoryRead(mem, offset);
        reg->A = value;
        incrementPC(reg);
        break;
    }
    case 0xF3:
    {
        // DI
        incrementPC(reg);
        break;
    }
    case 0xF4:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xF5:
    {
        // PUSH AF
        stack_push16(reg, mem, reg->AF);
        incrementPC(reg);
        break;
    }
    case 0xF6:
    {
        // OR A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_or(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xF7:
    {
        // RST $30
        instr_rst(reg, mem, 0x0030);
        break;
    }
    case 0xF8:
    {
        // LD HL, SP + e8
        int8_t offset = (int8_t)memoryRead(mem, reg->PC + 1);
        int16_t stackPointerSum = reg->SP + offset;

        unset_ZFlag(reg);
        unset_NFlag(reg);

        if (((reg->SP & 0x0F) + (offset & 0x0F)) > 0x0F)
        {
            set_HFlag(reg);
        }
        else
        {
            unset_HFlag(reg);
        }

        if (((reg->SP & 0xFF) + (offset & 0xFF)) > 0xFF)
        {
            set_CFlag(reg);
        }
        else
        {
            unset_CFlag(reg);
        }

        reg->HL = reg->SP + offset;

        reg->PC += 2;
        break;
    }
    case 0xF9:
    {
        // LD SP, HL
        reg->SP = reg->HL;
        incrementPC(reg);
        break;
    }
    case 0xFA:
    {
        // LD A, [a16]
        uint16_t memAddr = memoryRead16t(mem, reg->PC + 1);
        uint8_t value = memoryRead(mem, memAddr);
        reg->A = value;
        reg->PC += 3;
        break;
    }
    case 0xFB:
    {
        // EI
        incrementPC(reg);
        break;
    }
    case 0xFC:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xFD:
    {
        // empty instr
        incrementPC(reg);
        break;
    }
    case 0xFE:
    {
        // CP A, n8
        uint8_t memAddrValue = memoryRead(mem, reg->PC + 1);
        instr_cp8b(reg, &reg->A, memAddrValue);
        incrementPC(reg);
        break;
    }
    case 0xFF:
    {
        // RST $38
        instr_rst(reg, mem, 0x0038);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}