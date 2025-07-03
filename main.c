#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "./src/headers/memory.h"
#include "./src/headers/rom.h"
#include "./src/headers/cpu.h"

#define DEBUG

const int PIXEL_SCALE = 2;

void printSdlError(const char *message)
{
    printf("%s: %s\n", message, SDL_GetError());
}

int main(int argc, char *args[])
{
    // if (argc < 2)
    // {
    //     printf("Usage: %s <ROM file>\n", args[0]);
    //     return 1;
    // }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printSdlError("SDL was not able to initialize");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(args[1], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * PIXEL_SCALE, 144 * PIXEL_SCALE, SDL_WINDOW_SHOWN);
    Memory *mem = malloc(sizeof(Memory));
    ROM *rom = malloc(sizeof(ROM));
    Register *reg = malloc(sizeof(Register));

    if (window == NULL)
    {
        printSdlError("Window could not be created");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);

    initMemory(mem);
// loadRom(mem, "../ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb");
// loadRom(mem, "./ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb");
// loadRom(mem, "./ROMS/Mortal Kombat (USA, Europe).gb");
#ifdef DEBUG
    loadRom(mem, "./ROMS/cpu_instrs.gb");
#endif

#ifndef DEBUG
    loadRom(mem, "../ROMS/cpu_instrs.gb");
#endif
    printf("Program end successfully!!\n");
    initRegisters(reg);
    SDL_Event e;
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = 1;
                }
            }
        }

        // SDL_UpdateTexture(texture, NULL, chip->display, 64 * sizeof(uint32_t));
        cpu_cycle(reg, mem);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        // SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(mem);
    free(rom);
    // free(cpu);
    return 0;
}