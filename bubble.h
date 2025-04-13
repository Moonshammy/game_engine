#ifndef BUBBLE_H
#define BUBBLE_H

#include <SDL2/SDL.h>

typedef struct {
    float x, y;
    float dx, dy;
    float radius;
} Bubble;

void bubble_init(Bubble *b, float x, float y, float speed, float radius);
void bubble_update(Bubble *b, float delta_time, int screen_width, int screen_height);
void bubble_render(SDL_Renderer *renderer, const Bubble *b);

#endif