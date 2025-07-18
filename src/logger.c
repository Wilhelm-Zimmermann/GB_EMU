#include <stdio.h>
#include <stdlib.h>
#include "./headers/logger.h"

void writeCPULogs(Register *reg, Memory *mem, uint16_t pcAddr, uint8_t opcode)
{
    FILE *filePointer;
    char *fileName = "../log.txt";

    filePointer = fopen(fileName, "a");

    if (filePointer == NULL)
    {
        fprintf(stderr, "Error: Could not open the file '%s'.\n", fileName);
        exit(1);
    }

    // fprintf(filePointer, "PC: %04X | Opcode: %02X | AF: %04X | BC: %04X | DE: %04X | HL: %04X | SP: %04X\n",
    //         pcAddr, opcode, reg->AF, reg->BC, reg->DE, reg->HL, reg->SP);
    uint8_t part1 = memoryRead(mem, reg->PC);
    uint8_t part2 = memoryRead(mem, reg->PC + 1);
    uint8_t part3 = memoryRead(mem, reg->PC + 2);
    uint8_t part4 = memoryRead(mem, reg->PC + 3);

    // char cFlag = get_CFlag(reg) ? 'C' : '-';
    // char hFlag = get_HFlag(reg) ? 'H' : '-';
    // char nFlag = get_NFlag(reg) ? 'N' : '-';
    // char ZFlag = get_ZFlag(reg) ? 'Z' : '-';

    fprintf(filePointer, "A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X PCMEM:%02X,%02X,%02X,%02X \n",
            reg->A,
            reg->F,
            reg->B,
            reg->C,
            reg->D,
            reg->E,
            reg->H,
            reg->L,
            reg->SP,
            reg->PC,
            part1,
            part2,
            part3,
            part4);
    fclose(filePointer);
}