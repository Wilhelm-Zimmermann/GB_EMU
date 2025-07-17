#include "./headers/prefixedInstructions.h"
#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/bit.h"

void opcode_xp0(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
    {
        // RLC B
        rotateLeftCircular8b(reg, &reg->B);
        break;
    }
    case 0x01:
    {
        // RLC C
        rotateLeftCircular8b(reg, &reg->C);
        break;
    }
    case 0x02:
    {
        // RLC D
        rotateLeftCircular8b(reg, &reg->D);
        break;
    }
    case 0x03:
    {
        // RLC E
        rotateLeftCircular8b(reg, &reg->E);
        break;
    }
    case 0x04:
    {
        // RLC H
        rotateLeftCircular8b(reg, &reg->H);
        break;
    }
    case 0x05:
    {
        // RLC L
        rotateLeftCircular8b(reg, &reg->L);
        break;
    }
    case 0x06:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeftCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x07:
    {
        // RLC A
        rotateLeftCircular8b(reg, &reg->A);
        break;
    }
    case 0x08:
    {
        // RRC B
        rotateRightCircular8b(reg, &reg->B);
        break;
    }
    case 0x09:
    {
        // RRC C
        rotateRightCircular8b(reg, &reg->C);
        break;
    }
    case 0x0A:
    {
        // RRC D
        rotateRightCircular8b(reg, &reg->D);
        break;
    }
    case 0x0B:
    {
        // RRC E
        rotateRightCircular8b(reg, &reg->E);
        break;
    }
    case 0x0C:
    {
        // RRC H
        rotateRightCircular8b(reg, &reg->H);
        break;
    }
    case 0x0D:
    {
        // RRC L
        rotateRightCircular8b(reg, &reg->L);
        break;
    }
    case 0x0E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRightCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x0F:
    {
        // RRC A
        rotateRightCircular8b(reg, &reg->A);
        break;
    }
    default:
        break;
    }
}
void opcode_xp1(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x10:
    {
        // RLC B
        rotateLeft8b(reg, &reg->B);
        break;
    }
    case 0x11:
    {
        // RLC C
        rotateLeft8b(reg, &reg->C);
        break;
    }
    case 0x12:
    {
        // RLC D
        rotateLeft8b(reg, &reg->D);
        break;
    }
    case 0x13:
    {
        // RLC E
        rotateLeft8b(reg, &reg->E);
        break;
    }
    case 0x14:
    {
        // RLC H
        rotateLeft8b(reg, &reg->H);
        break;
    }
    case 0x15:
    {
        // RLC L
        rotateLeft8b(reg, &reg->L);
        break;
    }
    case 0x16:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeft8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x17:
    {
        // RLC A
        rotateLeft8b(reg, &reg->A);
        break;
    }
    case 0x18:
    {
        // RRC B
        rotateRight8b(reg, &reg->B);
        break;
    }
    case 0x19:
    {
        // RRC C
        rotateRight8b(reg, &reg->C);
        break;
    }
    case 0x1A:
    {
        // RRC D
        rotateRight8b(reg, &reg->D);
        break;
    }
    case 0x1B:
    {
        // RRC E
        rotateRight8b(reg, &reg->E);
        break;
    }
    case 0x1C:
    {
        // RRC H
        rotateRight8b(reg, &reg->H);
        break;
    }
    case 0x1D:
    {
        // RRC L
        rotateRight8b(reg, &reg->L);
        break;
    }
    case 0x1E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRight8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x1F:
    {
        // RRC A
        rotateRight8b(reg, &reg->A);
        break;
    }
    default:
        break;
    }
}
void opcode_xp2(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x20:
    {
        // SLA B
        shiftLeftArithmetic8b(reg, &reg->B);
        break;
    }
    case 0x21:
    {
        // SLA C
        shiftLeftArithmetic8b(reg, &reg->C);
        break;
    }
    case 0x22:
    {
        // SLA D
        shiftLeftArithmetic8b(reg, &reg->D);
        break;
    }
    case 0x23:
    {
        // SLA E
        shiftLeftArithmetic8b(reg, &reg->E);
        break;
    }
    case 0x24:
    {
        // SLA H
        shiftLeftArithmetic8b(reg, &reg->H);
        break;
    }
    case 0x25:
    {
        // SLA L
        shiftLeftArithmetic8b(reg, &reg->L);
        break;
    }
    case 0x26:
    {
        // SLA [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftLeftArithmetic8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x27:
    {
        // SLA A
        shiftLeftArithmetic8b(reg, &reg->A);
        break;
    }
    case 0x28:
    {
        // SRA B
        shiftRightArithmetic8b(reg, &reg->B);
        break;
    }
    case 0x29:
    {
        // SRA C
        shiftRightArithmetic8b(reg, &reg->C);
        break;
    }
    case 0x2A:
    {
        // SRA D
        shiftRightArithmetic8b(reg, &reg->D);
        break;
    }
    case 0x2B:
    {
        // SRA E
        shiftRightArithmetic8b(reg, &reg->E);
        break;
    }
    case 0x2C:
    {
        // SRA H
        shiftRightArithmetic8b(reg, &reg->H);
        break;
    }
    case 0x2D:
    {
        // SRA L
        shiftRightArithmetic8b(reg, &reg->L);
        break;
    }
    case 0x2E:
    {
        // SRA [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftRightArithmetic8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x2F:
    {
        // SRA A
        shiftRightArithmetic8b(reg, &reg->A);
        break;
    }
    default:
        break;
    }
}
void opcode_xp3(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x30:
    {
        // SWAP B
        swap8b(reg, &reg->B);
        break;
    }
    case 0x31:
    {
        // SWAP C
        swap8b(reg, &reg->C);
        break;
    }
    case 0x32:
    {
        // SWAP D
        swap8b(reg, &reg->D);
        break;
    }
    case 0x33:
    {
        // SWAP E
        swap8b(reg, &reg->E);
        break;
    }
    case 0x34:
    {
        // SWAP H
        swap8b(reg, &reg->H);
        break;
    }
    case 0x35:
    {
        // SWAP L
        swap8b(reg, &reg->L);
        break;
    }
    case 0x36:
    {
        // SWAP [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        swap8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x37:
    {
        // SWAP A
        swap8b(reg, &reg->A);
        break;
    }
    case 0x38:
    {
        // SRL B
        shiftRightLogical8b(reg, &reg->B);
        break;
    }
    case 0x39:
    {
        // SRL C
        shiftRightLogical8b(reg, &reg->C);
        break;
    }
    case 0x3A:
    {
        // SRL D
        shiftRightLogical8b(reg, &reg->D);
        break;
    }
    case 0x3B:
    {
        // SRL E
        shiftRightLogical8b(reg, &reg->E);
        break;
    }
    case 0x3C:
    {
        // SRL H
        shiftRightLogical8b(reg, &reg->H);
        break;
    }
    case 0x3D:
    {
        // SRL L
        shiftRightLogical8b(reg, &reg->L);
        break;
    }
    case 0x3E:
    {
        // SRL [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftRightLogical8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x3F:
    {
        // SRL A
        shiftRightLogical8b(reg, &reg->A);
        break;
    }
    default:
        break;
    }
}
void opcode_xp4(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x40:
    {
        // BIT 0, B
        checkBit(reg, &reg->B, 0);
        break;
    }
    case 0x41:
    {
        // BIT 0, C
        checkBit(reg, &reg->C, 0);
        break;
    }
    case 0x42:
    {
        // BIT 0, D
        checkBit(reg, &reg->D, 0);
        break;
    }
    case 0x43:
    {
        // BIT 0, E
        checkBit(reg, &reg->E, 0);
        break;
    }
    case 0x44:
    {
        // BIT 0, H
        checkBit(reg, &reg->H, 0);
        break;
    }
    case 0x45:
    {
        // BIT 0, L
        checkBit(reg, &reg->L, 0);
        break;
    }
    case 0x46:
    {
        // BIT 0, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 0);
        break;
    }
    case 0x47:
    {
        // BIT 0, A
        checkBit(reg, &reg->A, 0);
        break;
    }
    case 0x48:
    {
        // BIT 1, B
        checkBit(reg, &reg->B, 1);
        break;
    }
    case 0x49:
    {
        // BIT 1, C
        checkBit(reg, &reg->C, 1);
        break;
    }
    case 0x4A:
    {
        // BIT 1, D
        checkBit(reg, &reg->D, 1);
        break;
    }
    case 0x4B:
    {
        // BIT 1, E
        checkBit(reg, &reg->E, 1);
        break;
    }
    case 0x4C:
    {
        // BIT 1, H
        checkBit(reg, &reg->H, 1);
        break;
    }
    case 0x4D:
    {
        // BIT 1, L
        checkBit(reg, &reg->L, 1);
        break;
    }
    case 0x4E:
    {
        // BIT 1, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 1);
        break;
    }
    case 0x4F:
    {
        // BIT 1, A
        checkBit(reg, &reg->A, 1);
        break;
    }
    default:
        break;
    }
}
void opcode_xp5(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x50:
    {
        // BIT 2, B
        checkBit(reg, &reg->B, 2);
        break;
    }
    case 0x51:
    {
        // BIT 2, C
        checkBit(reg, &reg->C, 2);
        break;
    }
    case 0x52:
    {
        // BIT 2, D
        checkBit(reg, &reg->D, 2);
        break;
    }
    case 0x53:
    {
        // BIT 2, E
        checkBit(reg, &reg->E, 2);
        break;
    }
    case 0x54:
    {
        // BIT 2, H
        checkBit(reg, &reg->H, 2);
        break;
    }
    case 0x55:
    {
        // BIT 2, L
        checkBit(reg, &reg->L, 2);
        break;
    }
    case 0x56:
    {
        // BIT 2, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 2);
        break;
    }
    case 0x57:
    {
        // BIT 2, A
        checkBit(reg, &reg->A, 2);
        break;
    }
    case 0x58:
    {
        // BIT 3, B
        checkBit(reg, &reg->B, 3);
        break;
    }
    case 0x59:
    {
        // BIT 3, C
        checkBit(reg, &reg->C, 3);
        break;
    }
    case 0x5A:
    {
        // BIT 3, D
        checkBit(reg, &reg->D, 3);
        break;
    }
    case 0x5B:
    {
        // BIT 3, E
        checkBit(reg, &reg->E, 3);
        break;
    }
    case 0x5C:
    {
        // BIT 3, H
        checkBit(reg, &reg->H, 3);
        break;
    }
    case 0x5D:
    {
        // BIT 3, L
        checkBit(reg, &reg->L, 3);
        break;
    }
    case 0x5E:
    {
        // BIT 3, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 3);
        break;
    }
    case 0x5F:
    {
        // BIT 3, A
        checkBit(reg, &reg->A, 3);
        break;
    }
    default:
        break;
    }
}
void opcode_xp6(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x60:
    {
        // BIT 4, B
        checkBit(reg, &reg->B, 4);
        break;
    }
    case 0x61:
    {
        // BIT 4, C
        checkBit(reg, &reg->C, 4);
        break;
    }
    case 0x62:
    {
        // BIT 4, D
        checkBit(reg, &reg->D, 4);
        break;
    }
    case 0x63:
    {
        // BIT 4, E
        checkBit(reg, &reg->E, 4);
        break;
    }
    case 0x64:
    {
        // BIT 4, H
        checkBit(reg, &reg->H, 4);
        break;
    }
    case 0x65:
    {
        // BIT 4, L
        checkBit(reg, &reg->L, 4);
        break;
    }
    case 0x66:
    {
        // BIT 4, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 4);
        break;
    }
    case 0x67:
    {
        // BIT 4, A
        checkBit(reg, &reg->A, 4);
        break;
    }
    case 0x68:
    {
        // BIT 5, B
        checkBit(reg, &reg->B, 5);
        break;
    }
    case 0x69:
    {
        // BIT 5, C
        checkBit(reg, &reg->C, 5);
        break;
    }
    case 0x6A:
    {
        // BIT 5, D
        checkBit(reg, &reg->D, 5);
        break;
    }
    case 0x6B:
    {
        // BIT 5, E
        checkBit(reg, &reg->E, 5);
        break;
    }
    case 0x6C:
    {
        // BIT 5, H
        checkBit(reg, &reg->H, 5);
        break;
    }
    case 0x6D:
    {
        // BIT 5, L
        checkBit(reg, &reg->L, 5);
        break;
    }
    case 0x6E:
    {
        // BIT 5, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 5);
        break;
    }
    case 0x6F:
    {
        // BIT 5, A
        checkBit(reg, &reg->A, 5);
        break;
    }
    default:
        break;
    }
}
void opcode_xp7(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x70:
    {
        // BIT 6, B
        checkBit(reg, &reg->B, 6);
        break;
    }
    case 0x71:
    {
        // BIT 6, C
        checkBit(reg, &reg->C, 6);
        break;
    }
    case 0x72:
    {
        // BIT 6, D
        checkBit(reg, &reg->D, 6);
        break;
    }
    case 0x73:
    {
        // BIT 6, E
        checkBit(reg, &reg->E, 6);
        break;
    }
    case 0x74:
    {
        // BIT 6, H
        checkBit(reg, &reg->H, 6);
        break;
    }
    case 0x75:
    {
        // BIT 6, L
        checkBit(reg, &reg->L, 6);
        break;
    }
    case 0x76:
    {
        // BIT 6, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 6);
        break;
    }
    case 0x77:
    {
        // BIT 6, A
        checkBit(reg, &reg->A, 6);
        break;
    }
    case 0x78:
    {
        // BIT 7, B
        checkBit(reg, &reg->B, 7);
        break;
    }
    case 0x79:
    {
        // BIT 7, C
        checkBit(reg, &reg->C, 7);
        break;
    }
    case 0x7A:
    {
        // BIT 7, D
        checkBit(reg, &reg->D, 7);
        break;
    }
    case 0x7B:
    {
        // BIT 7, E
        checkBit(reg, &reg->E, 7);
        break;
    }
    case 0x7C:
    {
        // BIT 7, H
        checkBit(reg, &reg->H, 7);
        break;
    }
    case 0x7D:
    {
        // BIT 7, L
        checkBit(reg, &reg->L, 7);
        break;
    }
    case 0x7E:
    {
        // BIT 7, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 7);
        break;
    }
    case 0x7F:
    {
        // BIT 7, A
        checkBit(reg, &reg->A, 7);
        break;
    }
    default:
        break;
    }
}
void opcode_xp8(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x80:
    {
        // RES 0, B
        resetBit(reg, &reg->B, 0);
        break;
    }
    case 0x81:
    {
        // RES 0, C
        resetBit(reg, &reg->C, 0);
        break;
    }
    case 0x82:
    {
        // RES 0, D
        resetBit(reg, &reg->D, 0);
        break;
    }
    case 0x83:
    {
        // RES 0, E
        resetBit(reg, &reg->E, 0);
        break;
    }
    case 0x84:
    {
        // RES 0, H
        resetBit(reg, &reg->H, 0);
        break;
    }
    case 0x85:
    {
        // RES 0, L
        resetBit(reg, &reg->L, 0);
        break;
    }
    case 0x86:
    {
        // RES 0, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 0);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x87:
    {
        // RES 0, A
        resetBit(reg, &reg->A, 0);
        break;
    }
    case 0x88:
    {
        // RES 1, B
        resetBit(reg, &reg->B, 1);
        break;
    }
    case 0x89:
    {
        // RES 1, C
        resetBit(reg, &reg->C, 1);
        break;
    }
    case 0x8A:
    {
        // RES 1, D
        resetBit(reg, &reg->D, 1);
        break;
    }
    case 0x8B:
    {
        // RES 1, E
        resetBit(reg, &reg->E, 1);
        break;
    }
    case 0x8C:
    {
        // RES 1, H
        resetBit(reg, &reg->H, 1);
        break;
    }
    case 0x8D:
    {
        // RES 1, L
        resetBit(reg, &reg->L, 1);
        break;
    }
    case 0x8E:
    {
        // RES 1, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 1);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x8F:
    {
        // RES 1, A
        resetBit(reg, &reg->A, 1);
        break;
    }
    default:
        break;
    }
}
void opcode_xp9(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0x90:
    {
        // RES 2, B
        resetBit(reg, &reg->B, 2);
        break;
    }
    case 0x91:
    {
        // RES 2, C
        resetBit(reg, &reg->C, 2);
        break;
    }
    case 0x92:
    {
        // RES 2, D
        resetBit(reg, &reg->D, 2);
        break;
    }
    case 0x93:
    {
        // RES 2, E
        resetBit(reg, &reg->E, 2);
        break;
    }
    case 0x94:
    {
        // RES 2, H
        resetBit(reg, &reg->H, 2);
        break;
    }
    case 0x95:
    {
        // RES 2, L
        resetBit(reg, &reg->L, 2);
        break;
    }
    case 0x96:
    {
        // RES 2, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 2);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x97:
    {
        // RES 2, A
        resetBit(reg, &reg->A, 2);
        break;
    }
    case 0x98:
    {
        // RES 3, B
        resetBit(reg, &reg->B, 3);
        break;
    }
    case 0x99:
    {
        // RES 3, C
        resetBit(reg, &reg->C, 3);
        break;
    }
    case 0x9A:
    {
        // RES 3, D
        resetBit(reg, &reg->D, 3);
        break;
    }
    case 0x9B:
    {
        // RES 3, E
        resetBit(reg, &reg->E, 3);
        break;
    }
    case 0x9C:
    {
        // RES 3, H
        resetBit(reg, &reg->H, 3);
        break;
    }
    case 0x9D:
    {
        // RES 3, L
        resetBit(reg, &reg->L, 3);
        break;
    }
    case 0x9E:
    {
        // RES 3, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 3);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0x9F:
    {
        // RES 3, A
        resetBit(reg, &reg->A, 3);
        break;
    }
    default:
        break;
    }
}
void opcode_xpA(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xA0:
    {
        // RES 4, B
        resetBit(reg, &reg->B, 4);
        break;
    }
    case 0xA1:
    {
        // RES 4, C
        resetBit(reg, &reg->C, 4);
        break;
    }
    case 0xA2:
    {
        // RES 4, D
        resetBit(reg, &reg->D, 4);
        break;
    }
    case 0xA3:
    {
        // RES 4, E
        resetBit(reg, &reg->E, 4);
        break;
    }
    case 0xA4:
    {
        // RES 4, H
        resetBit(reg, &reg->H, 4);
        break;
    }
    case 0xA5:
    {
        // RES 4, L
        resetBit(reg, &reg->L, 4);
        break;
    }
    case 0xA6:
    {
        // RES 4, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 4);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xA7:
    {
        // RES 4, A
        resetBit(reg, &reg->A, 4);
        break;
    }
    case 0xA8:
    {
        // RES 5, B
        resetBit(reg, &reg->B, 5);
        break;
    }
    case 0xA9:
    {
        // RES 5, C
        resetBit(reg, &reg->C, 5);
        break;
    }
    case 0xAA:
    {
        // RES 5, D
        resetBit(reg, &reg->D, 5);
        break;
    }
    case 0xAB:
    {
        // RES 5, E
        resetBit(reg, &reg->E, 5);
        break;
    }
    case 0xAC:
    {
        // RES 5, H
        resetBit(reg, &reg->H, 5);
        break;
    }
    case 0xAD:
    {
        // RES 5, L
        resetBit(reg, &reg->L, 5);
        break;
    }
    case 0xAE:
    {
        // RES 5, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 5);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xAF:
    {
        // RES 5, A
        resetBit(reg, &reg->A, 5);
        break;
    }
    default:
        break;
    }
}
void opcode_xpB(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xB0:
    {
        // RES 6, B
        resetBit(reg, &reg->B, 6);
        break;
    }
    case 0xB1:
    {
        // RES 6, C
        resetBit(reg, &reg->C, 6);
        break;
    }
    case 0xB2:
    {
        // RES 6, D
        resetBit(reg, &reg->D, 6);
        break;
    }
    case 0xB3:
    {
        // RES 6, E
        resetBit(reg, &reg->E, 6);
        break;
    }
    case 0xB4:
    {
        // RES 6, H
        resetBit(reg, &reg->H, 6);
        break;
    }
    case 0xB5:
    {
        // RES 6, L
        resetBit(reg, &reg->L, 6);
        break;
    }
    case 0xB6:
    {
        // RES 6, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 6);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xB7:
    {
        // RES 6, A
        resetBit(reg, &reg->A, 6);
        break;
    }
    case 0xB8:
    {
        // RES 7, B
        resetBit(reg, &reg->B, 7);
        break;
    }
    case 0xB9:
    {
        // RES 7, C
        resetBit(reg, &reg->C, 7);
        break;
    }
    case 0xBA:
    {
        // RES 7, D
        resetBit(reg, &reg->D, 7);
        break;
    }
    case 0xBB:
    {
        // RES 7, E
        resetBit(reg, &reg->E, 7);
        break;
    }
    case 0xBC:
    {
        // RES 7, H
        resetBit(reg, &reg->H, 7);
        break;
    }
    case 0xBD:
    {
        // RES 7, L
        resetBit(reg, &reg->L, 7);
        break;
    }
    case 0xBE:
    {
        // RES 7, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        resetBit(reg, &memVal, 7);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xBF:
    {
        // RES 7, A
        resetBit(reg, &reg->A, 7);
        break;
    }
    default:
        break;
    }
}
void opcode_xpC(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xC0:
    {
        // SET 0, B
        setBit(reg, &reg->B, 0);
        break;
    }
    case 0xC1:
    {
        // SET 0, C
        setBit(reg, &reg->C, 0);
        break;
    }
    case 0xC2:
    {
        // SET 0, D
        setBit(reg, &reg->D, 0);
        break;
    }
    case 0xC3:
    {
        // SET 0, E
        setBit(reg, &reg->E, 0);
        break;
    }
    case 0xC4:
    {
        // SET 0, H
        setBit(reg, &reg->H, 0);
        break;
    }
    case 0xC5:
    {
        // SET 0, L
        setBit(reg, &reg->L, 0);
        break;
    }
    case 0xC6:
    {
        // SET 0, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 0);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xC7:
    {
        // SET 0, A
        setBit(reg, &reg->A, 0);
        break;
    }
    case 0xC8:
    {
        // SET 1, B
        setBit(reg, &reg->B, 1);
        break;
    }
    case 0xC9:
    {
        // SET 1, C
        setBit(reg, &reg->C, 1);
        break;
    }
    case 0xCA:
    {
        // SET 1, D
        setBit(reg, &reg->D, 1);
        break;
    }
    case 0xCB:
    {
        // SET 1, E
        setBit(reg, &reg->E, 1);
        break;
    }
    case 0xCC:
    {
        // SET 1, H
        setBit(reg, &reg->H, 1);
        break;
    }
    case 0xCD:
    {
        // SET 1, L
        setBit(reg, &reg->L, 1);
        break;
    }
    case 0xCE:
    {
        // SET 1, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 1);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xCF:
    {
        // SET 1, A
        setBit(reg, &reg->A, 1);
        break;
    }
    default:
        break;
    }
}
void opcode_xpD(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xD0:
    {
        // SET 2, B
        setBit(reg, &reg->B, 2);
        break;
    }
    case 0xD1:
    {
        // SET 2, C
        setBit(reg, &reg->C, 2);
        break;
    }
    case 0xD2:
    {
        // SET 2, D
        setBit(reg, &reg->D, 2);
        break;
    }
    case 0xD3:
    {
        // SET 2, E
        setBit(reg, &reg->E, 2);
        break;
    }
    case 0xD4:
    {
        // SET 2, H
        setBit(reg, &reg->H, 2);
        break;
    }
    case 0xD5:
    {
        // SET 2, L
        setBit(reg, &reg->L, 2);
        break;
    }
    case 0xD6:
    {
        // SET 2, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 2);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xD7:
    {
        // SET 2, A
        setBit(reg, &reg->A, 2);
        break;
    }
    case 0xD8:
    {
        // SET 3, B
        setBit(reg, &reg->B, 3);
        break;
    }
    case 0xD9:
    {
        // SET 3, C
        setBit(reg, &reg->C, 3);
        break;
    }
    case 0xDA:
    {
        // SET 3, D
        setBit(reg, &reg->D, 3);
        break;
    }
    case 0xDB:
    {
        // SET 3, E
        setBit(reg, &reg->E, 3);
        break;
    }
    case 0xDC:
    {
        // SET 3, H
        setBit(reg, &reg->H, 3);
        break;
    }
    case 0xDD:
    {
        // SET 3, L
        setBit(reg, &reg->L, 3);
        break;
    }
    case 0xDE:
    {
        // SET 3, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 3);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xDF:
    {
        // SET 3, A
        setBit(reg, &reg->A, 3);
        break;
    }
    default:
        break;
    }
}
void opcode_xpE(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xE0:
    {
        // SET 4, B
        setBit(reg, &reg->B, 4);
        break;
    }
    case 0xE1:
    {
        // SET 4, C
        setBit(reg, &reg->C, 4);
        break;
    }
    case 0xE2:
    {
        // SET 4, D
        setBit(reg, &reg->D, 4);
        break;
    }
    case 0xE3:
    {
        // SET 4, E
        setBit(reg, &reg->E, 4);
        break;
    }
    case 0xE4:
    {
        // SET 4, H
        setBit(reg, &reg->H, 4);
        break;
    }
    case 0xE5:
    {
        // SET 4, L
        setBit(reg, &reg->L, 4);
        break;
    }
    case 0xE6:
    {
        // SET 4, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 4);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xE7:
    {
        // SET 4, A
        setBit(reg, &reg->A, 4);
        break;
    }
    case 0xE8:
    {
        // SET 5, B
        setBit(reg, &reg->B, 5);
        break;
    }
    case 0xE9:
    {
        // SET 5, C
        setBit(reg, &reg->C, 5);
        break;
    }
    case 0xEA:
    {
        // SET 5, D
        setBit(reg, &reg->D, 5);
        break;
    }
    case 0xEB:
    {
        // SET 5, E
        setBit(reg, &reg->E, 5);
        break;
    }
    case 0xEC:
    {
        // SET 5, H
        setBit(reg, &reg->H, 5);
        break;
    }
    case 0xED:
    {
        // SET 5, L
        setBit(reg, &reg->L, 5);
        break;
    }
    case 0xEE:
    {
        // SET 5, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 5);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xEF:
    {
        // SET 5, A
        setBit(reg, &reg->A, 5);
        break;
    }
    default:
        break;
    }
}
void opcode_xpF(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    case 0xF0:
    {
        // SET 6, B
        setBit(reg, &reg->B, 6);
        break;
    }
    case 0xF1:
    {
        // SET 6, C
        setBit(reg, &reg->C, 6);
        break;
    }
    case 0xF2:
    {
        // SET 6, D
        setBit(reg, &reg->D, 6);
        break;
    }
    case 0xF3:
    {
        // SET 6, E
        setBit(reg, &reg->E, 6);
        break;
    }
    case 0xF4:
    {
        // SET 6, H
        setBit(reg, &reg->H, 6);
        break;
    }
    case 0xF5:
    {
        // SET 6, L
        setBit(reg, &reg->L, 6);
        break;
    }
    case 0xF6:
    {
        // SET 6, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 6);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xF7:
    {
        // SET 6, A
        setBit(reg, &reg->A, 6);
        break;
    }
    case 0xF8:
    {
        // SET 7, B
        setBit(reg, &reg->B, 7);
        break;
    }
    case 0xF9:
    {
        // SET 7, C
        setBit(reg, &reg->C, 7);
        break;
    }
    case 0xFA:
    {
        // SET 7, D
        setBit(reg, &reg->D, 7);
        break;
    }
    case 0xFB:
    {
        // SET 7, E
        setBit(reg, &reg->E, 7);
        break;
    }
    case 0xFC:
    {
        // SET 7, H
        setBit(reg, &reg->H, 7);
        break;
    }
    case 0xFD:
    {
        // SET 7, L
        setBit(reg, &reg->L, 7);
        break;
    }
    case 0xFE:
    {
        // SET 7, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        setBit(reg, &memVal, 7);
        memoryWrite(mem, reg->HL, memVal);
        break;
    }
    case 0xFF:
    {
        // SET 7, A
        setBit(reg, &reg->A, 7);
        break;
    }
    default:
        break;
    }
}

void execPrefix(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode & 0xF0)
    {
    case 0x00:
        opcode_xp0(reg, mem, opcode);
        break;
    case 0x10:
        opcode_xp1(reg, mem, opcode);
        break;
    case 0x20:
        opcode_xp2(reg, mem, opcode);
        break;
    case 0x30:
        opcode_xp3(reg, mem, opcode);
        break;
    case 0x40:
        opcode_xp4(reg, mem, opcode);
        break;
    case 0x50:
        opcode_xp5(reg, mem, opcode);
        break;
    case 0x60:
        opcode_xp6(reg, mem, opcode);
        break;
    case 0x70:
        opcode_xp7(reg, mem, opcode);
        break;
    case 0x80:
        opcode_xp8(reg, mem, opcode);
        break;
    case 0x90:
        opcode_xp9(reg, mem, opcode);
        break;
    case 0xA0:
        opcode_xpA(reg, mem, opcode);
        break;
    case 0xB0:
        opcode_xpB(reg, mem, opcode);
        break;
    case 0xC0:
        opcode_xpC(reg, mem, opcode);
        break;
    case 0xD0:
        opcode_xpD(reg, mem, opcode);
        break;
    case 0xE0:
        opcode_xpE(reg, mem, opcode);
        break;
    case 0xF0:
        opcode_xpF(reg, mem, opcode);
        break;
    default:
    UNKNOWN_OPCODE:
        // printf("Unknown opcode: %x\n", opcode);
        break;
    }
}