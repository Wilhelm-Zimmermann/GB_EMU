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
        incrementPC(reg);
        break;
    }
    case 0x01:
    {
        // RLC C
        rotateLeftCircular8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x02:
    {
        // RLC D
        rotateLeftCircular8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x03:
    {
        // RLC E
        rotateLeftCircular8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x04:
    {
        // RLC H
        rotateLeftCircular8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x05:
    {
        // RLC L
        rotateLeftCircular8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x06:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeftCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x07:
    {
        // RLC A
        rotateLeftCircular8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    case 0x08:
    {
        // RRC B
        rotateRightCircular8b(reg, &reg->B);
        incrementPC(reg);
        break;
    }
    case 0x09:
    {
        // RRC C
        rotateRightCircular8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x0A:
    {
        // RRC D
        rotateRightCircular8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x0B:
    {
        // RRC E
        rotateRightCircular8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x0C:
    {
        // RRC H
        rotateRightCircular8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x0D:
    {
        // RRC L
        rotateRightCircular8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x0E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRightCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x0F:
    {
        // RRC A
        rotateRightCircular8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x11:
    {
        // RLC C
        rotateLeft8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x12:
    {
        // RLC D
        rotateLeft8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x13:
    {
        // RLC E
        rotateLeft8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x14:
    {
        // RLC H
        rotateLeft8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x15:
    {
        // RLC L
        rotateLeft8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x16:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeft8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x17:
    {
        // RLC A
        rotateLeft8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    case 0x18:
    {
        // RRC B
        rotateRight8b(reg, &reg->B);
        incrementPC(reg);
        break;
    }
    case 0x19:
    {
        // RRC C
        rotateRight8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x1A:
    {
        // RRC D
        rotateRight8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x1B:
    {
        // RRC E
        rotateRight8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x1C:
    {
        // RRC H
        rotateRight8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x1D:
    {
        // RRC L
        rotateRight8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x1E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRight8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x1F:
    {
        // RRC A
        rotateRight8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x21:
    {
        // SLA C
        shiftLeftArithmetic8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x22:
    {
        // SLA D
        shiftLeftArithmetic8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x23:
    {
        // SLA E
        shiftLeftArithmetic8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x24:
    {
        // SLA H
        shiftLeftArithmetic8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x25:
    {
        // SLA L
        shiftLeftArithmetic8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x26:
    {
        // SLA [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftLeftArithmetic8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x27:
    {
        // SLA A
        shiftLeftArithmetic8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    case 0x28:
    {
        // SRA B
        shiftRightArithmetic8b(reg, &reg->B);
        incrementPC(reg);
        break;
    }
    case 0x29:
    {
        // SRA C
        shiftRightArithmetic8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x2A:
    {
        // SRA D
        shiftRightArithmetic8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x2B:
    {
        // SRA E
        shiftRightArithmetic8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x2C:
    {
        // SRA H
        shiftRightArithmetic8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x2D:
    {
        // SRA L
        shiftRightArithmetic8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x2E:
    {
        // SRA [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftRightArithmetic8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x2F:
    {
        // SRA A
        shiftRightArithmetic8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x31:
    {
        // SWAP C
        swap8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x32:
    {
        // SWAP D
        swap8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x33:
    {
        // SWAP E
        swap8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x34:
    {
        // SWAP H
        swap8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x35:
    {
        // SWAP L
        swap8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x36:
    {
        // SWAP [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        swap8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x37:
    {
        // SWAP A
        swap8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    case 0x38:
    {
        // SRL B
        shiftRightLogical8b(reg, &reg->B);
        incrementPC(reg);
        break;
    }
    case 0x39:
    {
        // SRL C
        shiftRightLogical8b(reg, &reg->C);
        incrementPC(reg);
        break;
    }
    case 0x3A:
    {
        // SRL D
        shiftRightLogical8b(reg, &reg->D);
        incrementPC(reg);
        break;
    }
    case 0x3B:
    {
        // SRL E
        shiftRightLogical8b(reg, &reg->E);
        incrementPC(reg);
        break;
    }
    case 0x3C:
    {
        // SRL H
        shiftRightLogical8b(reg, &reg->H);
        incrementPC(reg);
        break;
    }
    case 0x3D:
    {
        // SRL L
        shiftRightLogical8b(reg, &reg->L);
        incrementPC(reg);
        break;
    }
    case 0x3E:
    {
        // SRL [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        shiftRightLogical8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x3F:
    {
        // SRL A
        shiftRightLogical8b(reg, &reg->A);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x41:
    {
        // BIT 0, C
        checkBit(reg, &reg->C, 0);
        incrementPC(reg);
        break;
    }
    case 0x42:
    {
        // BIT 0, D
        checkBit(reg, &reg->D, 0);
        incrementPC(reg);
        break;
    }
    case 0x43:
    {
        // BIT 0, E
        checkBit(reg, &reg->E, 0);
        incrementPC(reg);
        break;
    }
    case 0x44:
    {
        // BIT 0, H
        checkBit(reg, &reg->H, 0);
        incrementPC(reg);
        break;
    }
    case 0x45:
    {
        // BIT 0, L
        checkBit(reg, &reg->L, 0);
        incrementPC(reg);
        break;
    }
    case 0x46:
    {
        // BIT 0, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 0);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x47:
    {
        // BIT 0, A
        checkBit(reg, &reg->A, 0);
        incrementPC(reg);
        break;
    }
    case 0x48:
    {
        // BIT 1, B
        checkBit(reg, &reg->B, 1);
        incrementPC(reg);
        break;
    }
    case 0x49:
    {
        // BIT 1, C
        checkBit(reg, &reg->C, 1);
        incrementPC(reg);
        break;
    }
    case 0x4A:
    {
        // BIT 1, D
        checkBit(reg, &reg->D, 1);
        incrementPC(reg);
        break;
    }
    case 0x4B:
    {
        // BIT 1, E
        checkBit(reg, &reg->E, 1);
        incrementPC(reg);
        break;
    }
    case 0x4C:
    {
        // BIT 1, H
        checkBit(reg, &reg->H, 1);
        incrementPC(reg);
        break;
    }
    case 0x4D:
    {
        // BIT 1, L
        checkBit(reg, &reg->L, 1);
        incrementPC(reg);
        break;
    }
    case 0x4E:
    {
        // BIT 1, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 1);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x4F:
    {
        // BIT 1, A
        checkBit(reg, &reg->A, 1);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x51:
    {
        // BIT 2, C
        checkBit(reg, &reg->C, 2);
        incrementPC(reg);
        break;
    }
    case 0x52:
    {
        // BIT 2, D
        checkBit(reg, &reg->D, 2);
        incrementPC(reg);
        break;
    }
    case 0x53:
    {
        // BIT 2, E
        checkBit(reg, &reg->E, 2);
        incrementPC(reg);
        break;
    }
    case 0x54:
    {
        // BIT 2, H
        checkBit(reg, &reg->H, 2);
        incrementPC(reg);
        break;
    }
    case 0x55:
    {
        // BIT 2, L
        checkBit(reg, &reg->L, 2);
        incrementPC(reg);
        break;
    }
    case 0x56:
    {
        // BIT 2, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 2);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x57:
    {
        // BIT 2, A
        checkBit(reg, &reg->A, 2);
        incrementPC(reg);
        break;
    }
    case 0x58:
    {
        // BIT 3, B
        checkBit(reg, &reg->B, 3);
        incrementPC(reg);
        break;
    }
    case 0x59:
    {
        // BIT 3, C
        checkBit(reg, &reg->C, 3);
        incrementPC(reg);
        break;
    }
    case 0x5A:
    {
        // BIT 3, D
        checkBit(reg, &reg->D, 3);
        incrementPC(reg);
        break;
    }
    case 0x5B:
    {
        // BIT 3, E
        checkBit(reg, &reg->E, 3);
        incrementPC(reg);
        break;
    }
    case 0x5C:
    {
        // BIT 3, H
        checkBit(reg, &reg->H, 3);
        incrementPC(reg);
        break;
    }
    case 0x5D:
    {
        // BIT 3, L
        checkBit(reg, &reg->L, 3);
        incrementPC(reg);
        break;
    }
    case 0x5E:
    {
        // BIT 3, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 3);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x5F:
    {
        // BIT 3, A
        checkBit(reg, &reg->A, 3);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x61:
    {
        // BIT 4, C
        checkBit(reg, &reg->C, 4);
        incrementPC(reg);
        break;
    }
    case 0x62:
    {
        // BIT 4, D
        checkBit(reg, &reg->D, 4);
        incrementPC(reg);
        break;
    }
    case 0x63:
    {
        // BIT 4, E
        checkBit(reg, &reg->E, 4);
        incrementPC(reg);
        break;
    }
    case 0x64:
    {
        // BIT 4, H
        checkBit(reg, &reg->H, 4);
        incrementPC(reg);
        break;
    }
    case 0x65:
    {
        // BIT 4, L
        checkBit(reg, &reg->L, 4);
        incrementPC(reg);
        break;
    }
    case 0x66:
    {
        // BIT 4, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 4);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x67:
    {
        // BIT 4, A
        checkBit(reg, &reg->A, 4);
        incrementPC(reg);
        break;
    }
    case 0x68:
    {
        // BIT 5, B
        checkBit(reg, &reg->B, 5);
        incrementPC(reg);
        break;
    }
    case 0x69:
    {
        // BIT 5, C
        checkBit(reg, &reg->C, 5);
        incrementPC(reg);
        break;
    }
    case 0x6A:
    {
        // BIT 5, D
        checkBit(reg, &reg->D, 5);
        incrementPC(reg);
        break;
    }
    case 0x6B:
    {
        // BIT 5, E
        checkBit(reg, &reg->E, 5);
        incrementPC(reg);
        break;
    }
    case 0x6C:
    {
        // BIT 5, H
        checkBit(reg, &reg->H, 5);
        incrementPC(reg);
        break;
    }
    case 0x6D:
    {
        // BIT 5, L
        checkBit(reg, &reg->L, 5);
        incrementPC(reg);
        break;
    }
    case 0x6E:
    {
        // BIT 5, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 5);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x6F:
    {
        // BIT 5, A
        checkBit(reg, &reg->A, 5);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
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
        incrementPC(reg);
        break;
    }
    case 0x71:
    {
        // BIT 6, C
        checkBit(reg, &reg->C, 6);
        incrementPC(reg);
        break;
    }
    case 0x72:
    {
        // BIT 6, D
        checkBit(reg, &reg->D, 6);
        incrementPC(reg);
        break;
    }
    case 0x73:
    {
        // BIT 6, E
        checkBit(reg, &reg->E, 6);
        incrementPC(reg);
        break;
    }
    case 0x74:
    {
        // BIT 6, H
        checkBit(reg, &reg->H, 6);
        incrementPC(reg);
        break;
    }
    case 0x75:
    {
        // BIT 6, L
        checkBit(reg, &reg->L, 6);
        incrementPC(reg);
        break;
    }
    case 0x76:
    {
        // BIT 6, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 6);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x77:
    {
        // BIT 6, A
        checkBit(reg, &reg->A, 6);
        incrementPC(reg);
        break;
    }
    case 0x78:
    {
        // BIT 7, B
        checkBit(reg, &reg->B, 7);
        incrementPC(reg);
        break;
    }
    case 0x79:
    {
        // BIT 7, C
        checkBit(reg, &reg->C, 7);
        incrementPC(reg);
        break;
    }
    case 0x7A:
    {
        // BIT 7, D
        checkBit(reg, &reg->D, 7);
        incrementPC(reg);
        break;
    }
    case 0x7B:
    {
        // BIT 7, E
        checkBit(reg, &reg->E, 7);
        incrementPC(reg);
        break;
    }
    case 0x7C:
    {
        // BIT 7, H
        checkBit(reg, &reg->H, 7);
        incrementPC(reg);
        break;
    }
    case 0x7D:
    {
        // BIT 7, L
        checkBit(reg, &reg->L, 7);
        incrementPC(reg);
        break;
    }
    case 0x7E:
    {
        // BIT 7, [HL]
        uint8_t memVal = memoryRead(mem, reg->HL);
        checkBit(reg, &memVal, 7);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
        break;
    }
    case 0x7F:
    {
        // BIT 7, A
        checkBit(reg, &reg->A, 7);
        incrementPC(reg);
        break;
    }
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp8(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp9(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpA(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpB(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpC(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpD(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpE(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xpF(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}

void execPrefix(Register *reg, Memory *mem)
{
    uint8_t opcode = mem->ram[reg->PC];
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
        incrementPC(reg);
        break;
    }
}