#pragma once
#include <stdint.h>

typedef struct
{
    union
    {
        struct
        {
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

    union
    {
        struct
        {
            uint8_t C;
            uint8_t B;
        };
        uint16_t BC;
    };

    union
    {
        struct
        {
            uint8_t E;
            uint8_t D;
        };
        uint16_t DE;
    };

    union
    {
        struct
        {
            uint8_t L;
            uint8_t H;
        };
        uint16_t HL;
    };

    uint16_t SP; // Stack Pointer
    uint16_t PC; // Program Counter
} Register;

void initialize(Register *reg);
void incrementPC(Register *reg);

uint8_t get_CFlag(Register *reg);
uint8_t get_ZFlag(Register *reg);
uint8_t get_NFlag(Register *reg);
uint8_t get_HFlag(Register *reg);

void set_ZFlag(Register *reg);
void set_CFlag(Register *reg);
void set_NFlag(Register *reg);
void set_HFlag(Register *reg);

void unset_ZFlag(Register *reg);
void unset_CFlag(Register *reg);
void unset_NFlag(Register *reg);
void unset_HFlag(Register *reg);

void checkIfHasCarryIncAndSetH8b(Register *reg, uint8_t value);
void checkIfHasCarryAddAndSetH8b(Register *reg, uint8_t value);
void checkIfHasCarryAndSetH16b(Register *reg, uint16_t value);

void checkIfOpZeroAndSetZ(Register *reg, uint8_t value);

void setCFlagIfAddOpGtThanFF(Register *reg, uint16_t value);
void setCFlagIfAddOpGtThanFFFF(Register *reg, uint32_t value);

void checkIfLessThan0CarryAndSetC8b(Register *reg, uint8_t operand1, uint8_t operand2);
void checkIfSubHasCarryAndSetH8b(Register *reg, uint8_t operand1, uint8_t operand2);
