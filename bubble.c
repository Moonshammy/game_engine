#include "bubble.h"
#include <time.h>
#include <math.h>

void bubble_init(Bubble *b, float x, float y, float speed, float radius) {
    b->x = x;
    b->y = y;
    b->radius = radius;

    float angle = (float)(rand() % 360) * (3.14159265f / 180.0f);

    b->dx = cosf(angle) * speed;
    b->dy = sinf(angle) * speed;
}

void bubble_update(Bubble *b, float dt, int screen_width, int screen_height){
    b->x += b->dx * dt;
    b->y += b->dy * dt;

    if (b->x - b->radius < 0 || b->x + b->radius > screen_width){
        b->dx *= -1;
    }
    if (b->y - b->radius < 0 || b->y + b->radius > screen_height) {
        b->dy *= -1;
    }
}

static void draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void bubble_render(SDL_Renderer *renderer, const Bubble *b) {
    SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
    draw_filled_circle(renderer, (int)b->x, (int)b->y, (int)b->radius);
}

