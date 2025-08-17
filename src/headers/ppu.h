#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "./memory.h"

typedef struct
{
    uint8_t lcdc; // $FF40 LCD Control
    uint8_t stat; // $FF41 LCD Status
    uint8_t scy;  // $FF42 Scroll Y
    uint8_t scx;  // $FF43 Scroll X
    uint8_t ly;   // $FF44 LCD Y-Coordinate
    uint8_t lyc;  // $FF45 LY Compare
    uint8_t bgp;  // $FF47 BG Palette Data
    uint8_t obp0; // $FF48 Object Palette 0 Data
    uint8_t obp1; // $FF49 Object Palette 1 Data
    uint8_t wy;   // $FF4A Window Y Position
    uint8_t wx;   // $FF4B Window X Position - 7

    int modeClock;
} PPU;

void ppuInit();
void ppuStep(PPU *ppu, Memory *mem, int cpuCycles);