#include <stdlib.h>
#include <stdio.h>
#include "rom.h"

#define DEBUG

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

    printf("File size %ldKB\n", size / 1024);
    fread(buffer, 1, size, file);
    fclose(file);
    for (long i = 0; i < size; i++)
    {
        mem->memory[i] = buffer[i];
    }

    free(buffer);
    printf("ROM has been loaded. Enjoy your game!!\n");
}