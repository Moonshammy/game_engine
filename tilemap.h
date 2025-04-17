#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

void tilemap_init();
void tilemap_set_tiles_width(int width);
void tilemap_set_tiles_height(int height);
void tilemap_set_tiles_dimensions(int width, int height);
void tilemap_set_size(int size);

void tilemap_set_tools_pos();

int tilemap_get_sidebar_width();
void tilemap_handle_input();
void tilemap_update();
void tilemap_render();


#endif