#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t lcdc; 
    uint8_t stat; 
    uint8_t scy;  
    uint8_t scx;  
    uint8_t ly;   
    uint8_t lyc;  
    uint8_t bgp;  
    uint8_t obp0; 
    uint8_t obp1; 
    uint8_t wy;   
    uint8_t wx;   

    int modeClock;
} PPU;

void ppu_init();
void ppu_step(int cpuCycles);