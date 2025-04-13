#include "color.h"
#include <stdio.h>

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

SDL_Color color_create(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_Color c = {r, g, b, a};
    return c;
}

bool color_equals(SDL_Color a, SDL_Color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

SDL_Color color_blend(SDL_Color a, SDL_Color b, float t){
    SDL_Color c;
    c.r = (Uint8)((1 - t) * a.r + t * b.r);
    c.g = (Uint8)((1 - t) * a.g + t * b.g);
    c.b = (Uint8)((1 - t) * a.b + t * b.b);
    c.a = (Uint8)((1 - t) * a.a + t * b.a);
    return c;
}

void color_debug(SDL_Color c) {
    printf("Color RGBA = (%d, %d, %d, %d)\n", c.r, c.g, c.b, c.a);
}

void draw_slider(SDL_Renderer * renderer, int channel, int value, int x, int y_offset, int width, int height){
    SDL_Rect bar = {x, y_offset, width, height};

    switch (channel) {
        case CHANNEL_R: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
        case CHANNEL_G: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;
        case CHANNEL_B: SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
    }

    SDL_RenderFillRect(renderer, &bar);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect handle = { x + value - 2, y_offset - 2, 4, height + 4 };
    SDL_RenderFillRect(renderer, &handle);
}