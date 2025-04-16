#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

void tilemap_init(int rows, int cols, int size);
int tilemap_get_sidebar_width();
void tilemap_handle_input();
void tilemap_render(SDL_Renderer *renderer);


#endif