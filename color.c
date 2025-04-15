#include "color.h"
#include "engine.h"
#include "editor.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SLIDER_WIDTH 255
#define SLIDER_HEIGHT 20
#define SLIDER_SPACING 45
#define SLIDER_X 10

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

typedef enum {
    PAINT,
    ERASE
} ColorTool;

static SDL_Rect tools[3];
static SDL_Color current_color = {255,0,0,255};

static int previous_mouse_state = 0;

static int window_width;
static int window_height;

static int padding = 10;
static int base_x;
static int base_y;

static bool color_fill = true;
static ColorTool current_tool = PAINT;


void color_init(int width, int height, int SIDEBAR_WIDTH){
    window_width = width;
    window_height = height;

    base_x = window_width - SIDEBAR_WIDTH + padding;
    base_y = get_toolbar_height() + padding;

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

void switch_to_paint(){
    current_tool = PAINT;
    color_fill = true;
}

void switch_to_erase(){
    current_tool = ERASE;
    color_fill = false;
}

SDL_Color get_current_color(){
    return current_color;
}

bool get_color_fill(){
    return color_fill;
}

void color_debug(SDL_Color c) {
    printf("Color RGBA = (%d, %d, %d, %d)\n", c.r, c.g, c.b, c.a);
}

void color_handle_input(){
    int mx, my;
    Uint32 current_mouse_state = SDL_GetMouseState(&mx, &my);    

    if (mx >= base_x + 45 && mx < base_x + 90 && my >= base_y && my <base_y + 40){
        switch_to_paint;
    }
    else if (mx >= base_x + 90 && mx < base_x + 135 && my >= base_y && my <base_y + 40){
        switch_to_erase;
    }

    for (int c = 0; c < 3; c++) {
        int y = base_y + c * SLIDER_SPACING + SLIDER_SPACING;
        SDL_Rect bar = { base_x, y, SLIDER_WIDTH, SLIDER_HEIGHT };

        if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
            !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

            
            if (mx >= bar.x && mx <= bar.x + bar.w &&
                my >= bar.y && my <= bar.y + bar.h) {
                
                if (current_tool == PAINT){
                    Uint8 value = (Uint8)(mx - bar.x);
                    if (c == CHANNEL_R) current_color.r = value;
                    if (c == CHANNEL_G) current_color.g = value;
                    if (c == CHANNEL_B) current_color.b = value;
                }
                else if(current_tool == ERASE){
                    current_color.r = 0;
                    current_color.g = 0;
                    current_color.b = 0;
                }
            }
        }
    }
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
    SDL_Rect handle = { x + value - 2, y_offset - 2, 4, SLIDER_HEIGHT + 4 };
    SDL_RenderFillRect(renderer, &handle);
}

void color_render(SDL_Renderer *renderer){
    draw_slider(renderer, CHANNEL_R, current_color.r, base_x, base_y + SLIDER_SPACING);
    draw_slider(renderer, CHANNEL_G, current_color.g, base_x, base_y + SLIDER_SPACING * 2);
    draw_slider(renderer, CHANNEL_B, current_color.b, base_x, base_y + SLIDER_SPACING * 3);
    
    SDL_Rect color_preview = {base_x, base_y, 40, 40};
    SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
    SDL_RenderFillRect(renderer, &color_preview);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &color_preview);

    tools[0] = (SDL_Rect){base_x + 45, base_y, 40, 40};
    tools[1] = (SDL_Rect){base_x + 90, base_y, 40, 40};
    for (int i = 0; i < 2; i++){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderFillRect(renderer, &tools[i]);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &tools[i]);
    }
}