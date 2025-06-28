#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "./src/headers/memory.h"
#include "./src/headers/rom.h"

#define DEBUG

int main(int argc, char *args[])
{
    // if (argc < 2)
    // {
    //     printf("Usage: %s <ROM file>\n", args[0]);
    //     return 1;
    // }
    Memory *mem = malloc(sizeof(Memory));
    ROM *rom = malloc(sizeof(ROM));

    initMemory(mem);
    loadRom(mem, "./ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb");
    printf("Program end successfully!!\n");
    return 0;
}