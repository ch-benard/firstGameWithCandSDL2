#ifndef __MAIN2_H__
#define __MAIN2_H__

typedef struct animation {
    int iFramesInAnimation;
    int iFrameWidth;
    int iFrameHeight;
    int iCurrentFrame;
} animation;

typedef struct tn2d_texture {
    SDL_Texture *sdl_texture;
    int width;
    int height;
} tn2d_texture;
#endif