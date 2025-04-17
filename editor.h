#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>

void editor_init(int window_width, int window_height);
void editor_quit();
void editor_start_tilemap();
void editor_start_scene();
void editor_start_options();
SDL_Rect* editor_get_toolbar();
SDL_Rect* editor_get_sidebar();
void editor_handle_input();
void editor_update(float dt);
void editor_render();

#endif