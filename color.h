#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <stdbool.h>

void color_init(int width, int height, int SIDEBAR_WIDTH);
SDL_Color color_create(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
bool color_equals(SDL_Color a, SDL_Color b);
SDL_Color color_blend(SDL_Color a, SDL_Color b, float t);
void color_debug(SDL_Color color);
void color_handle_input();
SDL_Color get_current_color();
bool get_color_fill();
void draw_slider(SDL_Renderer *renderer, int channel, int value, int x, int y_offset);
void color_render(SDL_Renderer *renderer);

#endif