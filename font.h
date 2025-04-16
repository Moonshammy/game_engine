#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

void font_init();
void font_set(char *font_name[]);
TTF_Font* font_get();
void font_shutdown();

#endif