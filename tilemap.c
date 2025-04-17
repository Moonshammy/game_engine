#include "tilemap.h"
#include "editor.h"
#include "engine.h"
//#include "color.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

int window_width;
int window_height;

int tiles_width;
int tiles_height;
int tiles_size;

int start_x;
int start_y;
int boundary_x;
int boundary_y;

typedef struct{
    bool filled;
    SDL_Color fill;
    SDL_Color outline;
    SDL_Rect rect;
}Tile;

Tile tiles[100][100];

void tilemap_init(int width, int height){
    window_width = width;
    window_height = height;
    start_y = editor_get_toolbar()->h;
    start_x = 0;
    boundary_y = window_height;
    boundary_x = window_width - editor_get_sidebar()->w;

    //Rest of init is broken
    tiles_width = (boundary_x - start_x) / 32;
    tiles_height = (boundary_y - start_y) / 32;
    tiles_size = 32;

    for (int x = 0; x < tiles_width; x++){
        int x_pos = (x*tiles_size) + start_x;
        for (int y = 0; y < tiles_height; y++){
            int y_pos = (y*tiles_size) + start_y;
            tiles[x][y] = (Tile){
                false,
                0,0,0,255, 
                200,200,200,255,
                x_pos,y_pos,tiles_size,tiles_size
            };
        }
    }
}

void tilemap_draw_tiles(SDL_Renderer *renderer, SDL_Color f, SDL_Color o, SDL_Rect r){
    SDL_SetRenderDrawColor(renderer, f.r,f.b,f.g,f.a);
    SDL_RenderFillRect(renderer,&r);

    SDL_SetRenderDrawColor(renderer, o.r,o.b,o.g,o.a);
    SDL_RenderDrawRect(renderer, &r);
}

void tilemap_set_tiles_width(int width);
void tilemap_set_tiles_height(int height);
void tilemap_set_tiles_dimensions(int width, int height);
void tilemap_set_size(int size);

void tilemap_handle_input(){

}

void tilemap_render(){
    SDL_Renderer *renderer = engine_get_renderer();

    //Not sure this is drawing properly
    for (int x = 0; x < tiles_width; x++){
        for(int y = 0; y < tiles_height; y++){
            Tile tile = tiles[x][y];
            SDL_Color o = tile.outline;
            SDL_SetRenderDrawColor(renderer, tile.fill.r,tile.fill.g,tile.fill.b,tile.fill.a);
            SDL_RenderFillRect(renderer, &tile.rect);

            SDL_SetRenderDrawColor(renderer, o.r, o.g, o.b, o.r);
            SDL_RenderDrawRect(renderer, &tile.rect);
        }
    }
}