#include <SDL2/SDL_ttf.h>

//Created a seperate font.c to stop an issue where the font was not closing properly.
static TTF_Font* ui_font = NULL;

void font_init(){
    if (TTF_Init() < 0) {
        SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
    }
    
    ui_font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    if (!ui_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

void close_font(){
    TTF_CloseFont(ui_font);
    TTF_Quit();
}

TTF_Font* get_font(){
    return ui_font;
}