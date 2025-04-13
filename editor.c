#include "editor.h"
#include "engine.h"
#include <SDL2/SDL.h>

#define MAX_ROWS 100
#define MAX_COLS 100

static int tilemap[MAX_ROWS][MAX_COLS];

static int tile_rows = 0;
static int tile_cols = 0;
static int tile_size = 32;

static int previous_mouse_state = 0;




void editor_init(int rows, int cols, int size){
    tile_rows = rows;
    tile_cols = cols;
    tile_size = size;

    for(int y = 0; y < tile_rows; y++){
        for (int x = 0; x < tile_cols; x++){
            tilemap[y][x] = 0;
        }
    }
}

void editor_handle_input() {
    int mouse_x, mouse_y;
    Uint32 current_mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
    
    if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) && !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

        if (current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            int col = mouse_x / tile_size;
            int row = mouse_y / tile_size;
            int valid = tilemap[row][col];

            if (row >= 0 && row < tile_rows && col >= 0 && col < tile_cols){
                if (valid == 0){tilemap[row][col] = 1;}
                else {tilemap[row][col] = 0;}
            }
        }
    }
    previous_mouse_state = current_mouse_state;
}

void editor_update(float dt){
    //TODO
}

void editor_render(){
    SDL_Renderer *renderer = get_engine_renderer();

    for (int y = 0; y < tile_rows; y++) {
        for (int x = 0; x < tile_cols; x++) {
            SDL_Rect cell = {x * tile_size, y * tile_size, tile_size, tile_size};

            int tile_id = tilemap[y][x];
            if (tile_id == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}