#ifndef __TN2D_TTF_H__
#define __TN2D_TTF_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "TN2D_Graphics.h"

extern const Uint8 *tn2d_ttf_key_state;

typedef struct {
    TTF_Font *sdl_font;
} tn2d_font;

int TN2D_ttfInit();
tn2d_font TN2D_newFont(const char *path, int iSize);
tn2d_texture TN2D_newText(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha);
void TN2D_freeFont (tn2d_font font);

#endif