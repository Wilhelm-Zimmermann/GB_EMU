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

// SWAP
void swap8b(Register *reg, uint8_t* value);

// SRL
void shiftRightLogical8b(Register *reg, uint8_t* value);

// BIT
void checkBit(Register *reg, uint8_t* value, uint8_t bitPos);
void resetBit(Register *reg, uint8_t* value, uint8_t bitPos);
void setBit(Register *reg, uint8_t* value, uint8_t bitPos);
