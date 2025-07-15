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
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp5(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp6(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp7(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
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