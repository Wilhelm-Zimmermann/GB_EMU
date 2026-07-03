#include "headers/joypad.h"
#include <SDL2/SDL.h>

void handle_joypad(SDL_Event e, JoypadState *joypad)
{
    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    {
        uint8_t state = (e.type == SDL_KEYDOWN) ? 1 : 0;

        switch (e.key.keysym.sym)
        {
        case SDLK_z:
            joypad->a = state;
            break;
        case SDLK_x:
            joypad->b = state;
            break;
        case SDLK_RETURN:
            joypad->start = state;
            break;
        case SDLK_SPACE:
            joypad->select = state;
            break;
        case SDLK_UP:
            joypad->up = state;
            break;
        case SDLK_DOWN:
            joypad->down = state;
            break;
        case SDLK_LEFT:
            joypad->left = state;
            break;
        case SDLK_RIGHT:
            joypad->right = state;
            break;
        }
    }
}