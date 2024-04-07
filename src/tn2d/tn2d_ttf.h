#ifndef __tn2d_ttf_h__
#define __tn2d_ttf_h__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "tn2d_graphics.h"

// Fonts and text
typedef struct {
    TTF_Font *sdl_font;
} tn2d_font;

tn2d_font tn2d_ttf_new_font(const char *path, int iSize);
tn2d_texture tn2d_ttf_new_text(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha);

#endif