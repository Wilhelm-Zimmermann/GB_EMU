#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./headers/memory.h"
#define DEBUG

void initMemory(Memory *mem)
{
#ifdef DEBUG
    printf("Allocating RAM...\n");
#endif
    mem->vRamSize = (1024 * 8);
    mem->memory = malloc(sizeof(uint8_t) * (1024 * 32));
    mem->vRam = malloc(sizeof(uint8_t) * mem->vRamSize);

    if(mem->memory == NULL) {
        fprintf(stderr, "RAM could not be allocated!!");
        return;
    }
}