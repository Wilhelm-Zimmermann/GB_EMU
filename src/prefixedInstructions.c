#include "./headers/prefixedInstructions.h"
#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/bit.h"

uint8_t opcode_xp0(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
    {
        // RLC B
        rotate_left_circular_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x01:
    {
        // RLC C
        rotate_left_circular_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x02:
    {
        // RLC D
        rotate_left_circular_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x03:
    {
        // RLC E
        rotate_left_circular_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x04:
    {
        // RLC H
        rotate_left_circular_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x05:
    {
        // RLC L
        rotate_left_circular_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x06:
    {
        // RLC HL
        uint8_t memVal = memory_read(mem, reg->HL);
        rotate_left_circular_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x07:
    {
        // RLC A
        rotate_left_circular_8b(reg, &reg->A);
        return 8;
        break;
    }
    case 0x08:
    {
        // RRC B
        rotate_right_circular_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x09:
    {
        // RRC C
        rotate_right_circular_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x0A:
    {
        // RRC D
        rotate_right_circular_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x0B:
    {
        // RRC E
        rotate_right_circular_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x0C:
    {
        // RRC H
        rotate_right_circular_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x0D:
    {
        // RRC L
        rotate_right_circular_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x0E:
    {
        // RRC HL
        uint8_t memVal = memory_read(mem, reg->HL);
        rotate_right_circular_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x0F:
    {
        // RRC A
        rotate_right_circular_8b(reg, &reg->A);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp1(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x10:
    {
        // RLC B
        rotate_left_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x11:
    {
        // RLC C
        rotate_left_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x12:
    {
        // RLC D
        rotate_left_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x13:
    {
        // RLC E
        rotate_left_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x14:
    {
        // RLC H
        rotate_left_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x15:
    {
        // RLC L
        rotate_left_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x16:
    {
        // RLC HL
        uint8_t memVal = memory_read(mem, reg->HL);
        rotate_left_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x17:
    {
        // RLC A
        rotate_left_8b(reg, &reg->A);
        return 8;
        break;
    }
    case 0x18:
    {
        // RRC B
        rotate_right_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x19:
    {
        // RRC C
        rotate_right_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x1A:
    {
        // RRC D
        rotate_right_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x1B:
    {
        // RRC E
        rotate_right_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x1C:
    {
        // RRC H
        rotate_right_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x1D:
    {
        // RRC L
        rotate_right_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x1E:
    {
        // RRC HL
        uint8_t memVal = memory_read(mem, reg->HL);
        rotate_right_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x1F:
    {
        // RRC A
        rotate_right_8b(reg, &reg->A);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp2(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x20:
    {
        // SLA B
        shift_left_arithmetic_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x21:
    {
        // SLA C
        shift_left_arithmetic_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x22:
    {
        // SLA D
        shift_left_arithmetic_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x23:
    {
        // SLA E
        shift_left_arithmetic_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x24:
    {
        // SLA H
        shift_left_arithmetic_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x25:
    {
        // SLA L
        shift_left_arithmetic_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x26:
    {
        // SLA [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        shift_left_arithmetic_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x27:
    {
        // SLA A
        shift_left_arithmetic_8b(reg, &reg->A);
        return 8;
        break;
    }
    case 0x28:
    {
        // SRA B
        shift_right_arithmetic_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x29:
    {
        // SRA C
        shift_right_arithmetic_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x2A:
    {
        // SRA D
        shift_right_arithmetic_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x2B:
    {
        // SRA E
        shift_right_arithmetic_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x2C:
    {
        // SRA H
        shift_right_arithmetic_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x2D:
    {
        // SRA L
        shift_right_arithmetic_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x2E:
    {
        // SRA [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        shift_right_arithmetic_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x2F:
    {
        // SRA A
        shift_right_arithmetic_8b(reg, &reg->A);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp3(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x30:
    {
        // SWAP B
        swap_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x31:
    {
        // SWAP C
        swap_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x32:
    {
        // SWAP D
        swap_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x33:
    {
        // SWAP E
        swap_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x34:
    {
        // SWAP H
        swap_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x35:
    {
        // SWAP L
        swap_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x36:
    {
        // SWAP [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        swap_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x37:
    {
        // SWAP A
        swap_8b(reg, &reg->A);
        return 8;
        break;
    }
    case 0x38:
    {
        // SRL B
        shift_right_logical_8b(reg, &reg->B);
        return 8;
        break;
    }
    case 0x39:
    {
        // SRL C
        shift_right_logical_8b(reg, &reg->C);
        return 8;
        break;
    }
    case 0x3A:
    {
        // SRL D
        shift_right_logical_8b(reg, &reg->D);
        return 8;
        break;
    }
    case 0x3B:
    {
        // SRL E
        shift_right_logical_8b(reg, &reg->E);
        return 8;
        break;
    }
    case 0x3C:
    {
        // SRL H
        shift_right_logical_8b(reg, &reg->H);
        return 8;
        break;
    }
    case 0x3D:
    {
        // SRL L
        shift_right_logical_8b(reg, &reg->L);
        return 8;
        break;
    }
    case 0x3E:
    {
        // SRL [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        shift_right_logical_8b(reg, &memVal);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x3F:
    {
        // SRL A
        shift_right_logical_8b(reg, &reg->A);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp4(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x40:
    {
        // BIT 0, B
        check_bit(reg, &reg->B, 0);
        return 8;
        break;
    }
    case 0x41:
    {
        // BIT 0, C
        check_bit(reg, &reg->C, 0);
        return 8;
        break;
    }
    case 0x42:
    {
        // BIT 0, D
        check_bit(reg, &reg->D, 0);
        return 8;
        break;
    }
    case 0x43:
    {
        // BIT 0, E
        check_bit(reg, &reg->E, 0);
        return 8;
        break;
    }
    case 0x44:
    {
        // BIT 0, H
        check_bit(reg, &reg->H, 0);
        return 8;
        break;
    }
    case 0x45:
    {
        // BIT 0, L
        check_bit(reg, &reg->L, 0);
        return 8;
        break;
    }
    case 0x46:
    {
        // BIT 0, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 0);
        return 8;
        break;
    }
    case 0x47:
    {
        // BIT 0, A
        check_bit(reg, &reg->A, 0);
        return 8;
        break;
    }
    case 0x48:
    {
        // BIT 1, B
        check_bit(reg, &reg->B, 1);
        return 8;
        break;
    }
    case 0x49:
    {
        // BIT 1, C
        check_bit(reg, &reg->C, 1);
        return 8;
        break;
    }
    case 0x4A:
    {
        // BIT 1, D
        check_bit(reg, &reg->D, 1);
        return 8;
        break;
    }
    case 0x4B:
    {
        // BIT 1, E
        check_bit(reg, &reg->E, 1);
        return 8;
        break;
    }
    case 0x4C:
    {
        // BIT 1, H
        check_bit(reg, &reg->H, 1);
        return 8;
        break;
    }
    case 0x4D:
    {
        // BIT 1, L
        check_bit(reg, &reg->L, 1);
        return 8;
        break;
    }
    case 0x4E:
    {
        // BIT 1, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 1);
        return 8;
        break;
    }
    case 0x4F:
    {
        // BIT 1, A
        check_bit(reg, &reg->A, 1);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp5(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x50:
    {
        // BIT 2, B
        check_bit(reg, &reg->B, 2);
        return 8;
        break;
    }
    case 0x51:
    {
        // BIT 2, C
        check_bit(reg, &reg->C, 2);
        return 8;
        break;
    }
    case 0x52:
    {
        // BIT 2, D
        check_bit(reg, &reg->D, 2);
        return 8;
        break;
    }
    case 0x53:
    {
        // BIT 2, E
        check_bit(reg, &reg->E, 2);
        return 8;
        break;
    }
    case 0x54:
    {
        // BIT 2, H
        check_bit(reg, &reg->H, 2);
        return 8;
        break;
    }
    case 0x55:
    {
        // BIT 2, L
        check_bit(reg, &reg->L, 2);
        return 8;
        break;
    }
    case 0x56:
    {
        // BIT 2, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 2);
        return 8;
        break;
    }
    case 0x57:
    {
        // BIT 2, A
        check_bit(reg, &reg->A, 2);
        return 8;
        break;
    }
    case 0x58:
    {
        // BIT 3, B
        check_bit(reg, &reg->B, 3);
        return 8;
        break;
    }
    case 0x59:
    {
        // BIT 3, C
        check_bit(reg, &reg->C, 3);
        return 8;
        break;
    }
    case 0x5A:
    {
        // BIT 3, D
        check_bit(reg, &reg->D, 3);
        return 8;
        break;
    }
    case 0x5B:
    {
        // BIT 3, E
        check_bit(reg, &reg->E, 3);
        return 8;
        break;
    }
    case 0x5C:
    {
        // BIT 3, H
        check_bit(reg, &reg->H, 3);
        return 8;
        break;
    }
    case 0x5D:
    {
        // BIT 3, L
        check_bit(reg, &reg->L, 3);
        return 8;
        break;
    }
    case 0x5E:
    {
        // BIT 3, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 3);
        return 8;
        break;
    }
    case 0x5F:
    {
        // BIT 3, A
        check_bit(reg, &reg->A, 3);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp6(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x60:
    {
        // BIT 4, B
        check_bit(reg, &reg->B, 4);
        return 8;
        break;
    }
    case 0x61:
    {
        // BIT 4, C
        check_bit(reg, &reg->C, 4);
        return 8;
        break;
    }
    case 0x62:
    {
        // BIT 4, D
        check_bit(reg, &reg->D, 4);
        return 8;
        break;
    }
    case 0x63:
    {
        // BIT 4, E
        check_bit(reg, &reg->E, 4);
        return 8;
        break;
    }
    case 0x64:
    {
        // BIT 4, H
        check_bit(reg, &reg->H, 4);
        return 8;
        break;
    }
    case 0x65:
    {
        // BIT 4, L
        check_bit(reg, &reg->L, 4);
        return 8;
        break;
    }
    case 0x66:
    {
        // BIT 4, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 4);
        return 8;
        break;
    }
    case 0x67:
    {
        // BIT 4, A
        check_bit(reg, &reg->A, 4);
        return 8;
        break;
    }
    case 0x68:
    {
        // BIT 5, B
        check_bit(reg, &reg->B, 5);
        return 8;
        break;
    }
    case 0x69:
    {
        // BIT 5, C
        check_bit(reg, &reg->C, 5);
        return 8;
        break;
    }
    case 0x6A:
    {
        // BIT 5, D
        check_bit(reg, &reg->D, 5);
        return 8;
        break;
    }
    case 0x6B:
    {
        // BIT 5, E
        check_bit(reg, &reg->E, 5);
        return 8;
        break;
    }
    case 0x6C:
    {
        // BIT 5, H
        check_bit(reg, &reg->H, 5);
        return 8;
        break;
    }
    case 0x6D:
    {
        // BIT 5, L
        check_bit(reg, &reg->L, 5);
        return 8;
        break;
    }
    case 0x6E:
    {
        // BIT 5, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 5);
        return 8;
        break;
    }
    case 0x6F:
    {
        // BIT 5, A
        check_bit(reg, &reg->A, 5);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp7(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x70:
    {
        // BIT 6, B
        check_bit(reg, &reg->B, 6);
        return 8;
        break;
    }
    case 0x71:
    {
        // BIT 6, C
        check_bit(reg, &reg->C, 6);
        return 8;
        break;
    }
    case 0x72:
    {
        // BIT 6, D
        check_bit(reg, &reg->D, 6);
        return 8;
        break;
    }
    case 0x73:
    {
        // BIT 6, E
        check_bit(reg, &reg->E, 6);
        return 8;
        break;
    }
    case 0x74:
    {
        // BIT 6, H
        check_bit(reg, &reg->H, 6);
        return 8;
        break;
    }
    case 0x75:
    {
        // BIT 6, L
        check_bit(reg, &reg->L, 6);
        return 8;
        break;
    }
    case 0x76:
    {
        // BIT 6, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 6);
        return 8;
        break;
    }
    case 0x77:
    {
        // BIT 6, A
        check_bit(reg, &reg->A, 6);
        return 8;
        break;
    }
    case 0x78:
    {
        // BIT 7, B
        check_bit(reg, &reg->B, 7);
        return 8;
        break;
    }
    case 0x79:
    {
        // BIT 7, C
        check_bit(reg, &reg->C, 7);
        return 8;
        break;
    }
    case 0x7A:
    {
        // BIT 7, D
        check_bit(reg, &reg->D, 7);
        return 8;
        break;
    }
    case 0x7B:
    {
        // BIT 7, E
        check_bit(reg, &reg->E, 7);
        return 8;
        break;
    }
    case 0x7C:
    {
        // BIT 7, H
        check_bit(reg, &reg->H, 7);
        return 8;
        break;
    }
    case 0x7D:
    {
        // BIT 7, L
        check_bit(reg, &reg->L, 7);
        return 8;
        break;
    }
    case 0x7E:
    {
        // BIT 7, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        check_bit(reg, &memVal, 7);
        return 8;
        break;
    }
    case 0x7F:
    {
        // BIT 7, A
        check_bit(reg, &reg->A, 7);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp8(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x80:
    {
        // RES 0, B
        reset_bit(reg, &reg->B, 0);
        return 8;
        break;
    }
    case 0x81:
    {
        // RES 0, C
        reset_bit(reg, &reg->C, 0);
        return 8;
        break;
    }
    case 0x82:
    {
        // RES 0, D
        reset_bit(reg, &reg->D, 0);
        return 8;
        break;
    }
    case 0x83:
    {
        // RES 0, E
        reset_bit(reg, &reg->E, 0);
        return 8;
        break;
    }
    case 0x84:
    {
        // RES 0, H
        reset_bit(reg, &reg->H, 0);
        return 8;
        break;
    }
    case 0x85:
    {
        // RES 0, L
        reset_bit(reg, &reg->L, 0);
        return 8;
        break;
    }
    case 0x86:
    {
        // RES 0, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 0);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x87:
    {
        // RES 0, A
        reset_bit(reg, &reg->A, 0);
        return 8;
        break;
    }
    case 0x88:
    {
        // RES 1, B
        reset_bit(reg, &reg->B, 1);
        return 8;
        break;
    }
    case 0x89:
    {
        // RES 1, C
        reset_bit(reg, &reg->C, 1);
        return 8;
        break;
    }
    case 0x8A:
    {
        // RES 1, D
        reset_bit(reg, &reg->D, 1);
        return 8;
        break;
    }
    case 0x8B:
    {
        // RES 1, E
        reset_bit(reg, &reg->E, 1);
        return 8;
        break;
    }
    case 0x8C:
    {
        // RES 1, H
        reset_bit(reg, &reg->H, 1);
        return 8;
        break;
    }
    case 0x8D:
    {
        // RES 1, L
        reset_bit(reg, &reg->L, 1);
        return 8;
        break;
    }
    case 0x8E:
    {
        // RES 1, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 1);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x8F:
    {
        // RES 1, A
        reset_bit(reg, &reg->A, 1);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xp9(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x90:
    {
        // RES 2, B
        reset_bit(reg, &reg->B, 2);
        return 8;
        break;
    }
    case 0x91:
    {
        // RES 2, C
        reset_bit(reg, &reg->C, 2);
        return 8;
        break;
    }
    case 0x92:
    {
        // RES 2, D
        reset_bit(reg, &reg->D, 2);
        return 8;
        break;
    }
    case 0x93:
    {
        // RES 2, E
        reset_bit(reg, &reg->E, 2);
        return 8;
        break;
    }
    case 0x94:
    {
        // RES 2, H
        reset_bit(reg, &reg->H, 2);
        return 8;
        break;
    }
    case 0x95:
    {
        // RES 2, L
        reset_bit(reg, &reg->L, 2);
        return 8;
        break;
    }
    case 0x96:
    {
        // RES 2, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 2);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x97:
    {
        // RES 2, A
        reset_bit(reg, &reg->A, 2);
        return 8;
        break;
    }
    case 0x98:
    {
        // RES 3, B
        reset_bit(reg, &reg->B, 3);
        return 8;
        break;
    }
    case 0x99:
    {
        // RES 3, C
        reset_bit(reg, &reg->C, 3);
        return 8;
        break;
    }
    case 0x9A:
    {
        // RES 3, D
        reset_bit(reg, &reg->D, 3);
        return 8;
        break;
    }
    case 0x9B:
    {
        // RES 3, E
        reset_bit(reg, &reg->E, 3);
        return 8;
        break;
    }
    case 0x9C:
    {
        // RES 3, H
        reset_bit(reg, &reg->H, 3);
        return 8;
        break;
    }
    case 0x9D:
    {
        // RES 3, L
        reset_bit(reg, &reg->L, 3);
        return 8;
        break;
    }
    case 0x9E:
    {
        // RES 3, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 3);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0x9F:
    {
        // RES 3, A
        reset_bit(reg, &reg->A, 3);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpA(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xA0:
    {
        // RES 4, B
        reset_bit(reg, &reg->B, 4);
        return 8;
        break;
    }
    case 0xA1:
    {
        // RES 4, C
        reset_bit(reg, &reg->C, 4);
        return 8;
        break;
    }
    case 0xA2:
    {
        // RES 4, D
        reset_bit(reg, &reg->D, 4);
        return 8;
        break;
    }
    case 0xA3:
    {
        // RES 4, E
        reset_bit(reg, &reg->E, 4);
        return 8;
        break;
    }
    case 0xA4:
    {
        // RES 4, H
        reset_bit(reg, &reg->H, 4);
        return 8;
        break;
    }
    case 0xA5:
    {
        // RES 4, L
        reset_bit(reg, &reg->L, 4);
        return 8;
        break;
    }
    case 0xA6:
    {
        // RES 4, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 4);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xA7:
    {
        // RES 4, A
        reset_bit(reg, &reg->A, 4);
        return 8;
        break;
    }
    case 0xA8:
    {
        // RES 5, B
        reset_bit(reg, &reg->B, 5);
        return 8;
        break;
    }
    case 0xA9:
    {
        // RES 5, C
        reset_bit(reg, &reg->C, 5);
        return 8;
        break;
    }
    case 0xAA:
    {
        // RES 5, D
        reset_bit(reg, &reg->D, 5);
        return 8;
        break;
    }
    case 0xAB:
    {
        // RES 5, E
        reset_bit(reg, &reg->E, 5);
        return 8;
        break;
    }
    case 0xAC:
    {
        // RES 5, H
        reset_bit(reg, &reg->H, 5);
        return 8;
        break;
    }
    case 0xAD:
    {
        // RES 5, L
        reset_bit(reg, &reg->L, 5);
        return 8;
        break;
    }
    case 0xAE:
    {
        // RES 5, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 5);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xAF:
    {
        // RES 5, A
        reset_bit(reg, &reg->A, 5);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpB(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xB0:
    {
        // RES 6, B
        reset_bit(reg, &reg->B, 6);
        return 8;
        break;
    }
    case 0xB1:
    {
        // RES 6, C
        reset_bit(reg, &reg->C, 6);
        return 8;
        break;
    }
    case 0xB2:
    {
        // RES 6, D
        reset_bit(reg, &reg->D, 6);
        return 8;
        break;
    }
    case 0xB3:
    {
        // RES 6, E
        reset_bit(reg, &reg->E, 6);
        return 8;
        break;
    }
    case 0xB4:
    {
        // RES 6, H
        reset_bit(reg, &reg->H, 6);
        return 8;
        break;
    }
    case 0xB5:
    {
        // RES 6, L
        reset_bit(reg, &reg->L, 6);
        return 8;
        break;
    }
    case 0xB6:
    {
        // RES 6, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 6);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xB7:
    {
        // RES 6, A
        reset_bit(reg, &reg->A, 6);
        return 8;
        break;
    }
    case 0xB8:
    {
        // RES 7, B
        reset_bit(reg, &reg->B, 7);
        return 8;
        break;
    }
    case 0xB9:
    {
        // RES 7, C
        reset_bit(reg, &reg->C, 7);
        return 8;
        break;
    }
    case 0xBA:
    {
        // RES 7, D
        reset_bit(reg, &reg->D, 7);
        return 8;
        break;
    }
    case 0xBB:
    {
        // RES 7, E
        reset_bit(reg, &reg->E, 7);
        return 8;
        break;
    }
    case 0xBC:
    {
        // RES 7, H
        reset_bit(reg, &reg->H, 7);
        return 8;
        break;
    }
    case 0xBD:
    {
        // RES 7, L
        reset_bit(reg, &reg->L, 7);
        return 8;
        break;
    }
    case 0xBE:
    {
        // RES 7, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        reset_bit(reg, &memVal, 7);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xBF:
    {
        // RES 7, A
        reset_bit(reg, &reg->A, 7);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpC(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xC0:
    {
        // SET 0, B
        set_bit(reg, &reg->B, 0);
        return 8;
        break;
    }
    case 0xC1:
    {
        // SET 0, C
        set_bit(reg, &reg->C, 0);
        return 8;
        break;
    }
    case 0xC2:
    {
        // SET 0, D
        set_bit(reg, &reg->D, 0);
        return 8;
        break;
    }
    case 0xC3:
    {
        // SET 0, E
        set_bit(reg, &reg->E, 0);
        return 8;
        break;
    }
    case 0xC4:
    {
        // SET 0, H
        set_bit(reg, &reg->H, 0);
        return 8;
        break;
    }
    case 0xC5:
    {
        // SET 0, L
        set_bit(reg, &reg->L, 0);
        return 8;
        break;
    }
    case 0xC6:
    {
        // SET 0, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 0);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xC7:
    {
        // SET 0, A
        set_bit(reg, &reg->A, 0);
        return 8;
        break;
    }
    case 0xC8:
    {
        // SET 1, B
        set_bit(reg, &reg->B, 1);
        return 8;
        break;
    }
    case 0xC9:
    {
        // SET 1, C
        set_bit(reg, &reg->C, 1);
        return 8;
        break;
    }
    case 0xCA:
    {
        // SET 1, D
        set_bit(reg, &reg->D, 1);
        return 8;
        break;
    }
    case 0xCB:
    {
        // SET 1, E
        set_bit(reg, &reg->E, 1);
        return 8;
        break;
    }
    case 0xCC:
    {
        // SET 1, H
        set_bit(reg, &reg->H, 1);
        return 8;
        break;
    }
    case 0xCD:
    {
        // SET 1, L
        set_bit(reg, &reg->L, 1);
        return 8;
        break;
    }
    case 0xCE:
    {
        // SET 1, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 1);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xCF:
    {
        // SET 1, A
        set_bit(reg, &reg->A, 1);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpD(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xD0:
    {
        // SET 2, B
        set_bit(reg, &reg->B, 2);
        return 8;
        break;
    }
    case 0xD1:
    {
        // SET 2, C
        set_bit(reg, &reg->C, 2);
        return 8;
        break;
    }
    case 0xD2:
    {
        // SET 2, D
        set_bit(reg, &reg->D, 2);
        return 8;
        break;
    }
    case 0xD3:
    {
        // SET 2, E
        set_bit(reg, &reg->E, 2);
        return 8;
        break;
    }
    case 0xD4:
    {
        // SET 2, H
        set_bit(reg, &reg->H, 2);
        return 8;
        break;
    }
    case 0xD5:
    {
        // SET 2, L
        set_bit(reg, &reg->L, 2);
        return 8;
        break;
    }
    case 0xD6:
    {
        // SET 2, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 2);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xD7:
    {
        // SET 2, A
        set_bit(reg, &reg->A, 2);
        return 8;
        break;
    }
    case 0xD8:
    {
        // SET 3, B
        set_bit(reg, &reg->B, 3);
        return 8;
        break;
    }
    case 0xD9:
    {
        // SET 3, C
        set_bit(reg, &reg->C, 3);
        return 8;
        break;
    }
    case 0xDA:
    {
        // SET 3, D
        set_bit(reg, &reg->D, 3);
        return 8;
        break;
    }
    case 0xDB:
    {
        // SET 3, E
        set_bit(reg, &reg->E, 3);
        return 8;
        break;
    }
    case 0xDC:
    {
        // SET 3, H
        set_bit(reg, &reg->H, 3);
        return 8;
        break;
    }
    case 0xDD:
    {
        // SET 3, L
        set_bit(reg, &reg->L, 3);
        return 8;
        break;
    }
    case 0xDE:
    {
        // SET 3, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 3);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xDF:
    {
        // SET 3, A
        set_bit(reg, &reg->A, 3);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpE(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xE0:
    {
        // SET 4, B
        set_bit(reg, &reg->B, 4);
        return 8;
        break;
    }
    case 0xE1:
    {
        // SET 4, C
        set_bit(reg, &reg->C, 4);
        return 8;
        break;
    }
    case 0xE2:
    {
        // SET 4, D
        set_bit(reg, &reg->D, 4);
        return 8;
        break;
    }
    case 0xE3:
    {
        // SET 4, E
        set_bit(reg, &reg->E, 4);
        return 8;
        break;
    }
    case 0xE4:
    {
        // SET 4, H
        set_bit(reg, &reg->H, 4);
        return 8;
        break;
    }
    case 0xE5:
    {
        // SET 4, L
        set_bit(reg, &reg->L, 4);
        return 8;
        break;
    }
    case 0xE6:
    {
        // SET 4, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 4);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xE7:
    {
        // SET 4, A
        set_bit(reg, &reg->A, 4);
        return 8;
        break;
    }
    case 0xE8:
    {
        // SET 5, B
        set_bit(reg, &reg->B, 5);
        return 8;
        break;
    }
    case 0xE9:
    {
        // SET 5, C
        set_bit(reg, &reg->C, 5);
        return 8;
        break;
    }
    case 0xEA:
    {
        // SET 5, D
        set_bit(reg, &reg->D, 5);
        return 8;
        break;
    }
    case 0xEB:
    {
        // SET 5, E
        set_bit(reg, &reg->E, 5);
        return 8;
        break;
    }
    case 0xEC:
    {
        // SET 5, H
        set_bit(reg, &reg->H, 5);
        return 8;
        break;
    }
    case 0xED:
    {
        // SET 5, L
        set_bit(reg, &reg->L, 5);
        return 8;
        break;
    }
    case 0xEE:
    {
        // SET 5, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 5);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xEF:
    {
        // SET 5, A
        set_bit(reg, &reg->A, 5);
        return 8;
        break;
    }
    default:
        break;
    }
}
uint8_t opcode_xpF(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xF0:
    {
        // SET 6, B
        set_bit(reg, &reg->B, 6);
        return 8;
        break;
    }
    case 0xF1:
    {
        // SET 6, C
        set_bit(reg, &reg->C, 6);
        return 8;
        break;
    }
    case 0xF2:
    {
        // SET 6, D
        set_bit(reg, &reg->D, 6);
        return 8;
        break;
    }
    case 0xF3:
    {
        // SET 6, E
        set_bit(reg, &reg->E, 6);
        return 8;
        break;
    }
    case 0xF4:
    {
        // SET 6, H
        set_bit(reg, &reg->H, 6);
        return 8;
        break;
    }
    case 0xF5:
    {
        // SET 6, L
        set_bit(reg, &reg->L, 6);
        return 8;
        break;
    }
    case 0xF6:
    {
        // SET 6, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 6);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xF7:
    {
        // SET 6, A
        set_bit(reg, &reg->A, 6);
        return 8;
        break;
    }
    case 0xF8:
    {
        // SET 7, B
        set_bit(reg, &reg->B, 7);
        return 8;
        break;
    }
    case 0xF9:
    {
        // SET 7, C
        set_bit(reg, &reg->C, 7);
        return 8;
        break;
    }
    case 0xFA:
    {
        // SET 7, D
        set_bit(reg, &reg->D, 7);
        return 8;
        break;
    }
    case 0xFB:
    {
        // SET 7, E
        set_bit(reg, &reg->E, 7);
        return 8;
        break;
    }
    case 0xFC:
    {
        // SET 7, H
        set_bit(reg, &reg->H, 7);
        return 8;
        break;
    }
    case 0xFD:
    {
        // SET 7, L
        set_bit(reg, &reg->L, 7);
        return 8;
        break;
    }
    case 0xFE:
    {
        // SET 7, [HL]
        uint8_t memVal = memory_read(mem, reg->HL);
        set_bit(reg, &memVal, 7);
        memory_write(mem, reg->HL, memVal);
        return 8;
        break;
    }
    case 0xFF:
    {
        // SET 7, A
        set_bit(reg, &reg->A, 7);
        return 8;
        break;
    }
    default:
        break;
    }
}

uint8_t execPrefix(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode & 0xF0)
    {
    case 0x00:
        return opcode_xp0(reg, mem, opcode);
        break;
    case 0x10:
        return opcode_xp1(reg, mem, opcode);
        break;
    case 0x20:
        return opcode_xp2(reg, mem, opcode);
        break;
    case 0x30:
        return opcode_xp3(reg, mem, opcode);
        break;
    case 0x40:
        return opcode_xp4(reg, mem, opcode);
        break;
    case 0x50:
        return opcode_xp5(reg, mem, opcode);
        break;
    case 0x60:
        return opcode_xp6(reg, mem, opcode);
        break;
    case 0x70:
        return opcode_xp7(reg, mem, opcode);
        break;
    case 0x80:
        return opcode_xp8(reg, mem, opcode);
        break;
    case 0x90:
        return opcode_xp9(reg, mem, opcode);
        break;
    case 0xA0:
        return opcode_xpA(reg, mem, opcode);
        break;
    case 0xB0:
        return opcode_xpB(reg, mem, opcode);
        break;
    case 0xC0:
        return opcode_xpC(reg, mem, opcode);
        break;
    case 0xD0:
        return opcode_xpD(reg, mem, opcode);
        break;
    case 0xE0:
        return opcode_xpE(reg, mem, opcode);
        break;
    case 0xF0:
        return opcode_xpF(reg, mem, opcode);
        break;
    default:
    UNKNOWN_OPCODE:
        // printf("Unknown opcode: %x\n", opcode);
        return 4;
        break;
    }
}