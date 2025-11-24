#pragma once
#include <stdint.h>
#include "register.h"

// RLC & RRC
void rotate_left_circular_8b(Register *reg, uint8_t* value);
void rotate_right_circular_8b(Register *reg, uint8_t* value);

// RL & RR
void rotate_left_8b(Register *reg, uint8_t* value);
void rotate_right_8b(Register *reg, uint8_t* value);

// SLA & SRA
void shift_left_arithmetic_8b(Register *reg, uint8_t* value);
void shift_right_arithmetic_8b(Register *reg, uint8_t* value);

// SWAP
void swap_8b(Register *reg, uint8_t* value);

// SRL
void shift_right_logical_8b(Register *reg, uint8_t* value);

// BIT
void check_bit(Register *reg, uint8_t* value, uint8_t bitPos);
void reset_bit(Register *reg, uint8_t* value, uint8_t bitPos);
void set_bit(Register *reg, uint8_t* value, uint8_t bitPos);
