#include <stdlib.h>
#include "./headers/ppu.h"

int const VIDEO_SIZE = 160 * 144;

void init_ppu_video(PPU *ppu)
{
    ppu->video = calloc(VIDEO_SIZE, sizeof(uint32_t));
    ppu->cycle_counter = 0;
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
    // these lines will not work
    uint32_t *tile_line = calloc(8, sizeof(uint32_t));
    for (int i = 7; i >= 0; i--)
    {
        uint8_t value = ((second >> i) & 2) | ((first >> i) & 1);
        tile_line[i] = value;
    }
    return tile_line;
}

static inline uint8_t get_ppu_mode(Memory *mem)
{
    // get ppu mode
    // 0 - horizontal blank
    // 1 - vertical blank
    // 2 - OAM scan
    // 3 - drawing pixels
    return memory_read(mem, 0xFF41) & 0x03;
}

int handle_lcdc_blank(PPU *ppu, Memory *mem)
{
    uint8_t lcdc = memory_read(mem, 0xFF40);
    uint8_t bg_window_enable = lcdc & 1; // get the rightmost bit.

    if (!bg_window_enable)
    {
        for(int i = 0; i < VIDEO_SIZE; i++) {
            ppu->video[i] = 0xFFFFFFFF; // put white on every place; just because i want.
        }
        return 1;
    }
    return 0;
}

void render(PPU *ppu, Memory *mem)
{
    int lcdc_window_blank_status = handle_lcdc_blank(ppu, mem);
    if(lcdc_window_blank_status) return;

    int i = 0;
    // it does not work yet

}

// PPU = Picture Processing Unit
void ppu_step(PPU *ppu, Memory *mem, int cpu_cycles)
{
    render(ppu, mem);
}