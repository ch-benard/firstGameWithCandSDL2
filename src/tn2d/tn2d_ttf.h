#ifndef __TN2D_TTF_H__
#define __TN2D_TTF_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "tn2d_graphics.h"

extern const Uint8 *tn2d_ttf_key_state;

typedef struct {
    TTF_Font *sdl_font;
} tn2d_font;

int tn2d_ttf_init();
tn2d_font tn2d_ttf_new_font(const char *path, int iSize);
tn2d_texture tn2d_ttf_new_text(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha);

#endif