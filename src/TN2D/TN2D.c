#include "TN2D.h"
#include "TN2D_Graphics.h"
#include "TN2D_Keyboard.h"
#include "TN2D_Ttf.h"
#include "../constants.h"

int TN2D_Init(void) {
    if (TN2D_graphicsInit(GAMETITLE, GAMEWIDTH, GAMEHEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        TN2D_keyboardInit();
        TN2D_ttfInit();
        return TRUE;
    }
    return FALSE;
}

void TN2D_Close(void) {
    TN2D_graphicsClose();
}