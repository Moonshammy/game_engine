#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>

void editor_init(int window_width, int window_height);
void editor_quit();
void editor_start_tilemap();
void editor_start_scene();
void editor_start_options();

void editor_set_color(SDL_Color c);
void editor_draw_text(SDL_Color color, char *name, SDL_Rect rect);
void editor_draw_rect(SDL_Rect rect, SDL_Color c);
void editor_fill_rect(SDL_Rect rect, SDL_Color c);
void editor_fill_draw_rect(SDL_Rect rect, SDL_Color fill, SDL_Color draw);
void editor_create_text_rect(SDL_Renderer *renderer, SDL_Color color, char *name, SDL_Rect rect);

SDL_Rect editor_get_toolbar();
SDL_Rect editor_get_sidebar();

void editor_handle_input();
void editor_update(float dt);
void editor_render();

#endif