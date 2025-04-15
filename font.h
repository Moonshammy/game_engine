#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

void font_init();
TTF_Font* get_font();
void close_font();

#endif