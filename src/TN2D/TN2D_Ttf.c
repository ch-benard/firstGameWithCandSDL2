#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "TN2D_Ttf.h"
#include "TN2D_Graphics.h"

int TN2D_ttfInit() {
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    } else {
        return 0;
    }
}

tn2d_font TN2D_newFont(const char *path, int iSize) {
    tn2d_font font = {NULL};
    font.sdl_font = TTF_OpenFont(path, iSize);
    if (font.sdl_font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s %s\n", path, TTF_GetError());
    }
    return font;
}

tn2d_texture TN2D_newText(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha) {
    SDL_Color color = {iRed, iGreen, iBlue, iAlpha};
    SDL_Surface *surface = TTF_RenderText_Blended(font.sdl_font, text, color);
    if (surface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        tn2d_texture texture = {NULL, 0, 0};
        return texture;
    }

    tn2d_texture texture = {NULL, 0, 0};
    texture.sdl_texture = SDL_CreateTextureFromSurface(tn2d_sdl_renderer, surface);
    if (texture.sdl_texture == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        texture.width = surface->w;
        texture.height = surface->h;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void TN2D_freeFont (tn2d_font font) {
    if (font.sdl_font != NULL) {
        TTF_CloseFont(font.sdl_font);
        font.sdl_font = NULL;
    }
}
