#include "SDL2/SDL.h"
#include "tn2d_keyboard.h"

tn2d_sdlkey _tn2d_keymap[] = {
    {"a", SDL_SCANCODE_A},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"e", SDL_SCANCODE_E},
    {"f", SDL_SCANCODE_F},
    {"g", SDL_SCANCODE_G},
    {"h", SDL_SCANCODE_H},
    {"i", SDL_SCANCODE_I},
    {"j", SDL_SCANCODE_J},
    {"k", SDL_SCANCODE_K},
    {"l", SDL_SCANCODE_L},
    {"m", SDL_SCANCODE_M},
    {"n", SDL_SCANCODE_N},
    {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P},
    {"q", SDL_SCANCODE_Q},
    {"r", SDL_SCANCODE_R},
    {"s", SDL_SCANCODE_S},
    {"t", SDL_SCANCODE_T},
    {"u", SDL_SCANCODE_U},
    {"v", SDL_SCANCODE_V},
    {"w", SDL_SCANCODE_W},
    {"x", SDL_SCANCODE_X},
    {"y", SDL_SCANCODE_Y},
    {"z", SDL_SCANCODE_Z},
    {"o", SDL_SCANCODE_0},
    {"1", SDL_SCANCODE_1},
    {"2", SDL_SCANCODE_2},
    {"3", SDL_SCANCODE_3},
    {"4", SDL_SCANCODE_4},
    {"5", SDL_SCANCODE_5},
    {"6", SDL_SCANCODE_6},
    {"7", SDL_SCANCODE_7},
    {"8", SDL_SCANCODE_8},
    {"9", SDL_SCANCODE_9},
    {"Return", SDL_SCANCODE_RETURN},
    {"Escape", SDL_SCANCODE_ESCAPE},
    {"Backspace", SDL_SCANCODE_BACKSPACE},
    {"Tab", SDL_SCANCODE_TAB},
    {"Space", SDL_SCANCODE_SPACE},
    {"Minus", SDL_SCANCODE_MINUS},
    {"Equals", SDL_SCANCODE_EQUALS},
    {"Leftbracket", SDL_SCANCODE_LEFTBRACKET},
    {"Rightbracket", SDL_SCANCODE_RIGHTBRACKET},
    {"Backslash", SDL_SCANCODE_BACKSLASH},
    {"Nonushash", SDL_SCANCODE_NONUSHASH},
    {"Semicolon", SDL_SCANCODE_SEMICOLON},
    {"Apostrophe", SDL_SCANCODE_APOSTROPHE},
    {"Grave", SDL_SCANCODE_GRAVE},
    {"Comma", SDL_SCANCODE_COMMA},
    {"Period", SDL_SCANCODE_PERIOD},
    {"Slash", SDL_SCANCODE_SLASH},
    {"Right", SDL_SCANCODE_RIGHT},
    {"Left", SDL_SCANCODE_LEFT},
    {"Down", SDL_SCANCODE_DOWN},
    {"Up", SDL_SCANCODE_UP}
};

const Uint8 *_tn2d_ttf_key_state = NULL;

tn2d_sdlkey *_tn2d_keyboard_get_key(const char *key) {
    size_t num_items = sizeof(_tn2d_keymap) / sizeof(tn2d_sdlkey);
    for (size_t i = 0; i < num_items; i++) {
        if (strcmp(_tn2d_keymap[i].key, key) == 0) {
            return &_tn2d_keymap[i];
        }
    }
    return NULL;
}

void _tn2d_keyboard_init(void) {
    _tn2d_ttf_key_state = SDL_GetKeyboardState(NULL);
}

bool tn2d_keyboard_key_pressed(const char *key) {
    tn2d_sdlkey *sdlkey = _tn2d_keyboard_get_key(key);
    if (sdlkey) {
        return _tn2d_ttf_key_state[sdlkey->sdl_scancode];
    }
    return NULL;
}