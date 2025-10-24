#include "./headers/ppu.h"

uint8_t get_color(uint8_t color_id, uint8_t palette)
{
    // 3 == Black
    // 2 == Dark Gray
    // 1 == Light Gray
    // 0 == White
    return (palette >> (color_id * 2)) & 0x03;
}

static inline uint8_t get_ppu_mode(Memory *mem) {
    return memoryRead(mem, 0xFF41) & 0x03;
}

void render() 
{

}

// PPU = Picture Processing Unit
void ppuStep(PPU* ppu, Memory *mem, int cpu_cycles)
{

}