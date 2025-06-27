#include <stdint.h>
#include <stdlib.h>
#include "memory.h"

void initMemory(Memory *mem)
{
    mem->memory = malloc(sizeof(uint16_t) * (1024 * 32));
}