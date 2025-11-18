#include <stdlib.h>
#include "./headers/ppu.h"

int const VIDEO_SIZE = 160 * 144;

void initPPUVideo(PPU *ppu)
{
    ppu->video = calloc(VIDEO_SIZE, sizeof(uint32_t));
}

const uint32_t display_palette[4] = {
    0xE0F8D0FF, // Shade 0: White
    0x88C070FF, // Shade 1: Light Gray
    0x346856FF, // Shade 2: Dark Gray
    0x081820FF  // Shade 3: Black
};

uint8_t get_color(uint8_t color_id, uint8_t palette)
{
    // 3 == Black
    // 2 == Dark Gray
    // 1 == Light Gray
    // 0 == White
    return (palette >> (color_id * 2)) & 0x03;
}

uint32_t *merge_tile_line(uint8_t first, uint8_t second)
{
    uint32_t* tile_line = calloc(8, sizeof(uint32_t));
    for (int i = 7; i >= 0; i--)
    {
        uint8_t value = ((second >> i) & 2) | ((first >> i) & 1);
        tile_line[i] = value;
    }
    return tile_line;
}

static inline uint8_t get_ppu_mode(Memory *mem)
{
    return memoryRead(mem, 0xFF41) & 0x03;
}

void render(PPU *ppu, Memory *mem)
{
    int i = 0;
    while (i < VIDEO_SIZE)
    {
        uint8_t firstChunk = memoryRead(mem, 0x8000 + i);
        uint8_t secondChunk = memoryRead(mem, 0x8000 + i + 1);
        uint32_t *merge_result = merge_tile_line(firstChunk, secondChunk);

        for (int j = 0; j < 8; j++)
        {
            ppu->video[i + j] = display_palette[merge_result[j]];
        }
        free(merge_result);
        i += 8;
    }
}

// PPU = Picture Processing Unit
void ppuStep(PPU *ppu, Memory *mem, int cpu_cycles)
{
    render(ppu, mem);
}