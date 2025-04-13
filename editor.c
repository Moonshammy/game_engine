#include "editor.h"
#include "engine.h"
#include <SDL2/SDL.h>

static int tile_rows = 0;
static int tile_cols = 0;
static int tile_size = 32;

void editor_init(int rows, int cols, int size){
    tile_rows = rows;
    tile_cols = cols;
    tile_size = size;
}

void editor_handle_input() {
    //TODO
}

void editor_update(float dt){
    //TODO
}

void editor_render(){
    SDL_Renderer *renderer = get_engine_renderer();
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

    for (int y = 0; y < tile_rows; y++) {
        for (int x = 0; x < tile_cols; x++) {
            SDL_Rect cell = {x * tile_size, y * tile_size, tile_size, tile_size};
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}