#include <stdlib.h>
#include <stdio.h>
#include "rom.h"

#define DEBUG

// If i forget something about ROM; https://gbdev.io/pandocs/The_Cartridge_Header.html
void load_rom(Memory *mem, const char *fileName)
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
    mem->romSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    mem->fullRom = calloc(mem->romSize, sizeof(uint8_t));
    if (mem->fullRom == NULL)
    {
        fprintf(stderr, "Memory allocation for buffer failed\n");
        fclose(file);
        return;
    }

    fread(mem->fullRom, 1, mem->romSize, file);
    fclose(file);
    mem->romBank0 = mem->fullRom;
    mem->romBankN = mem->fullRom + 0x4000;

    uint8_t mbcType = mem->fullRom[0x0147];
    uint8_t romSizeCode = mem->fullRom[0x0148];
    uint8_t ramSizeCode = mem->fullRom[0x0149];

    printf("MBC Type: 0x%02X\n", mbcType);
    printf("ROM Size Code: 0x%02X\n", romSizeCode);
    printf("RAM Size Code: 0x%02X\n", ramSizeCode);

    // take the number "1" and shift by 0x148 position value, and then multiply by 32KB, this is a beautiful way to getting the ROM size lol!
    long romSize = (1024 * 32) * (1 << mem->fullRom[0x0148]);
    printf("ROM size %ldKB\n", romSize / 1024);

    // Fill the video ram with current map
    if (mem->fullRom[0x0149] == 0x02)
    {
        // make this work
        printf("Allocating additinal RAM. 8KiB\n");
    }

    printf("ROM has been loaded. Enjoy your game!!\n");
}