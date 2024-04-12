#ifndef __TN2D_GRAPHICS_H__
#define __TN2D_GRAPHICS_H__

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

extern SDL_Renderer *tn2d_sdl_renderer;

// Init and close the graphics
int tn2d_graphics_init(char *stitle, int iWidth, int iHeight, bool bFukllscreen);
void tn2d_graphics_close(void);

// Game loop
int tn2d_graphics_begin_draw(void);
void tn2d_graphics_end_draw(void);

// Image

typedef struct {
    int x;
    int y;
    int width;
    int height;
} tn2d_graphics_rect;

typedef struct {
    SDL_Texture *sdl_texture;
    int width;
    int height;
} tn2d_texture;

tn2d_texture tn2d_graphics_new_image(const char *path);
void tn2d_graphics_free_image(tn2d_texture texture);
float get_tn2d_fDeltaTime(void);
void tn2d_graphics_draw_image(tn2d_texture texture, int iX, int iY);
void tn2d_graphics_draw_quad(tn2d_texture texture, tn2d_graphics_rect rectSource, int iX, int iY);

// Primitives
void tn2d_graphics_color(int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_point(int iX, int iY, int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_line(int iX1, int iY1, int iX2, int iY2, int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_rect(const char *mode, int iX, int iY, int iWidth, int iHeight, int iRed, int iGreen, int iBlue, int iAlpha);

#endif