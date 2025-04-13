#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <stdbool.h>

SDL_Color color_create(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
bool color_equals(SDL_Color a, SDL_Color b);
SDL_Color color_blend(SDL_Color a, SDL_Color b, float t);
void color_debug(SDL_Color color);
void draw_slider(SDL_Renderer * renderer, int channel, int value, int x, int y_offset, int width, int height);

#endif