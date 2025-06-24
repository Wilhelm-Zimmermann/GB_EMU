#pragma once
#include <stdint.h>

typedef struct
{
    union {
        struct {
            // Lower byte
            // z -> zero flag - 7th bit
            // n -> subtraction flag (BCD) - 6th bit
            // h -> half carry flag (BCD) - 5th bit
            // c -> carry flag - 4th bit
            // Lower 4 bits are always 0
            uint8_t F;
            // Higher byte
            uint8_t A;
        };
        uint16_t AF;
    };

    union {
        struct {
            uint8_t C;
            uint8_t B;
        };
        uint16_t BC;
    };

    union {
        struct {
            uint8_t E;
            uint8_t D;
        };
        uint16_t DE;
    };

    union {
        struct {
            uint8_t L;
            uint8_t H;
        };
        uint16_t HL;
    };

    uint16_t SP; // Stack Pointer
    uint16_t PC; // Program Counter
} Register;


void initialize(Register* reg);