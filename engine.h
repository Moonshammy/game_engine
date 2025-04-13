#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

bool engine_init(const char *title, int width, int height);
void engine_update();
void engine_render();
void engine_shutdown();
bool engine_is_running();
SDL_Renderer* get_engine_renderer();
float get_engine_delta_time();
int get_engine_window_width();
int get_engine_window_height();

#endif
