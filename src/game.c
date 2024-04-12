#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tn2d/tn2d.h"
#include "tn2d/tn2d_graphics.h"
#include "tn2d/tn2d_ttf.h"

tn2d_font font;
tn2d_texture texBackground;
tn2d_texture texShaolin;
tn2d_texture texTitle;

void game_init(void) {
    font = tn2d_ttf_new_font("assets/fonts/Bangers-Regular.ttf", 36);
    if (font.sdl_font == NULL) {
        printf("Failed to load font!\n");
    }
    texBackground = tn2d_graphics_new_image("assets/images/background.jpg");
    texTitle = tn2d_ttf_new_text(font, "Shaolin Quest", 255, 255, 255, 255);
    texShaolin = tn2d_graphics_new_image("assets/images/ninja/ninja_right_sprite_100.png");
}

void game_update(float fDeltaTime) {

}

void game_render(void) {
    tn2d_graphics_draw_image(texTitle, 0, 0);
    tn2d_graphics_draw_image(texBackground, 0, 100);
    tn2d_graphics_rect rect = {0, 0, 100, 100};
    tn2d_graphics_draw_quad(texShaolin, rect, 0, 824);
}

void game_close(void) {
    tn2d_graphics_free_image(texTitle);
    tn2d_graphics_free_image(texBackground);
    tn2d_graphics_free_image(texShaolin);
    tn2d_ttf_free_font(font);
}
