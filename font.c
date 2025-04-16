#include "font.h"

#include <SDL2/SDL_ttf.h>

/*
Created a seperate font.c to stop an issue where the font was not closing properly.
I believe when it was in editor.c it was getting initialized out of order.
*/
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

void font_set(char *font_name[255]){
    TTF_CloseFont(ui_font);
    ui_font = TTF_OpenFont(*font_name, 16);
    if (!ui_font){
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

void font_shutdown(){
    TTF_CloseFont(ui_font);
    TTF_Quit();
}

TTF_Font* font_get(){
    return ui_font;
}