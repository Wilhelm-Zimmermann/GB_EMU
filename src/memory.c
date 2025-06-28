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
    mem->memory = malloc(sizeof(uint8_t) * (1024 * 1024 * 32)); // 32MB, only for tests

    if(mem->memory == NULL) {
        fprintf(stderr, "RAM could not be allocated!!");
        return;
    }
}