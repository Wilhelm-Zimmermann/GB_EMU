#include <stdlib.h>
#include <stdio.h>
#include "rom.h"

#define DEBUG

// If i forget something about ROM; https://gbdev.io/pandocs/The_Cartridge_Header.html
void loadRom(Memory *mem, const char *fileName)
{
#ifdef DEBUG
    printf("Reading ROM file...\n");
#endif
    FILE *file = fopen(fileName, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the file\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation for buffer failed\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, size, file);
    fclose(file);
    for (long i = 0; i < size; i++)
    {
        mem->ram[i] = buffer[i];
    }
    
    for (int i = 0; i < mem->vRamSize; i++)
    {
        mem->vRam[i] = buffer[0x8000 + i];
    }
    // take the number "1" and shift by 0x148 position value, and then multiply by 32KB, this is a beautiful way to getting the ROM size lol!
    long romSize = (1024 * 32) * (1 << buffer[0x0148]);
    printf("ROM size %ldKB\n", romSize / 1024);

    if (buffer[0x0149] == 0x02)
    {
        printf("Allocating additinal RAM. 8KiB\n");
    }

    free(buffer);
    printf("ROM has been loaded. Enjoy your game!!\n");
}