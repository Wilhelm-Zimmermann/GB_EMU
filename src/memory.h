#include <stdint.h>

typedef struct
{
    uint16_t *memory;
} Memory;

void initMemory(Memory *mem);