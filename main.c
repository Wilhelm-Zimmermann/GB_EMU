#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "./src/headers/memory.h"

int main()
{
    printf("Hello World!!\n");
    Memory *mem = malloc(sizeof(Memory));
    initMemory(mem);
    return 0;
}