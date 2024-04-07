#ifndef __tn2d_graphics_h__
#define __tn2d_graphics_h__

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

// Init and close the graphics
int tn2d_graphics_init(char *stitle, int iWidth, int iHeight, bool bFukllscreen);
void tn2d_graphics_close(void);

// Game loop
int tn2d_graphics_begin_draw(void);
void tn2d_graphics_end_draw(void);

// Image loading
typedef struct {
    SDL_Texture *sdl_texture;
    int width;
    int height;
} tn2d_texture;
tn2d_texture tn2d_graphics_new_image(const char *path);
void tn2d_graphics_free_image(tn2d_texture texture);
void tn2d_graphics_draw_image(tn2d_texture texture, int iX, int iY);

// Primitives
void tn2d_graphics_color(int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_point(int iX, int iY, int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_line(int iX1, int iY1, int iX2, int iY2, int iRed, int iGreen, int iBlue, int iAlpha);
void tn2d_graphics_draw_rect(const char *mode, int iX, int iY, int iWidth, int iHeight, int iRed, int iGreen, int iBlue, int iAlpha);

// Fonts and text
typedef struct {
    TTF_Font *sdl_font;
} tn2d_font;

tn2d_font tn2d_graphics_new_font(const char *path, int iSize);
tn2d_texture tn2d_graphics_new_text(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha);  
#endif