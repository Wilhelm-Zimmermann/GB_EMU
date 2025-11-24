#pragma once
#include "./register.h"
#include "./memory.h"

// printf("PC: %04X | Opcode: %02X | AF: %04X | BC: %04X | DE: %04X | HL: %04X | SP: %04X\n",
//        pc_before, opcode, reg->AF, reg->BC, reg->DE, reg->HL, reg->SP);

void write_cpu_logs(Register *reg, Memory *mem, uint16_t pcAddr, uint8_t opcode);