#ifndef __TN2D_KEYBOARD_H__
#define __TN2D_KEYBOARD_H__

#include <stdbool.h>
#include "SDL2/SDL.h"

typedef struct tn2d_sdlkey {
    char *key; // "a", "right", etc.
    SDL_Scancode sdl_scancode;
} tn2d_sdlkey;

extern const Uint8 *tn2d_ttf_key_state;

void TN2D_keyboardInit(void);

bool TN2D_keyPress(const char *key);

#endif