#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

bool engine_init(const char *title, int width, int height);
void engine_update();
void engine_render();
void engine_shutdown();
bool engine_is_running();
SDL_Renderer* engine_get_renderer();
float engine_get_delta_time();

#endif
