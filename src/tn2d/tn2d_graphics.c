#include <stdio.h>
#include "tn2d_graphics.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *tn2d_sdl_window;
SDL_Renderer *tn2d_sdl_renderer;
 
int tn2d_graphics_init(char *stitle, int iWidth, int iHeight, bool bFukllscreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Failed to initialise SDL\n");
        return -1;
    }

    Uint32 iFlags = SDL_WINDOW_SHOWN;
    if (bFukllscreen)
    {
        iFlags |= SDL_WINDOW_FULLSCREEN;
    }

    tn2d_sdl_window = SDL_CreateWindow( stitle,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        iWidth,
                                        iHeight,
                                        iFlags);

    if (tn2d_sdl_window == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    tn2d_sdl_renderer = SDL_CreateRenderer(tn2d_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (tn2d_sdl_renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return -1;
    }
    else
    {
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return -1;
        }
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    SDL_SetRenderDrawBlendMode(tn2d_sdl_renderer, SDL_BLENDMODE_BLEND);
}

void tn2d_graphics_close(void) {
    SDL_DestroyRenderer(tn2d_sdl_renderer);
    SDL_DestroyWindow(tn2d_sdl_window);
    IMG_Quit();
    SDL_Quit();
}

int tn2d_graphics_begin_draw(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 0;
        }
    }

    SDL_RenderClear(tn2d_sdl_renderer);
    return 1;
}

void tn2d_graphics_end_draw(void) {
    SDL_RenderPresent(tn2d_sdl_renderer);
}

/* Fonction qui envoit une texture */
SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *texture = NULL;

    texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return NULL;
    }

    return texture;
}


tn2d_texture tn2d_graphics_new_image(const char *path) {
    tn2d_texture texture;
    texture.sdl_texture = LoadTexture(tn2d_sdl_renderer, path);
    if (texture.sdl_texture == NULL)
    {
        printf("Unable to load texture from %s! SDL Error: %s\n", path, SDL_GetError());
    } else {
        SDL_QueryTexture(texture.sdl_texture, NULL, NULL, &texture.width, &texture.height);
    }
    return texture;
}

void tn2d_graphics_free_image(tn2d_texture texture) {
    if(texture.sdl_texture != NULL) {
        SDL_DestroyTexture(texture.sdl_texture);
        texture.sdl_texture = NULL;
    }
}

void tn2d_graphics_draw_image(tn2d_texture texture, int iX, int iY) {
    SDL_Rect dest;
    dest.x = iX;
    dest.y = iY;
    dest.w = texture.width;
    dest.h = texture.height;
    int iresult = SDL_RenderCopy(tn2d_sdl_renderer, texture.sdl_texture, NULL, &dest);
    if (iresult != 0)
    {
        printf("Unable to draw texture! SDL Error: %s\n", SDL_GetError());
        return;
    }
}

// Primitives
void tn2d_graphics_color(int iRed, int iGreen, int iBlue, int iAlpha) {
    SDL_SetRenderDrawColor(tn2d_sdl_renderer, iRed, iGreen, iBlue, iAlpha);
}

void tn2d_graphics_draw_point(int iX, int iY, int iRed, int iGreen, int iBlue, int iAlpha) {
    tn2d_graphics_color(iRed, iGreen, iBlue, iAlpha);
    SDL_RenderDrawPoint(tn2d_sdl_renderer, iX, iY);
}

void tn2d_graphics_draw_line(int iX1, int iY1, int iX2, int iY2, int iRed, int iGreen, int iBlue, int iAlpha) {
    tn2d_graphics_color(iRed, iGreen, iBlue, iAlpha);
    SDL_RenderDrawLine(tn2d_sdl_renderer, iX1, iY1, iX2, iY2);
}

void tn2d_graphics_draw_rect(const char *mode, int iX, int iY, int iWidth, int iHeight, int iRed, int iGreen, int iBlue, int iAlpha) {
    tn2d_graphics_color(iRed, iGreen, iBlue, iAlpha);
    SDL_Rect rect;
    rect.x = iX;
    rect.y = iY;
    rect.w = iWidth;
    rect.h = iHeight;

    if (strcmp(mode, "line" ) == 0) {
        SDL_RenderDrawRect(tn2d_sdl_renderer, &rect);
    }
    else if (strcmp(mode, "fill" ) == 0) {
        SDL_RenderFillRect(tn2d_sdl_renderer, &rect);
    }
    else {
        printf("Mode %s not supported\n", mode);
    }

    SDL_RenderDrawRect(tn2d_sdl_renderer, &rect);
}

tn2d_font tn2d_graphics_new_font(const char *path, int iSize) {
    tn2d_font font = {NULL};
    font.sdl_font = TTF_OpenFont(path, iSize);
    if (font.sdl_font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s %s\n", path, TTF_GetError());
    }
    return font;
}

tn2d_texture tn2d_graphics_new_text(tn2d_font font, const char *text, int iRed, int iGreen, int iBlue, int iAlpha) {
    SDL_Color color = {iRed, iGreen, iBlue, iAlpha};
    SDL_Surface *surface = TTF_RenderText_Solid(font.sdl_font, text, color);
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