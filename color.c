#include "color.h"
#include "engine.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#define SLIDER_WIDTH 255
#define SLIDER_HEIGHT 20
#define SLIDER_SPACING 40
#define SLIDER_X 10
#define SLIDER_Y_START 10

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

static SDL_Color current_color = {255,0,0,255};
static int previous_mouse_state = 0;
static int sidebar_width;
static int sidebar_padding;
static int base_x;

static int window_width;
static int window_height;

void color_init(int width, int height, int SIDEBAR_WIDTH, int SIDEBAR_PADDING){
    window_width = width;
    window_height = height;

    sidebar_width = SIDEBAR_WIDTH;
    sidebar_padding = SIDEBAR_PADDING;
    base_x = window_width - SIDEBAR_WIDTH + SIDEBAR_PADDING;
    current_color = color_create(255, 0, 0, 255);

}

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

void color_handle_input(){
    int mx, my;
    Uint32 current_mouse_state = SDL_GetMouseState(&mx, &my);
    int base_x = get_engine_window_width() - sidebar_width + sidebar_padding;

    for (int c = 0; c < 3; c++) {
        int y = SLIDER_Y_START + c * SLIDER_SPACING + SLIDER_SPACING;
        SDL_Rect bar = { base_x, y, SLIDER_WIDTH, SLIDER_HEIGHT };

        if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
            !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

            if (mx >= bar.x && mx <= bar.x + bar.w &&
                my >= 
                
                bar.y && my <= bar.y + bar.h) {

                Uint8 value = (Uint8)(mx - bar.x);
                if (c == CHANNEL_R) current_color.r = value;
                if (c == CHANNEL_G) current_color.g = value;
                if (c == CHANNEL_B) current_color.b = value;
            }
        }
    }
}

SDL_Color get_current_color(){
    return current_color;
}

void draw_slider(SDL_Renderer *renderer, int channel, int value, int x, int y_offset){
    SDL_Rect bar = {x, y_offset, SLIDER_WIDTH, SLIDER_HEIGHT};

    switch (channel) {
        case CHANNEL_R: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
        case CHANNEL_G: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;
        case CHANNEL_B: SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
    }

    SDL_RenderFillRect(renderer, &bar);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect handle = { x + value - 2, y_offset - 2, 4, window_height + 4 };
    SDL_RenderFillRect(renderer, &handle);
}

void color_render(SDL_Renderer *renderer){
    draw_slider(renderer, CHANNEL_R, current_color.r, base_x, SLIDER_Y_START + SLIDER_SPACING + 5);
    draw_slider(renderer, CHANNEL_G, current_color.g, base_x, SLIDER_Y_START + SLIDER_SPACING * 2 + 5);
    draw_slider(renderer, CHANNEL_B, current_color.b, base_x, SLIDER_Y_START + SLIDER_SPACING * 3 + 5);
    
    SDL_Rect preview = { base_x, SLIDER_Y_START, 40, 40 };
    SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
    SDL_RenderFillRect(renderer, &preview);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &preview);
}