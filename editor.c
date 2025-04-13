#include "editor.h"
#include "engine.h"
#include "color.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

#define SIDEBAR_WIDTH 300
#define SIDEBAR_PADDING 10

#define SLIDER_WIDTH 255
#define SLIDER_HEIGHT 20
#define SLIDER_SPACING 40
#define SLIDER_X 10
#define SLIDER_Y_START 10

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

typedef struct {
    SDL_Color color;
    bool filled;
} Tile;

static Tile tilemap[MAX_ROWS][MAX_COLS];
static int tile_rows = 0;
static int tile_cols = 0;
static int tile_size = 32;

static SDL_Color current_color;
static int previous_mouse_state = 0;


void editor_init(int rows, int cols, int size){
    tile_rows = rows;
    tile_cols = cols;
    tile_size = size;
    int window_width = get_engine_window_width();
    int window_height = get_engine_window_height();
    int usable_width = window_width - SIDEBAR_WIDTH;
    tile_cols = usable_width / tile_size;

    current_color = color_create(255, 0, 0, 255);

    for(int y = 0; y < tile_rows; y++){
        for (int x = 0; x < tile_cols; x++){
            tilemap[y][x].filled = false;
        }
    }
}

void editor_handle_input() {
    int mx, my;
    Uint32 current_mouse_state = SDL_GetMouseState(&mx, &my);
    int base_x = get_engine_window_width() - SIDEBAR_WIDTH + SIDEBAR_PADDING;

    for (int c = 0; c < 3; c++) {
        int y = SLIDER_Y_START + c * SLIDER_SPACING + SLIDER_SPACING;
        SDL_Rect bar = { base_x, y, SLIDER_WIDTH, SLIDER_HEIGHT };

        if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
            !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

            if (mx >= bar.x && mx <= bar.x + bar.w &&
                my >= bar.y && my <= bar.y + bar.h) {

                Uint8 value = (Uint8)(mx - bar.x);
                if (c == CHANNEL_R) current_color.r = value;
                if (c == CHANNEL_G) current_color.g = value;
                if (c == CHANNEL_B) current_color.b = value;
            }
        }
    }

    if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

        int col = mx / tile_size;
        int row = my / tile_size;

        if (row >= 0 && row < tile_rows && col >= 0 && col < tile_cols) {
            tilemap[row][col].color = current_color;
            tilemap[row][col].filled = true;
        }
    }

    previous_mouse_state = current_mouse_state;
}

void editor_update(float dt){
    //TODO
}

void editor_render() {
    int window_width = get_engine_window_width();
    int window_height = get_engine_window_height();
    SDL_Renderer *renderer = get_engine_renderer();


    // Draw tile grid
    for (int y = 0; y < tile_rows; y++) {
        for (int x = 0; x < tile_cols; x++) {
            SDL_Rect cell = { x * tile_size, y * tile_size, tile_size, tile_size };

            if (tilemap[y][x].filled) {
                SDL_Color c = tilemap[y][x].color;
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderFillRect(renderer, &cell);
            }

            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }

    SDL_Rect sidebar = {window_width - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, window_height};
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark gray sidebar
    SDL_RenderFillRect(renderer, &sidebar);

    int base_x = window_width - SIDEBAR_WIDTH + SIDEBAR_PADDING;

    // Draw RGB sliders
    draw_slider(renderer, CHANNEL_R, current_color.r, base_x, SLIDER_Y_START + SLIDER_SPACING + 5, SLIDER_WIDTH, SLIDER_HEIGHT);
    draw_slider(renderer, CHANNEL_G, current_color.g, base_x, SLIDER_Y_START + SLIDER_SPACING * 2 + 5, SLIDER_WIDTH, SLIDER_HEIGHT);
    draw_slider(renderer, CHANNEL_B, current_color.b, base_x, SLIDER_Y_START + SLIDER_SPACING * 3 + 5, SLIDER_WIDTH, SLIDER_HEIGHT);

    // Color preview
    SDL_Rect preview = { base_x, SLIDER_Y_START, 40, 40 };
    SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
    SDL_RenderFillRect(renderer, &preview);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &preview);
}
