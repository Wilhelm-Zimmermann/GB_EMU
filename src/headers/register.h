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
    int IME;           
    int ime_scheduled;
    int halted;
    int stopped;
} Register;

void initialize(Register *reg);
void increment_pc(Register *reg);

uint8_t get_c_flag(Register *reg);
uint8_t get_z_flag(Register *reg);
uint8_t get_n_flag(Register *reg);
uint8_t get_h_flag(Register *reg);

void set_z_flag(Register *reg);
void set_c_flag(Register *reg);
void set_n_flag(Register *reg);
void set_HFlag(Register *reg);

void unset_z_flag(Register *reg);
void unset_c_flag(Register *reg);
void unset_n_flag(Register *reg);
void unset_h_flag(Register *reg);

void check_if_has_carry_and_set_8b(Register *reg, uint8_t value1, uint8_t value2);
void check_if_has_borrow_and_set_8b(Register *reg, uint8_t value1, uint8_t value2);
void check_if_has_carry_and_set_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry);
void check_if_has_borrow_and_set_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry);

void check_if_has_carry_and_set_h_16b(Register *reg, uint16_t value);

void check_if_op_zero_and_set_z(Register *reg, uint8_t value);

void set_c_flag_if_add_op_gt_FF(Register *reg, uint16_t value);
void set_c_flag_if_add_op_gt_FFFF(Register *reg, uint32_t value);
void set_c_flag_if_add_lt_0(Register *reg, uint16_t value);
void check_if_has_borrow_and_set_c_8b(Register *reg, uint8_t value1, uint8_t value2);
void check_if_has_borrow_and_set_c_8b_with_carry(Register *reg, uint8_t value1, uint8_t value2, uint8_t carry);
