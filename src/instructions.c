#include "./headers/instructions.h"
#include "./headers/prefixedInstructions.h"
#include "./headers/opcodes.h"

uint8_t opcode_x0(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
        // NOP operation
        increment_pc(reg);
        return 4;
        break;
    case 0x01:
    {
        // LD BC, n16
        instr_ld_nxt_16b_addr_reg(reg, mem, &reg->BC);
        return 12;
        break;
    }
    case 0x02:
        // LD [BC], A
        memory_write(mem, reg->BC, reg->A);
        increment_pc(reg);
        return 8;
        break;
    case 0x03:
        // INC BC
        reg->BC++;
        increment_pc(reg);
        return 8;
        break;
    case 0x04:
        // INC B
        instr_inc_8b(reg, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    case 0x05:
        // DEC B
        instr_dec_8b(reg, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    case 0x06:
        // LD B, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->B);
        return 8;
        break;
    case 0x07:
        // RLCA
        uint8_t accMsb = (reg->A >> 7) & 1;
        reg->A = (reg->A << 1) | accMsb;
        reg->F = 0;

        if (accMsb)
        {
            set_c_flag(reg);
        }
        else
        {
            unset_c_flag(reg);
        }
        increment_pc(reg);
        return 4;
        break;
    case 0x08:
    {
        // LD [a16], SP
        uint8_t lowByte = memory_read(mem, reg->PC + 1);
        uint8_t highByte = memory_read(mem, reg->PC + 2);
        uint16_t address = (highByte << 8) | lowByte;

        uint16_t spValue = reg->SP;

        memory_write(mem, address, spValue & 0xFF);
        memory_write(mem, address + 1, spValue >> 8);
        reg->PC += 3;
        return 20;
        break;
    }
    case 0x09:
        // ADD HL, BC
        instr_add_16b(reg, &reg->HL, reg->BC);
        increment_pc(reg);
        return 8;
        break;
    case 0x0A:
    {
        // LD A, [BC]
        instr_ld_addr_8b_reg(reg, mem, reg->BC, &reg->A);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x0B:
        // DEC BC
        reg->BC--;
        increment_pc(reg);
        return 8;
        break;
    case 0x0C:
        // INC C
        instr_inc_8b(reg, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    case 0x0D:
        // DEC C
        instr_dec_8b(reg, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    case 0x0E:
    {
        // LD C, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->C);
        return 8;
        break;
    }
    case 0x0F:
        // RRCA
        {
            uint8_t lsb = reg->A & 0x01;
            reg->A = (reg->A >> 1) | (lsb << 7);
            reg->F = 0;
            if (lsb)
                set_c_flag(reg);
            else
                unset_c_flag(reg);
            increment_pc(reg);
            return 4;
        }
        break;
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x1(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x10:
        // STOP n8 - IDLE EMU
        // Implement this after
        reg->PC += 2;
        return 4;
        break;
    case 0x11:
    {
        // LD DE, n16
        instr_ld_nxt_16b_addr_reg(reg, mem, &reg->DE);
        return 12;
        break;
    }
    case 0x12:
    {
        // LD [DE], A
        memory_write(mem, reg->DE, reg->A);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x13:
    {
        // INC DE
        reg->DE++;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x14:
    {
        // INC D
        instr_inc_8b(reg, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x15:
    {
        // DEC D
        instr_dec_8b(reg, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x16:
    {
        // LD D, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->D);
        return 8;
        break;
    }
    case 0x17:
    {
        // RLA
        uint8_t carryBit = get_c_flag(reg) & 1;
        uint8_t accMSB = (reg->A >> 7) & 1;

        reg->A = (reg->A << 1) | carryBit;

        reg->F = 0;

        if (accMSB)
        {
            set_c_flag(reg);
        }
        else
        {
            unset_c_flag(reg);
        }
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x18:
    {
        // JR e8
        uint8_t unsignedValue = memory_read(mem, reg->PC + 1);
        int8_t signedValue = (int8_t)unsignedValue;
        uint16_t newPCAddr = reg->PC + 2 + signedValue;
        reg->PC = newPCAddr;
        return 12;
        break;
    }
    case 0x19:
    {
        // ADD HL, DE
        instr_add_16b(reg, &reg->HL, reg->DE);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x1A:
    {
        // LD A, [DE]
        instr_ld_addr_8b_reg(reg, mem, reg->DE, &reg->A);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x1B:
    {
        // DEC DE
        reg->DE--;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x1C:
    {
        // INC E
        instr_inc_8b(reg, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x1D:
    {
        // DEC E
        instr_dec_8b(reg, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x1E:
    {
        // LD E, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->E);
        return 8;
        break;
    }
    case 0x1F:
    {
        // RRA
        uint8_t accLSB = reg->A & 1;
        uint8_t carryBit = get_c_flag(reg) & 1;
        reg->A = (reg->A >> 1) | (carryBit << 7);
        reg->F = 0;

        if (accLSB)
        {
            set_c_flag(reg);
        }
        else
        {
            unset_c_flag(reg);
        }
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x2(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x20:
    {
        // JR NZ, e8
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 0)
        {
            uint8_t unsignedValue = memory_read(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
            return 12;
        }
        else
        {
            reg->PC += 2;
            return 8;
        }
        break;
    }
    case 0x21:
    {
        // LD HL, n16
        instr_ld_nxt_16b_addr_reg(reg, mem, &reg->HL);
        return 12;
        break;
    }
    case 0x22:
    {
        // LD [HL+], A
        memory_write(mem, reg->HL, reg->A);
        reg->HL++;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x23:
    {
        // INC HL
        reg->HL++;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x24:
    {
        // INC H
        instr_inc_8b(reg, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x25:
    {
        // DEC H
        instr_dec_8b(reg, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x26:
    {
        // LD H, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->H);
        return 8;
        break;
    }
    case 0x27:
    {
        // DAA
        uint16_t a = reg->A;

        if (!get_n_flag(reg))
        {
            if (get_c_flag(reg) || a > 0x99)
            {
                a += 0x60;
                set_c_flag(reg);
            }
            if (get_h_flag(reg) || (a & 0x0F) > 0x09)
            {
                a += 0x06;
            }
        }
        else
        {
            if (get_c_flag(reg))
            {
                a -= 0x60;
                set_c_flag(reg);
            }
            if (get_h_flag(reg))
            {
                a -= 0x06;
            }
        }

        reg->A = (uint8_t)a;
        check_if_op_zero_and_set_z(reg, reg->A);
        unset_h_flag(reg);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x28:
    {
        // JR Z, e8
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 1)
        {
            uint8_t unsignedValue = memory_read(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
            return 12;
        }
        else
        {
            reg->PC += 2;
            return 8;
        }
        break;
    }
    case 0x29:
    {
        // ADD HL, HL
        instr_add_16b(reg, &reg->HL, reg->HL);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x2A:
    {
        // LD A, [HL+]
        instr_ld_addr_8b_reg(reg, mem, reg->HL, &reg->A);
        reg->HL++;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x2B:
    {
        // DEC HL
        reg->HL--;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x2C:
    {
        // INC L
        instr_inc_8b(reg, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x2D:
    {
        // DEC L
        instr_dec_8b(reg, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x2E:
    {
        // LD L, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->L);
        return 8;
        break;
    }
    case 0x2F:
    {
        // CPL
        reg->A = ~reg->A;
        set_n_flag(reg);
        set_HFlag(reg);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x3(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x30:
    {
        // JR NC, e8
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 0)
        {
            uint8_t unsignedValue = memory_read(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
            return 12;
        }
        else
        {
            reg->PC += 2;
            return 8;
        }
        break;
    }
    case 0x31:
    {
        // LD SP, n16
        instr_ld_nxt_16b_addr_reg(reg, mem, &reg->SP);
        return 12;
        break;
    }
    case 0x32:
    {
        // LD [HL-], A
        memory_write(mem, reg->HL, reg->A);
        reg->HL--;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x33:
    {
        // INC SP
        reg->SP++;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x34:
    {
        // INC [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_inc_8b(reg, &memValue);
        memory_write(mem, reg->HL, memValue);
        increment_pc(reg);
        return 12;
        break;
    }
    case 0x35:
    {
        // DEC [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_dec_8b(reg, &memValue);
        memory_write(mem, reg->HL, memValue);
        increment_pc(reg);
        return 12;
        break;
    }
    case 0x36:
    {
        // LD [HL], n8
        uint8_t memValue = memory_read(mem, reg->PC + 1);
        memory_write(mem, reg->HL, memValue);
        reg->PC += 2;
        return 12;
        break;
    }
    case 0x37:
    {
        // SCF
        set_c_flag(reg);
        unset_h_flag(reg);
        unset_n_flag(reg);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x38:
    {
        // JR C, e8
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 1)
        {
            uint8_t unsignedValue = memory_read(mem, reg->PC + 1);
            int8_t signedValue = (int8_t)unsignedValue;
            uint16_t newPCAddr = reg->PC + 2 + signedValue;
            reg->PC = newPCAddr;
            return 12;
        }
        else
        {
            reg->PC += 2;
            return 8;
        }
        break;
    }
    case 0x39:
    {
        // ADD HL, SP
        instr_add_16b(reg, &reg->HL, reg->SP);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x3A:
    {
        // LD A, [HL-]
        instr_ld_addr_8b_reg(reg, mem, reg->HL, &reg->A);
        reg->HL--;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x3B:
    {
        // DEC SP
        reg->SP--;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x3C:
    {
        // INC A
        instr_inc_8b(reg, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x3D:
    {
        // DEC A
        instr_dec_8b(reg, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x3E:
    {
        // LD A, n8
        instr_ld_nxt_8b_addr_reg(reg, mem, &reg->A);
        return 8;
        break;
    }
    case 0x3F:
    {
        // CCF
        unset_h_flag(reg);
        unset_n_flag(reg);

        if (get_c_flag(reg) == 1)
        {
            unset_c_flag(reg);
        }
        else
        {
            set_c_flag(reg);
        }
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x4(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x40:
    {
        // LD B, B
        instr_ld_8b_in_8b(reg, &reg->B, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x41:
    {
        // LD B, C
        instr_ld_8b_in_8b(reg, &reg->B, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x42:
    {
        // LD B, D
        instr_ld_8b_in_8b(reg, &reg->B, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x43:
    {
        // LD B, E
        instr_ld_8b_in_8b(reg, &reg->B, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x44:
    {
        // LD B, H
        instr_ld_8b_in_8b(reg, &reg->B, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x45:
    {
        // LD B, L
        instr_ld_8b_in_8b(reg, &reg->B, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x46:
    {
        // LD B, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->B, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x47:
    {
        // LD B, A
        instr_ld_8b_in_8b(reg, &reg->B, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x48:
    {
        // LD C, B
        instr_ld_8b_in_8b(reg, &reg->C, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x49:
    {
        // LD C, C
        instr_ld_8b_in_8b(reg, &reg->C, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x4A:
    {
        // LD C, D
        instr_ld_8b_in_8b(reg, &reg->C, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x4B:
    {
        // LD C, E
        instr_ld_8b_in_8b(reg, &reg->C, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x4C:
    {
        // LD C, H
        instr_ld_8b_in_8b(reg, &reg->C, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x4D:
    {
        // LD C, L
        instr_ld_8b_in_8b(reg, &reg->C, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x4E:
    {
        // LD C, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->C, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x4F:
    {
        // LD C, A
        instr_ld_8b_in_8b(reg, &reg->C, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x5(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x50:
    {
        // LD D, B
        instr_ld_8b_in_8b(reg, &reg->D, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x51:
    {
        // LD D, C
        instr_ld_8b_in_8b(reg, &reg->D, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x52:
    {
        // LD D, D
        instr_ld_8b_in_8b(reg, &reg->D, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x53:
    {
        // LD D, E
        instr_ld_8b_in_8b(reg, &reg->D, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x54:
    {
        // LD D, H
        instr_ld_8b_in_8b(reg, &reg->D, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x55:
    {
        // LD D, L
        instr_ld_8b_in_8b(reg, &reg->D, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x56:
    {
        // LD D, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->D, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x57:
    {
        // LD D, A
        instr_ld_8b_in_8b(reg, &reg->D, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x58:
    {
        // LD E, B
        instr_ld_8b_in_8b(reg, &reg->E, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x59:
    {
        // LD E, C
        instr_ld_8b_in_8b(reg, &reg->E, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x5A:
    {
        // LD E, D
        instr_ld_8b_in_8b(reg, &reg->E, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x5B:
    {
        // LD E, E
        instr_ld_8b_in_8b(reg, &reg->E, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x5C:
    {
        // LD E, H
        instr_ld_8b_in_8b(reg, &reg->E, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x5D:
    {
        // LD E, L
        instr_ld_8b_in_8b(reg, &reg->E, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x5E:
    {
        // LD E, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->E, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x5F:
    {
        // LD E, A
        instr_ld_8b_in_8b(reg, &reg->E, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x6(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x60:
    {
        // LD H, B
        instr_ld_8b_in_8b(reg, &reg->H, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x61:
    {
        // LD H, C
        instr_ld_8b_in_8b(reg, &reg->H, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x62:
    {
        // LD H, D
        instr_ld_8b_in_8b(reg, &reg->H, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x63:
    {
        // LD H, E
        instr_ld_8b_in_8b(reg, &reg->H, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x64:
    {
        // LD H, H
        instr_ld_8b_in_8b(reg, &reg->H, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x65:
    {
        // LD H, L
        instr_ld_8b_in_8b(reg, &reg->H, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x66:
    {
        // LD H, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->H, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x67:
    {
        // LD H, A
        instr_ld_8b_in_8b(reg, &reg->H, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x68:
    {
        // LD L, B
        instr_ld_8b_in_8b(reg, &reg->L, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x69:
    {
        // LD L, C
        instr_ld_8b_in_8b(reg, &reg->L, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x6A:
    {
        // LD L, D
        instr_ld_8b_in_8b(reg, &reg->L, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x6B:
    {
        // LD L, E
        instr_ld_8b_in_8b(reg, &reg->L, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x6C:
    {
        // LD L, H
        instr_ld_8b_in_8b(reg, &reg->L, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x6D:
    {
        // LD L, L
        instr_ld_8b_in_8b(reg, &reg->L, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x6E:
    {
        // LD L, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->L, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x6F:
    {
        // LD L, A
        instr_ld_8b_in_8b(reg, &reg->L, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x7(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x70:
    {
        // LD [HL], B
        memory_write(mem, reg->HL, reg->B);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x71:
    {
        // LD [HL], C
        memory_write(mem, reg->HL, reg->C);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x72:
    {
        // LD [HL], D
        memory_write(mem, reg->HL, reg->D);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x73:
    {
        // LD [HL], E
        memory_write(mem, reg->HL, reg->E);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x74:
    {
        // LD [HL], H
        memory_write(mem, reg->HL, reg->H);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x75:
    {
        // LD [HL], L
        memory_write(mem, reg->HL, reg->L);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x76:
    {
        // HALT - Only CPU STOPS - IDLE
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x77:
    {
        // LD [HL], A
        memory_write(mem, reg->HL, reg->A);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x78:
    {
        // LD A, B
        instr_ld_8b_in_8b(reg, &reg->A, &reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x79:
    {
        // LD A, C
        instr_ld_8b_in_8b(reg, &reg->A, &reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x7A:
    {
        // LD A, D
        instr_ld_8b_in_8b(reg, &reg->A, &reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x7B:
    {
        // LD A, E
        instr_ld_8b_in_8b(reg, &reg->A, &reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x7C:
    {
        // LD A, H
        instr_ld_8b_in_8b(reg, &reg->A, &reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x7D:
    {
        // LD A, L
        instr_ld_8b_in_8b(reg, &reg->A, &reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x7E:
    {
        // LD A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_ld_8b_in_8b(reg, &reg->A, &memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x7F:
    {
        // LD A, A
        instr_ld_8b_in_8b(reg, &reg->A, &reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x8(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x80:
    {
        // ADD A, B
        instr_add_8b(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x81:
    {
        // ADD A, C
        instr_add_8b(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x82:
    {
        // ADD A, D
        instr_add_8b(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x83:
    {
        // ADD A, E
        instr_add_8b(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x84:
    {
        // ADD A, H
        instr_add_8b(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x85:
    {
        // ADD A, L
        instr_add_8b(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x86:
    {
        // ADD A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_add_8b(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x87:
    {
        // ADD A, A
        instr_add_8b(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x88:
    {
        // ADC A, B
        instr_add_8b_with_carry(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x89:
    {
        // ADC A, C
        instr_add_8b_with_carry(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x8A:
    {
        // ADC A, D
        instr_add_8b_with_carry(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x8B:
    {
        // ADC A, E
        instr_add_8b_with_carry(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x8C:
    {
        // ADC A, H
        instr_add_8b_with_carry(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x8D:
    {
        // ADC A, L
        instr_add_8b_with_carry(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x8E:
    {
        // ADC A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_add_8b_with_carry(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x8F:
    {
        // ADC A, A
        instr_add_8b_with_carry(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_x9(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x90:
    {
        // SUB A, B
        instr_sub_8b(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x91:
    {
        // SUB A, C
        instr_sub_8b(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x92:
    {
        // SUB A, D
        instr_sub_8b(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x93:
    {
        // SUB A, E
        instr_sub_8b(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x94:
    {
        // SUB A, H
        instr_sub_8b(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x95:
    {
        // SUB A, L
        instr_sub_8b(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x96:
    {
        // SUB A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_sub_8b(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x97:
    {
        // SUB A, A
        instr_sub_8b(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x98:
    {
        // SBC A, B
        instr_sub_8b_with_carry(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x99:
    {
        // SBC A, C
        instr_sub_8b_with_carry(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x9A:
    {
        // SBC A, D
        instr_sub_8b_with_carry(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x9B:
    {
        // SBC A, E
        instr_sub_8b_with_carry(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x9C:
    {
        // SBC A, H
        instr_sub_8b_with_carry(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x9D:
    {
        // SBC A, L
        instr_sub_8b_with_carry(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0x9E:
    {
        // SBC A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_sub_8b_with_carry(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0x9F:
    {
        // SBC A, A
        instr_sub_8b_with_carry(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xA(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xA0:
    {
        // AND A, B
        instr_and(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA1:
    {
        // AND A, C
        instr_and(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA2:
    {
        // AND A, D
        instr_and(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA3:
    {
        // AND A, E
        instr_and(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA4:
    {
        // AND A, H
        instr_and(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA5:
    {
        // AND A, L
        instr_and(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA6:
    {
        // AND A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_and(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xA7:
    {
        // AND A, A
        instr_and(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA8:
    {
        // XOR A, B
        instr_xor(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xA9:
    {
        // XOR A, C
        instr_xor(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xAA:
    {
        // XOR A, D
        instr_xor(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xAB:
    {
        // XOR A, E
        instr_xor(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xAC:
    {
        // XOR A, H
        instr_xor(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xAD:
    {
        // XOR A, L
        instr_xor(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xAE:
    {
        // XOR A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_xor(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xAF:
    {
        // XOR A, A
        instr_xor(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xB(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xB0:
    {
        // OR A, B
        instr_or(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB1:
    {
        // OR A, C
        instr_or(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB2:
    {
        // OR A, D
        instr_or(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB3:
    {
        // OR A, E
        instr_or(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB4:
    {
        // OR A, H
        instr_or(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB5:
    {
        // OR A, L
        instr_or(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB6:
    {
        // OR A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_or(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xB7:
    {
        // OR A, A
        instr_or(reg, &reg->A, reg->A);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB8:
    {
        // CP A, B
        instr_cp_8b(reg, &reg->A, reg->B);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xB9:
    {
        // CP A, C
        instr_cp_8b(reg, &reg->A, reg->C);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xBA:
    {
        // CP A, D
        instr_cp_8b(reg, &reg->A, reg->D);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xBB:
    {
        // CP A, E
        instr_cp_8b(reg, &reg->A, reg->E);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xBC:
    {
        // CP A, H
        instr_cp_8b(reg, &reg->A, reg->H);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xBD:
    {
        // CP A, L
        instr_cp_8b(reg, &reg->A, reg->L);
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xBE:
    {
        // CP A, [HL]
        uint8_t memValue = memory_read(mem, reg->HL);
        instr_cp_8b(reg, &reg->A, memValue);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xBF:
    {
        // CP A, A
        instr_cp_8b(reg, &reg->A, reg->A);
        increment_pc(reg);
        set_z_flag(reg);
        set_n_flag(reg);
        unset_h_flag(reg);
        unset_c_flag(reg);
        return 4;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xC(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xC0:
    {
        // RET NZ
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 0)
        {
            instr_ret(reg, mem);
            return 20;
        }
        else
        {
            increment_pc(reg);
            return 8;
        }
        break;
    }
    case 0xC1:
    {
        // POP BC
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->BC = stackValue;
        increment_pc(reg);
        return 12;
        break;
    }
    case 0xC2:
    {
        // JP NZ, a16
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 0)
        {
            instr_jp_nxt16(reg, mem);
            return 16;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xC3:
    {
        // JP a16
        instr_jp_nxt16(reg, mem);
        return 16;
        break;
    }
    case 0xC4:
    {
        // CALL NZ, a16
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 0)
        {
            instr_callAddr16(reg, mem);
            return 24;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xC5:
    {
        // PUSH BC
        stack_push16(reg, mem, reg->BC);
        increment_pc(reg);
        return 16;
        break;
    }
    case 0xC6:
    {
        // ADD A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_add_8b(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xC7:
    {
        // RST $00
        instr_rst(reg, mem, 0x0000);
        return 16;
        break;
    }
    case 0xC8:
    {
        // RET Z
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 1)
        {
            instr_ret(reg, mem);
            return 20;
        }
        else
        {
            increment_pc(reg);
            return 8;
        }
        break;
    }
    case 0xC9:
    {
        // RET
        instr_ret(reg, mem);
        return 16;
        break;
    }
    case 0xCA:
    {
        // JP Z, a16
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 1)
        {
            instr_jp_nxt16(reg, mem);
            return 16;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xCB:
    {
        // PREFIX
        uint8_t cb_opcode = memory_read(mem, reg->PC + 1);
        uint8_t tState = execPrefix(reg, mem, cb_opcode);
        reg->PC += 2;
        return tState;
        break;
    }
    case 0xCC:
    {
        // CALL Z, a16
        uint8_t zFlagValue = get_z_flag(reg);
        if (zFlagValue == 1)
        {
            instr_callAddr16(reg, mem);
            return 24;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xCD:
    {
        // CALL a16
        instr_callAddr16(reg, mem);
        return 24;
        break;
    }
    case 0xCE:
    {
        // ADC A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_add_8b_with_carry(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xCF:
    {
        // RST $08
        instr_rst(reg, mem, 0x0008);
        return 16;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xD(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xD0:
    {
        // RET NC
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 0)
        {
            instr_ret(reg, mem);
            return 20;
        }
        else
        {
            increment_pc(reg);
            return 8;
        }
        break;
    }
    case 0xD1:
    {
        // POP DE
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->DE = stackValue;
        increment_pc(reg);
        return 12;
        break;
    }
    case 0xD2:
    {
        // JP NC, a16
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 0)
        {
            instr_jp_nxt16(reg, mem);
            return 16;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xD3:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xD4:
    {
        // CALL NC, a16
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 0)
        {
            instr_callAddr16(reg, mem);
            return 24;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xD5:
    {
        // PUSH DE
        stack_push16(reg, mem, reg->DE);
        increment_pc(reg);
        return 16;
        break;
    }
    case 0xD6:
    {
        // SUB A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_sub_8b(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xD7:
    {
        // RST $10
        instr_rst(reg, mem, 0x0010);
        return 16;
        break;
    }
    case 0xD8:
    {
        // RET C
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 1)
        {
            instr_ret(reg, mem);
            return 20;
        }
        else
        {
            increment_pc(reg);
            return 8;
        }
        break;
    }
    case 0xD9:
    {
        // RETI -- TODO: revise when implementing the Interrupt
        instr_ret(reg, mem);
        return 16;
        break;
    }
    case 0xDA:
    {
        // JP C, a16
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 1)
        {
            instr_jp_nxt16(reg, mem);
            return 16;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xDB:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xDC:
    {
        // CALL C, a16
        uint8_t cFlagValue = get_c_flag(reg);
        if (cFlagValue == 1)
        {
            instr_callAddr16(reg, mem);
            return 24;
        }
        else
        {
            reg->PC += 3;
            return 12;
        }
        break;
    }
    case 0xDD:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xDE:
    {
        // SBC A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_sub_8b_with_carry(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xDF:
    {
        // RST $18
        instr_rst(reg, mem, 0x0018);
        return 16;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xE(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xE0:
    {
        // LDH [a8], A
        uint8_t offset = memory_read(mem, reg->PC + 1);
        memory_write(mem, 0xFF00 + offset, reg->A);
        reg->PC += 2;
        return 12;
        break;
    }
    case 0xE1:
    {
        // POP HL
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->HL = stackValue;
        increment_pc(reg);
        return 12;
        break;
    }
    case 0xE2:
    {
        // LDH [C], A
        memory_write(mem, 0xFF00 + reg->C, reg->A);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xE3:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xE4:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xE5:
    {
        // PUSH HL
        stack_push16(reg, mem, reg->HL);
        increment_pc(reg);
        return 16;
        break;
    }
    case 0xE6:
    {
        // AND A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_and(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xE7:
    {
        // RST $20
        instr_rst(reg, mem, 0x0020);
        return 16;
        break;
    }
    case 0xE8:
    {
        // ADD SP, e8
        int8_t offset = (int8_t)memory_read(mem, reg->PC + 1);

        unset_z_flag(reg);
        unset_n_flag(reg);

        if (((reg->SP & 0x0F) + (offset & 0x0F)) > 0x0F)
        {
            set_HFlag(reg);
        }
        else
        {
            unset_h_flag(reg);
        }

        if (((reg->SP & 0xFF) + (offset & 0xFF)) > 0xFF)
        {
            set_c_flag(reg);
        }
        else
        {
            unset_c_flag(reg);
        }

        reg->SP = reg->SP + offset;

        reg->PC += 2;
        return 16;
        break;
    }
    case 0xE9:
    {
        // JP HL
        uint16_t hlAddr = reg->HL;
        reg->PC = hlAddr;
        return 4;
        break;
    }
    case 0xEA:
    {
        // LD [a16], A
        uint16_t memAddr = memory_read_16t(mem, reg->PC + 1);
        memory_write(mem, memAddr, reg->A);
        reg->PC += 3;
        return 16;
        break;
    }
    case 0xEB:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xEC:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xED:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xEE:
    {
        // XOR A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_xor(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xEF:
    {
        // RST $28
        instr_rst(reg, mem, 0x0028);
        return 16;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}

uint8_t opcode_xF(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xF0:
    {
        // LDH A, [a8]
        uint8_t offset = memory_read(mem, reg->PC + 1);
        uint16_t source_address = 0xFF00 + offset;
        uint8_t value = memory_read(mem, source_address);
        reg->A = value;
        reg->PC += 2;
        return 12;
        break;
    }
    case 0xF1:
    {
        // POP AF
        uint16_t stackValue = stack_pop16(reg, mem);
        reg->AF = stackValue & 0xFFF0;
        increment_pc(reg);
        return 12;
        break;
    }
    case 0xF2:
    {
        // LDH A, [C]
        uint16_t offset = 0xFF00 + reg->C;
        uint8_t value = memory_read(mem, offset);
        reg->A = value;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xF3:
    {
        // DI
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xF4:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xF5:
    {
        // PUSH AF
        stack_push16(reg, mem, reg->AF);
        increment_pc(reg);
        return 16;
        break;
    }
    case 0xF6:
    {
        // OR A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_or(reg, &reg->A, memAddrValue);
        increment_pc(reg);
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xF7:
    {
        // RST $30
        instr_rst(reg, mem, 0x0030);
        return 16;
        break;
    }
    case 0xF8:
    {
        // LD HL, SP + e8
        int8_t offset = (int8_t)memory_read(mem, reg->PC + 1);
        int16_t stackPointerSum = reg->SP + offset;

        unset_z_flag(reg);
        unset_n_flag(reg);

        if (((reg->SP & 0x0F) + (offset & 0x0F)) > 0x0F)
        {
            set_HFlag(reg);
        }
        else
        {
            unset_h_flag(reg);
        }

        if (((reg->SP & 0xFF) + (offset & 0xFF)) > 0xFF)
        {
            set_c_flag(reg);
        }
        else
        {
            unset_c_flag(reg);
        }

        reg->HL = reg->SP + offset;

        reg->PC += 2;
        return 12;
        break;
    }
    case 0xF9:
    {
        // LD SP, HL
        reg->SP = reg->HL;
        increment_pc(reg);
        return 8;
        break;
    }
    case 0xFA:
    {
        // LD A, [a16]
        uint16_t memAddr = memory_read_16t(mem, reg->PC + 1);
        uint8_t value = memory_read(mem, memAddr);
        reg->A = value;
        reg->PC += 3;
        return 16;
        break;
    }
    case 0xFB:
    {
        // EI
        increment_pc(reg);
        return 4;
        break;
    }
    case 0xFC:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xFD:
    {
        // empty instr
        increment_pc(reg);
        break;
    }
    case 0xFE:
    {
        // CP A, n8
        uint8_t memAddrValue = memory_read(mem, reg->PC + 1);
        instr_cp_8b(reg, &reg->A, memAddrValue);
        reg->PC += 2;
        return 8;
        break;
    }
    case 0xFF:
    {
        // RST $38
        instr_rst(reg, mem, 0x0038);
        return 16;
        break;
    }
    default:
        increment_pc(reg);
        break;
    }
}