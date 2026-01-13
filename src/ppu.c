#include <stdio.h>
#include <stdlib.h>
#include "./headers/ppu.h"

int const VIDEO_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

void init_ppu(PPU *ppu)
{
    ppu->video = calloc(VIDEO_SIZE, sizeof(uint32_t));
    ppu->dot_clock = 0;
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

void check_lyc(Memory *mem)
{
    uint8_t ly = memory_read(mem, 0xFF44);
    uint8_t lyc = memory_read(mem, 0xFF45);
    uint8_t stat = memory_read(mem, 0xFF41);

    if (ly == lyc)
    {
        stat |= STAT_LYC_FLAG;

        if (stat & STAT_LYC_INT)
        {
            uint8_t if_reg = memory_read(mem, 0xFF0F);
            memory_write(mem, 0xFF0F, if_reg | IF_STAT_BIT);
        }
    }
    else
    {
        stat &= ~STAT_LYC_FLAG;
    }

    memory_write(mem, 0xFF41, stat);
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
    uint8_t bg_window_enable = (ppu->lcdc >> 7) & 1; // get the rightmost bit.

    if (!bg_window_enable)
    {
        // for (int i = 0; i < VIDEO_SIZE; i++)
        // {
        //     ppu->video[i] = 0xFFFFFFFF; // put white on every place; just because i want.
        // }
        ppu->mode = 0;
        ppu->dot_clock = 0;
        return 1;
    }
    return 0;
}

void render_sprites(PPU *ppu, Memory *mem)
{

    if (!(ppu->lcdc & 0x02))
        return;

    int sprite_height = 8;

    for (int i = 0; i < 40; i++)
    {
        uint16_t sprite_addr = 0xFE00 + (i * 4);

        int16_t sprite_y = memory_read(mem, sprite_addr) - 16;
        int16_t sprite_x = memory_read(mem, sprite_addr + 1) - 8;
        uint8_t tile_id = memory_read(mem, sprite_addr + 2);
        uint8_t attributes = memory_read(mem, sprite_addr + 3);

        int ly = memory_read(mem, 0xFF44);

        if (ly >= sprite_y && ly < (sprite_y + sprite_height))
        {

            int line = ly - sprite_y;

            if (attributes & 0x40)
            {
                line = sprite_height - 1 - line;
            }

            uint16_t tile_data_addr = 0x8000 + (tile_id * 16) + (line * 2);
            uint8_t b1 = memory_read(mem, tile_data_addr);
            uint8_t b2 = memory_read(mem, tile_data_addr + 1);

            for (int x = 0; x < 8; x++)
            {

                int pixel_x_screen = sprite_x + x;

                if (pixel_x_screen < 0 || pixel_x_screen >= 160)
                    continue;

                int bit_index = x;
                if (!(attributes & 0x20))
                {
                    bit_index = 7 - x;
                }

                uint8_t color_bit_low = (b1 >> bit_index) & 1;
                uint8_t color_bit_high = (b2 >> bit_index) & 1;
                uint8_t color_id = (color_bit_high << 1) | color_bit_low;

                if (color_id == 0)
                    continue;

                uint16_t palette_addr = (attributes & 0x10) ? 0xFF49 : 0xFF48;
                uint8_t palette = memory_read(mem, palette_addr);

                ppu->video[ly * 160 + pixel_x_screen] = display_palette[get_color(color_id, palette)];
            }
        }
    }
}

void render(PPU *ppu, Memory *mem)
{
    uint8_t lcdc = ppu->lcdc;

    uint8_t bg_window_enable = lcdc & 1;

    uint8_t bg_tile_map_select = (lcdc >> 3) & 1;
    uint8_t window_tile_map_select = (lcdc >> 6) & 1;
    uint8_t window_enable = (lcdc >> 5) & 1;
    uint8_t tile_data_select = (lcdc >> 4) & 1;

    uint8_t scx = memory_read(mem, 0xFF43);
    uint8_t scy = memory_read(mem, 0xFF42);
    uint8_t wx = memory_read(mem, 0xFF4B);
    uint8_t wy = memory_read(mem, 0xFF4A);
    int ly = memory_read(mem, 0xFF44);

    int lcdc_window_blank_status = handle_lcdc_blank(ppu, mem);
    if (lcdc_window_blank_status)
        return;

    uint16_t bg_map_base = bg_tile_map_select ? 0x9C00 : 0x9800;
    uint16_t win_map_base = window_tile_map_select ? 0x9C00 : 0x9800;
    uint16_t tile_data_base = tile_data_select ? 0x8000 : 0x9000;

    int window_line_counter = 0;

    for (int pixel_x = 0; pixel_x < 160; pixel_x++)
    {
        // & 0xFF is the same as %256 but faster
        // uint8_t map_x = (x + scx) & 0xFF
        if (!bg_window_enable)
        {
            ppu->video[ly * 160 + pixel_x] = display_palette[0]; // Branco
            continue;
        }
        int using_window = 0;

        if (window_enable && (ly >= wy) && (pixel_x >= wx - 7))
        {
            using_window = 1;
        }

        uint8_t x_pos;
        uint8_t y_pos;
        uint16_t current_map_base;

        if (using_window)
        {
            x_pos = pixel_x - (wx - 7);
            y_pos = ly - wy;
            current_map_base = win_map_base;
        }
        else
        {

            x_pos = (pixel_x + scx) & 0xFF;
            y_pos = (ly + scy) & 0xFF;
            current_map_base = bg_map_base;
        }

        uint8_t col = x_pos / 8;
        uint8_t row = y_pos / 8;

        uint16_t address = current_map_base + (row * 32) + col;
        uint8_t tile_id = memory_read(mem, address);

        uint16_t tile_data_start_addr;
        if (tile_data_select)
        {
            tile_data_start_addr = 0x8000 + (tile_id * 16);
        }
        else
        {
            tile_data_start_addr = 0x9000 + ((int8_t)tile_id * 16);
        }

        uint8_t internal_line = y_pos % 8;
        uint16_t current_line_addr = tile_data_start_addr + (internal_line * 2);

        uint8_t tile_byte_1 = memory_read(mem, current_line_addr);
        uint8_t tile_byte_2 = memory_read(mem, current_line_addr + 1);

        uint8_t pixel_num = x_pos % 8;
        uint8_t bit_to_check = 7 - pixel_num;

        uint8_t bit_low = (tile_byte_1 >> bit_to_check) & 1;
        uint8_t bit_high = (tile_byte_2 >> bit_to_check) & 1;

        uint8_t color_id = (bit_high << 1) | bit_low;
        uint8_t palette = memory_read(mem, 0xFF47);

        ppu->video[ly * 160 + pixel_x] = display_palette[get_color(color_id, palette)];
    }
    render_sprites(ppu, mem);
}

// PPU = Picture Processing Unit
void ppu_step(PPU *ppu, Memory *mem, int cpu_cycles)
{
    refresh_lcdc_flags(ppu, mem);
    // TODO: only for test the below asignment; remove after;
    ppu->dot_clock += cpu_cycles;
    // printf("PPU MODE: %d\n", ppu->mode);
    switch (ppu->mode)
    {
    case 2:
        // OAM Scan
        if (ppu->dot_clock >= 80)
        {
            ppu->mode = 3;
            update_ppu_mode(ppu, mem);
        }
        break;
    case 3:
        // Drawing pixels
        if (ppu->dot_clock >= 252)
        {
            ppu->mode = 0;
            update_ppu_mode(ppu, mem);
            render(ppu, mem);
        }
        break;
    case 0:
        // Horizontal blank;
        if (ppu->dot_clock >= TICKS_PER_LINE)
        {
            // ppu->dot_clock = 0;
            ppu->dot_clock -= TICKS_PER_LINE;
            int ly = memory_read(mem, 0xFF44);
            ly++;

            memory_write(mem, 0xFF44, ly);
            check_lyc(mem);

            if (ly == LY_MAX_LINE)
            {
                ppu->mode = 1;
                uint8_t if_reg = memory_read(mem, 0xFF0F);
                memory_write(mem, 0xFF0F, if_reg | 0x01);
            }
            else
            {
                ppu->mode = 2;
            }
            update_ppu_mode(ppu, mem);
        }
        break;
    case 1:
        // Vertical blank;
        if (ppu->dot_clock >= TICKS_PER_LINE)
        {
            // ppu->dot_clock = 0;
            ppu->dot_clock -= TICKS_PER_LINE;
            int ly = memory_read(mem, 0xFF44);
            ly++;
            if (ly > V_BLANK_LY_MAX)
            {
                ppu->mode = 2;
                ly = 0;
            }
            memory_write(mem, 0xFF44, ly);
            check_lyc(mem);
            update_ppu_mode(ppu, mem);
        }
        break;
    default:
        break;
    }
}