#include "editor.h"
#include "engine.h"
#include "color.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    SDL_Color color;
    bool filled;
} Tile;

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

static Tile tilemap[MAX_ROWS][MAX_COLS];
static int tile_rows = 0;
static int tile_cols = 0;
static int tile_size = 32;

static int previous_mouse_state = 0;



void tilemap_init(int rows, int cols, int size, int sidebar_width){
    int window_width = get_engine_window_width();
    int window_height = get_engine_window_height();

    tile_rows = rows;
    tile_cols = cols;
    tile_size = size;
    int usable_width = window_width - sidebar_width;
    tile_cols = usable_width / tile_size;

    for(int y = 0; y < tile_rows; y++){
        for (int x = 0; x < tile_cols; x++){
            tilemap[y][x].filled = false;
        }
    }
}

void tilemap_handle_input(){
    int mx, my;
    Uint32 current_mouse_state = SDL_GetMouseState(&mx, &my);
    if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

        int col = mx / tile_size;
        int row = my / tile_size;

        if (row >= 0 && row < tile_rows && col >= 0 && col < tile_cols) {
            tilemap[row][col].color = get_current_color();
            tilemap[row][col].filled = true;
        }
    }

    previous_mouse_state = current_mouse_state;
}

void tilemap_render(SDL_Renderer *renderer){
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
}



/* Not known if needed
    

*/