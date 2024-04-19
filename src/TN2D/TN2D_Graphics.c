#include <stdio.h>
#include "TN2D_Graphics.h"
#include ".././constants.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *tn2d_sdl_window;
SDL_Renderer *tn2d_sdl_renderer;
float tn2d_fDeltaTime = 0.0f;
Uint32 _tn2d_iTicksLastFrame;
 
int TN2D_graphicsInit(char *stitle, int iWidth, int iHeight, int iScreenMode) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Failed to initialise SDL: %s\n", SDL_GetError());
        return false;
    }

    // Try to create the game window
    tn2d_sdl_window = SDL_CreateWindow( stitle,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        iWidth,
                                        iHeight,
                                        iScreenMode);

    if (tn2d_sdl_window == NULL)
    {
        fprintf(stderr, "Could not create a window: %s", SDL_GetError());
        return -1;
    }

    // Try to create renderer
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

    SDL_SetRenderDrawBlendMode(tn2d_sdl_renderer, SDL_BLENDMODE_BLEND);

    return TRUE;
}

void TN2D_graphicsClose(void) {
    SDL_DestroyRenderer(tn2d_sdl_renderer);
    SDL_DestroyWindow(tn2d_sdl_window);
    IMG_Quit();
    SDL_Quit();
}

int TN2D_beginDraw(void) {
    Uint32 iTicksThisFrame = SDL_GetTicks();
    tn2d_fDeltaTime = (iTicksThisFrame - _tn2d_iTicksLastFrame) / 1000.0f;
    _tn2d_iTicksLastFrame = iTicksThisFrame;
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

void TN2D_endDraw(void) {
    SDL_RenderPresent(tn2d_sdl_renderer);

    // Cap the frame rate
    int iTimeToWait = 16 - (SDL_GetTicks() - _tn2d_iTicksLastFrame);
    if (iTimeToWait > 0 && iTimeToWait <= 16)
    {
        SDL_Delay(iTimeToWait);
    }
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


tn2d_texture TN2D_newImage(const char *path) {
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

void TN2D_freeImage(tn2d_texture texture) {
    if(texture.sdl_texture != NULL) {
        SDL_DestroyTexture(texture.sdl_texture);
        texture.sdl_texture = NULL;
    }
}

void TN2D_drawImage(tn2d_texture texture, int iX, int iY) {
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

void TN2D_drawSpriteFromSheet(tn2d_texture texture, TN2D_Graphics_rect source, int iX, int iY) {
    SDL_Rect rectSource;
    rectSource.x = source.x;
    rectSource.y = source.y;
    rectSource.w = source.width;
    rectSource.h = source.height;

    SDL_Rect dest;
    dest.x = iX;
    dest.y = iY;
    dest.w = rectSource.w;
    dest.h = rectSource.h;
    int iresult = SDL_RenderCopy(tn2d_sdl_renderer, texture.sdl_texture, &rectSource, &dest);
    if (iresult != 0)
    {
        printf("Unable to draw texture! SDL Error: %s\n", SDL_GetError());
        return;
    }
}

// Primitives
void TN2D_setColor(int iRed, int iGreen, int iBlue, int iAlpha) {
    SDL_SetRenderDrawColor(tn2d_sdl_renderer, iRed, iGreen, iBlue, iAlpha);
}

void TN2D_drawPoint(int iX, int iY, int iRed, int iGreen, int iBlue, int iAlpha) {
    TN2D_setColor(iRed, iGreen, iBlue, iAlpha);
    SDL_RenderDrawPoint(tn2d_sdl_renderer, iX, iY);
}

void TN2D_drawLine(int iX1, int iY1, int iX2, int iY2, int iRed, int iGreen, int iBlue, int iAlpha) {
    TN2D_setColor(iRed, iGreen, iBlue, iAlpha);
    SDL_RenderDrawLine(tn2d_sdl_renderer, iX1, iY1, iX2, iY2);
}

void TN2D_drawRectangle(const char *mode, int iX, int iY, int iWidth, int iHeight, int iRed, int iGreen, int iBlue, int iAlpha) {
    TN2D_setColor(iRed, iGreen, iBlue, iAlpha);
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
}
