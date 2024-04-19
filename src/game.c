#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "TN2D/TN2D.h"
#include "TN2D/TN2D_Graphics.h"
#include "TN2D/TN2D_Ttf.h"
#include "game.h"

tn2d_font font;
tn2d_texture texBackground;
tn2d_texture texNinja;
tn2d_texture texTitle;

animation ninjaAnimation;
float fCurrentFrame;

int fps;
uint64_t frameTimer;
uint64_t frameInterval;
uint64_t startTime;
int speed;

int playerPositionX = 0;

void gameInit(void) {
    // Load the font
    font = TN2D_newFont("assets/fonts/Bangers-Regular.ttf", 36);
    if (font.sdl_font == NULL) {
        printf("Failed to load font!\n");
    }
    // Load the textures
    texBackground = TN2D_newImage("assets/images/background.jpg");
    texTitle = TN2D_newText(font, "Ninja Quest", 255, 255, 255, 255);
    texNinja = TN2D_newImage("assets/images/ninja/lg_ninja_walk_right.png");
    // Set the animation
    ninjaAnimation = (animation) {8, 400, 400, 0};
    // Set the current frame
    fCurrentFrame = ninjaAnimation.iCurrentFrame;
    // Set the FPS
    fps = 5;
    // Set the frame timer
    frameTimer = 0;
    // Set the frame timer
    frameInterval = 1000 / fps;
    // Set the speed
    speed = 8;    
    // Initialize the Deltatime
    // float fDeltaTime = 0;
}

void gameUpdate(float fDeltaTime) {
    if (frameTimer > frameInterval) {
        // Set the current frame
        fCurrentFrame = fCurrentFrame + 1;
        if (fCurrentFrame >= ninjaAnimation.iFramesInAnimation) {
            fCurrentFrame = 0;
        }
        printf("Current frame: %f\n", fCurrentFrame);
        // Reset the frame timer back to 0
        frameTimer = 0;
    } else {
        frameTimer += fDeltaTime;
    }

    // Move the player
    playerPositionX += speed;

    // Get time at the start of the frame
    startTime = SDL_GetPerformanceCounter();
    // Get time at the end of the frame
    uint64_t endTime = SDL_GetPerformanceCounter();
    // Calculate the elapsed time
    double elapsedTime = (double)(
        (endTime - startTime) / (double)(SDL_GetPerformanceFrequency())
    );
    fprintf(stdout, "Elapsed time: %f\n", elapsedTime);
} 

void renderSprite(tn2d_texture *texSprite, int iPositionX, int iPositionY, int iFrameWidth, int iFrameHeight, int iFrameNumber) {
    TN2D_Graphics_rect rect = {iFrameWidth * iFrameNumber, 0, iFrameWidth, iFrameHeight};
    TN2D_drawSpriteFromSheet(*texSprite, rect, iPositionX, iPositionY);
}

void gameRender(void) {
    TN2D_drawImage(texTitle, 0, 0);
    TN2D_drawImage(texBackground, 0, 100);
    renderSprite(&texNinja, playerPositionX, 600, 400, 400, fCurrentFrame);
}

void gameClose(void) {
    TN2D_freeImage(texTitle);
    TN2D_freeImage(texBackground);
    TN2D_freeImage(texNinja);
    TN2D_freeFont(font);
}
