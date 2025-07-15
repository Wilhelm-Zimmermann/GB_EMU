#pragma once
#include <stdint.h>
#include "register.h"

// RLC & RRC
void rotateLeftCircular8b(Register *reg, uint8_t* value);
void rotateRightCircular8b(Register *reg, uint8_t* value);

// RL & RR
void rotateLeft8b(Register *reg, uint8_t* value);
void rotateRight8b(Register *reg, uint8_t* value);

// SLA & SRA
void shiftLeftArithmetic8b(Register *reg, uint8_t* value);
void shiftRightArithmetic8b(Register *reg, uint8_t* value);