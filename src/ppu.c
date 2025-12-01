#include <stdio.h>
#include <stdlib.h>
#include "./headers/ppu.h"

int const VIDEO_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

void init_ppu(PPU *ppu)
{
    ppu->video = calloc(VIDEO_SIZE, sizeof(uint32_t));
    ppu->cycle_counter = 0;
    ppu->mode = 0;
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

static inline uint8_t get_ppu_mode(Memory *mem)
{
    // get ppu mode
    // 0 - horizontal blank
    // 1 - vertical blank
    // 2 - OAM scan
    // 3 - drawing pixels
    // 0x03 in binary is 00000011
    return memory_read(mem, 0xFF41) & 0x03;
}

// update ppu mode
void update_ppu_mode(PPU *ppu, Memory *mem)
{
    uint8_t status = memory_read(mem, 0xFF41);

    memory_write(mem, 0xFF41, (status & 0xFC) | (ppu->mode & 0x03));
}

void refresh_lcdc_flags(PPU *ppu, Memory *mem)
{
    uint8_t lcdc = memory_read(mem, 0xFF40);
    ppu->lcdc = lcdc;
}

int handle_lcdc_blank(PPU *ppu, Memory *mem)
{
    uint8_t bg_window_enable = ppu->lcdc & 1; // get the rightmost bit.

    if (!bg_window_enable)
    {
        for (int i = 0; i < VIDEO_SIZE; i++)
        {
            ppu->video[i] = 0xFFFFFFFF; // put white on every place; just because i want.
        }
        ppu->mode = 0;
        ppu->cycle_counter = 0;
        return 1;
    }
    return 0;
}

void render(PPU *ppu, Memory *mem)
{
    uint8_t lcdc = ppu->lcdc;
    uint8_t bg_window_flag = (lcdc >> 4) & 1;
    uint8_t tile_map_flag = (lcdc >> 6) & 1;

    int lcdc_window_blank_status = handle_lcdc_blank(ppu, mem);
    if (lcdc_window_blank_status)
        return;

    // LCDC flags: https://gbdev.io/pandocs/LCDC.html
    // object always use 8000 addr as base; if bg_window_flag = 1 0x8000 else 0x8800
    uint16_t tile_data_addr = bg_window_flag ? 0x8000 : 0x8800;
    // tile map -> 0x9800 to 0x9bff and 0x9c00 to 9fff
    uint16_t tile_map_addr = tile_map_flag ? 0x9800 : 0x9c00;
}

// PPU = Picture Processing Unit
void ppu_step(PPU *ppu, Memory *mem, int cpu_cycles)
{
    refresh_lcdc_flags(ppu, mem);
    // TODO: only for test the below asignment; remove after;

    printf("PPU mode: %d\n", ppu->mode);
    switch (ppu->mode)
    {
    case 2:
        // OAM Scan
        if (ppu->cycle_counter >= 80)
        {
            ppu->mode = 3;
            update_ppu_mode(ppu, mem);
        }
        break;
    case 3:
        // Drawing pixels
        if (ppu->cycle_counter >= 252)
        {
            ppu->mode = 0;
            update_ppu_mode(ppu, mem);
            render(ppu, mem);
        }
        break;
    case 0:
        // Horizontal blank;
        if (ppu->cycle_counter >= 80)
        {
            ppu->mode = 1;
            update_ppu_mode(ppu, mem);
        }
        break;
    case 1:
        // Vertical blank;
        if (ppu->cycle_counter >= 80)
        {
            ppu->mode = 2;
            update_ppu_mode(ppu, mem);
        }
        break;
    default:
        break;
    }
    ppu->cycle_counter += cpu_cycles;
}