#include "./register.h"
#include "./memory.h"

typedef struct
{
} CPU;

void cpu_cycle(Register* reg, Memory* mem);
void initRegisters(Register* reg);