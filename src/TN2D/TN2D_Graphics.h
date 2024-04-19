#ifndef __TN2D_GRAPHICS_H__
#define __TN2D_GRAPHICS_H__

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

extern SDL_Renderer *tn2d_sdl_renderer;

// Init and close the graphics
int TN2D_graphicsInit(char *stitle, int iWidth, int iHeight, int iScreenMode);
void TN2D_graphicsClose(void);

// Game loop
int TN2D_beginDraw(void);
void TN2D_endDraw(void);

// Image
typedef struct {
    int x;
    int y;
    int width;
    int height;
} TN2D_Graphics_rect;

typedef struct {
    SDL_Texture *sdl_texture;
    int width;
    int height;
} tn2d_texture;

tn2d_texture TN2D_newImage(const char *path);
void TN2D_freeImage(tn2d_texture texture);
void TN2D_drawImage(tn2d_texture texture, int iX, int iY);
void TN2D_drawSpriteFromSheet(tn2d_texture texture, TN2D_Graphics_rect rectSource, int iX, int iY);

// Primitives
void TN2D_setColor(int iRed, int iGreen, int iBlue, int iAlpha);
void TN2D_drawPoint(int iX, int iY, int iRed, int iGreen, int iBlue, int iAlpha);
void TN2D_drawLine(int iX1, int iY1, int iX2, int iY2, int iRed, int iGreen, int iBlue, int iAlpha);
void TN2D_drawRectangle(const char *mode, int iX, int iY, int iWidth, int iHeight, int iRed, int iGreen, int iBlue, int iAlpha);

#endif