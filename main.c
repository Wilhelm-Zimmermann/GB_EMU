#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "./src/headers/memory.h"
#include "./src/headers/rom.h"
#include "./src/headers/cpu.h"
#include "./src/headers/ppu.h"

// #define DEBUG

const int PIXEL_SCALE = 6;
const int CYCLES_PER_FRAME = 70224;

void print_sdl_error(const char *message)
{
    printf("%s: %s\n", message, SDL_GetError());
}

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        printf("Usage: %s <ROM file>\n", args[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_sdl_error("SDL was not able to initialize");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(args[1], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * PIXEL_SCALE, 144 * PIXEL_SCALE, SDL_WINDOW_SHOWN);
    Memory *mem = calloc(1, sizeof(Memory));
    ROM *rom = calloc(1, sizeof(ROM));
    Register *reg = calloc(1, sizeof(Register));
    PPU *ppu = calloc(1, sizeof(PPU));

    if (window == NULL)
    {
        print_sdl_error("Window could not be created");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160 , 144);

    init_memory(mem);
    init_ppu(ppu);
    init_registers(reg);

    load_rom(mem, args[1]);
    SDL_Event e;
    int quit = 0;

    while (!quit)
    {
        int frame_cycles = 0;
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
        while (frame_cycles <= CYCLES_PER_FRAME)
        {
            int cycles = cpu_cycle(reg, mem);
            ppu_step(ppu, mem, cycles);
            frame_cycles += cycles;
        }

        SDL_UpdateTexture(texture, NULL, ppu->video, 160 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free_memory(mem);
    if (rom != NULL)
        free(rom);
    if (reg != NULL)
        free(reg);
    return 0;
}