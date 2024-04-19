#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "TN2D/TN2D.h"
#include "TN2D/TN2D_Graphics.h"
#include "TN2D/TN2D_Ttf.h"
#include "game.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    // setvbuf(stdout, NULL, _IONBF, 0);
    // INIT TN2D
    if (TN2D_Init() == FALSE) {
        printf("Failed to initialize TN2D!\n");
        return 1;
    };

    // INIT GAME
    gameInit();

    // GAME LOOP
    while (TRUE) {

        TN2D_setColor(0, 0, 0, 0);
        if (TN2D_beginDraw() == 0) {
            break;
        }

        // UPDATE GAME
        // gameUpdate();

        // RENDER GAME
        gameRender();

        // END
        TN2D_endDraw();
    }

    gameClose();
    TN2D_Close();

    return 0;
}
