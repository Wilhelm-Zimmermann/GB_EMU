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
    }
    case 0x01:
    {
        // RLC C
        rotateLeftCircular8b(reg, &reg->C);
        incrementPC(reg);
    }
    case 0x02:
    {
        // RLC D
        rotateLeftCircular8b(reg, &reg->D);
        incrementPC(reg);
    }
    case 0x03:
    {
        // RLC E
        rotateLeftCircular8b(reg, &reg->E);
        incrementPC(reg);
    }
    case 0x04:
    {
        // RLC H
        rotateLeftCircular8b(reg, &reg->H);
        incrementPC(reg);
    }
    case 0x05:
    {
        // RLC L
        rotateLeftCircular8b(reg, &reg->L);
        incrementPC(reg);
    }
    case 0x06:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeftCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
    }
    case 0x07:
    {
        // RLC A
        rotateLeftCircular8b(reg, &reg->A);
        incrementPC(reg);
    }
    case 0x08:
    {
        // RRC B
        rotateRightCircular8b(reg, &reg->B);
        incrementPC(reg);
    }
    case 0x09:
    {
        // RRC C
        rotateRightCircular8b(reg, &reg->C);
        incrementPC(reg);
    }
    case 0x0A:
    {
        // RRC D
        rotateRightCircular8b(reg, &reg->D);
        incrementPC(reg);
    }
    case 0x0B:
    {
        // RRC E
        rotateRightCircular8b(reg, &reg->E);
        incrementPC(reg);
    }
    case 0x0C:
    {
        // RRC H
        rotateRightCircular8b(reg, &reg->H);
        incrementPC(reg);
    }
    case 0x0D:
    {
        // RRC L
        rotateRightCircular8b(reg, &reg->L);
        incrementPC(reg);
    }
    case 0x0E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRightCircular8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
    }
    case 0x0F:
    {
        // RRC A
        rotateRightCircular8b(reg, &reg->A);
        incrementPC(reg);
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
    }
    case 0x11:
    {
        // RLC C
        rotateLeft8b(reg, &reg->C);
        incrementPC(reg);
    }
    case 0x12:
    {
        // RLC D
        rotateLeft8b(reg, &reg->D);
        incrementPC(reg);
    }
    case 0x13:
    {
        // RLC E
        rotateLeft8b(reg, &reg->E);
        incrementPC(reg);
    }
    case 0x14:
    {
        // RLC H
        rotateLeft8b(reg, &reg->H);
        incrementPC(reg);
    }
    case 0x15:
    {
        // RLC L
        rotateLeft8b(reg, &reg->L);
        incrementPC(reg);
    }
    case 0x16:
    {
        // RLC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateLeft8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
    }
    case 0x17:
    {
        // RLC A
        rotateLeft8b(reg, &reg->A);
        incrementPC(reg);
    }
    case 0x18:
    {
        // RRC B
        rotateRight8b(reg, &reg->B);
        incrementPC(reg);
    }
    case 0x19:
    {
        // RRC C
        rotateRight8b(reg, &reg->C);
        incrementPC(reg);
    }
    case 0x1A:
    {
        // RRC D
        rotateRight8b(reg, &reg->D);
        incrementPC(reg);
    }
    case 0x1B:
    {
        // RRC E
        rotateRight8b(reg, &reg->E);
        incrementPC(reg);
    }
    case 0x1C:
    {
        // RRC H
        rotateRight8b(reg, &reg->H);
        incrementPC(reg);
    }
    case 0x1D:
    {
        // RRC L
        rotateRight8b(reg, &reg->L);
        incrementPC(reg);
    }
    case 0x1E:
    {
        // RRC HL
        uint8_t memVal = memoryRead(mem, reg->HL);
        rotateRight8b(reg, &memVal);
        memoryWrite(mem, reg->HL, memVal);
        incrementPC(reg);
    }
    case 0x1F:
    {
        // RRC A
        rotateRight8b(reg, &reg->A);
        incrementPC(reg);
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
    default:
        incrementPC(reg);
        break;
    }
}
void opcode_xp3(Register *reg, Memory *mem, uint8_t opcode)
{
    switch (opcode)
    {
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