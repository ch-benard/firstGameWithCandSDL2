#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tn2d/tn2d.h"
#include "tn2d/tn2d_graphics.h"
#include "tn2d/tn2d_ttf.h"
#include "game.h"

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int iGameWidth = 1024, iGameHeight = 824;

    tn2d_init();
    tn2d_graphics_init("Shaolin Quest", iGameWidth, iGameHeight, false);
    tn2d_ttf_init();

    // INIT
    game_init();

    // GAME LOOP
    while (true) {

        // UPDATE
        tn2d_graphics_color(0, 0, 0, 0);
        if (tn2d_graphics_begin_draw() == 0) {
            break;
        }

        game_update(get_tn2d_fDeltaTime());
        game_render();

        // RENDER
        tn2d_graphics_end_draw();
    }

    game_close();
    tn2d_graphics_close();

    return 0;
}
