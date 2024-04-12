#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tn2d/tn2d.h"
#include "tn2d/tn2d_graphics.h"
#include "tn2d/tn2d_ttf.h"

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int iGameWidth = 800, iGameHeight = 864;
    tn2d_texture texFusee;

    tn2d_init();
    tn2d_graphics_init("My first SDL2 test", iGameWidth, iGameHeight, false);
    tn2d_ttf_init();

    texFusee = tn2d_graphics_new_image("assets/images/fusee.png");
    int iYpos = iGameHeight - texFusee.height;
    tn2d_font font = tn2d_ttf_new_font("assets/fonts/Bangers-Regular.ttf", 48);
    tn2d_texture texText = tn2d_ttf_new_text(font, "Hey SpaceX, look how precise my landing is !", 255, 255, 255, 125);
    tn2d_texture textDeltatime;

    // GAME LOOP
    while (true) {
        // INIT


        // UPDATE
        tn2d_graphics_color(0, 0, 0, 0);
        if (tn2d_graphics_begin_draw() == 0) {
            break;
        }

        if (tn2d_keyboard_key_pressed("Up")) {
            if (iYpos > 0) {
                iYpos += -1;
            }
        } else if (tn2d_keyboard_key_pressed("Down")) {
            if (iYpos <= iGameHeight - texFusee.height) {
                iYpos += 1;
            }
        }

        // RENDER
        tn2d_graphics_draw_line(0, 0, iGameWidth, iGameHeight, 255, 0, 255, 255);
        tn2d_graphics_draw_rect("fill", 100, 100, 200, 200, 255, 0, 0, 100);
        tn2d_graphics_draw_rect("fill", 130, 130, 200, 200, 0, 0, 255, 100);
        tn2d_graphics_draw_image(texFusee, 0, iYpos);
        tn2d_graphics_draw_image(texText, 10, 10);

        char sDeltatime[50];
        sprintf(sDeltatime, "Deltatime: %.2f", get_tn2d_fDeltaTime());
        textDeltatime = tn2d_ttf_new_text(font, sDeltatime, 255, 255, 255, 255);
        tn2d_graphics_draw_image(textDeltatime, 10, 100);


        tn2d_graphics_end_draw();
    }
    tn2d_graphics_free_image(texFusee);
    tn2d_graphics_free_image(texText);
    tn2d_graphics_free_image(textDeltatime);
    tn2d_ttf_free_font(font);
    tn2d_graphics_close();
    return 0;
}
