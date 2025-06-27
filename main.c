#include <stdio.h>
#include <stdlib.h>
#include "./src/memory.h"

int main()
{
    printf("Hello World!!\n");
    Memory *mem = malloc(sizeof(Memory));
    initMemory(mem);
    return 0;
}