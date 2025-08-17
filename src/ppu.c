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

void ppuStep(PPU* ppu, Memory *mem, int cpu_cycles)
{
    if (!(ppu->lcdc & 0x80))
    {
        ppu->modeClock = 0;
        ppu->ly = 0;

        ppu->stat = (ppu->stat & 0b11111100);
        return;
    }

    ppu->modeClock += cpu_cycles;

    uint8_t current_mode = ppu->stat & 0x03;

    switch (current_mode)
    {
    case 2:
        if (ppu->modeClock >= 80)
        {
            ppu->modeClock -= 80;
            ppu->stat = (ppu->stat & 0b11111100) | 3;
        }
        break;
    case 3:
        if (ppu->modeClock >= 172)
        {
            ppu->modeClock -= 172;
            ppu->stat = (ppu->stat & 0b11111100) | 0;
            render();
        }
        break;
    case 0:
        if (ppu->modeClock >= 204)
        {
            ppu->modeClock -= 204;
            ppu->ly++;

            if (ppu->ly == 144)
            {
                ppu->stat = (ppu->stat & 0b11111100) | 1;
                // TODO: Request V-Blank Interrupt (Set bit 0 of IF register $FF0F)
            }
            else
            {
                ppu->stat = (ppu->stat & 0b11111100) | 2;
            }
        }
        break;
    case 1:
        if (ppu->modeClock >= 456)
        {
            ppu->modeClock -= 456;
            ppu->ly++;

            if (ppu->ly > 153)
            {
                ppu->ly = 0;
                ppu->stat = (ppu->stat & 0b11111100) | 2;
            }
        }
        break;
    }

    if (ppu->ly == ppu->lyc)
    {
        ppu->stat |= (1 << 2);
        if (ppu->stat & (1 << 6))
        {
            // TODO: Request STAT Interrupt (Set bit 1 of IF register $FF0F)
        }
    }
    else
    {
        ppu->stat &= ~(1 << 2);
    }
}