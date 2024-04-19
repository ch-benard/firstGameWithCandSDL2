#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "constants.h"
#include "main2.h"

int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
SDL_Texture *background_texture = NULL;
SDL_Rect dstrect;
tn2d_texture texNinja;
animation ninjaAnimation;
int fCurrentFrame;
int fps;
uint64_t frame_interval;
uint64_t last_frame_time;
uint64_t startTime;
int speed;
int playerPositionX;
float fDeltaTime;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GAMEWIDTH,
        GAMEHEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }
    return TRUE;
}

void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game_is_running = FALSE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game_is_running = FALSE;
                }
                break;
        }
    }
}

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
    texture.sdl_texture = LoadTexture(renderer, path);
    if (texture.sdl_texture == NULL)
    {
        printf("Unable to load texture from %s! SDL Error: %s\n", path, SDL_GetError());
    } else {
        SDL_QueryTexture(texture.sdl_texture, NULL, NULL, &texture.width, &texture.height);
    }
    return texture;
}

void drawSpriteFromSheet(tn2d_texture texture, SDL_Rect source, int iX, int iY) {
    SDL_Rect rectSource;
    rectSource.x = source.x;
    rectSource.y = source.y;
    rectSource.w = source.w;
    rectSource.h = source.h;

    SDL_Rect dest;
    dest.x = iX;
    dest.y = iY;
    dest.w = rectSource.w;
    dest.h = rectSource.h;
    int iresult = SDL_RenderCopy(renderer, texture.sdl_texture, &rectSource, &dest);
    if (iresult != 0)
    {
        printf("Unable to draw texture! SDL Error: %s\n", SDL_GetError());
        return;
    }
}

void renderSprite(tn2d_texture *texSprite, int iPositionX, int iPositionY, int iFrameWidth, int iFrameHeight, int iFrameNumber) {
    SDL_Rect rect = {iFrameWidth * iFrameNumber, 0, iFrameWidth, iFrameHeight};
    drawSpriteFromSheet(*texSprite, rect, iPositionX, iPositionY);
}

void setup() {
    // Create a background texture
    background_texture = IMG_LoadTexture(renderer, "assets/images/background.jpg");
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 960;
    dstrect.h = 432;

    // Create the player texture
    texNinja = TN2D_newImage("assets/images/ninja/sm_ninja_walk_right.png");
    // Set the player animation
    ninjaAnimation = (animation) {8, 100, 100, 0};
        // Set the current frame
    fCurrentFrame = ninjaAnimation.iCurrentFrame;
    // Set the FPS
    fps = 10;
    // Set the frame interval
    frame_interval = 1000 / fps;
    // Set the frame timer
    last_frame_time = 0;
    // Set the speed
    speed = 50;
    // Set the player position
    playerPositionX = 0;
    // Initialize the Deltatime
    fDeltaTime = 0.0f;

}

void update() {
    // Calculate how much we have to wait to hit the target frame time
    uint64_t time_to_wait = frame_interval - (SDL_GetTicks() - last_frame_time);

    // Only delay if we are too fast to update this frame
    if (time_to_wait > 0 && time_to_wait <= frame_interval) {
        SDL_Delay(time_to_wait);
    }

    // Get the deltatime factor converted to seconds to be used to update objects
    fDeltaTime = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // Update the player animation
    // Set the current frame
    fCurrentFrame = fCurrentFrame + 1;
    if (fCurrentFrame >= ninjaAnimation.iFramesInAnimation) {
        fCurrentFrame = 0;
    }

    // Move the player
    playerPositionX += speed * fDeltaTime;

    // Store the milliseconds of the current frame to be useed to update objects
    last_frame_time = SDL_GetTicks();

}

void render() {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, &dstrect);
    renderSprite(&texNinja, playerPositionX, 320, 100, 100, fCurrentFrame);

    // Here is where we can start drawing game objects
    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update(fDeltaTime);
        render();
    }

    return 0;
}