#pragma once
#include <stdint.h>
#include "register.h"

void rotateLeftCircular8b(Register *reg, uint8_t* value);
void rotateRightCircular8b(Register *reg, uint8_t* value);
void rotateLeft8b(Register *reg, uint8_t* value);
void rotateRight8b(Register *reg, uint8_t* value);