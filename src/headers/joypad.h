#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t start;
    uint8_t select;
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
} JoypadState;

JoypadState joypad = {0};

void handle_joypad(SDL_Event e, JoypadState *joypad);