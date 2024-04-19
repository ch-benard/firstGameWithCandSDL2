#ifndef __GAME_H__
#define __GAME_H__

typedef struct animation {
    int iFramesInAnimation;
    int iFrameWidth;
    int iFrameHeight;
    int iCurrentFrame;
} animation;

void gameInit(void);
void gameUpdate(float fDeltaTime);
void gameRender(void);
void gameClose(void);

#endif