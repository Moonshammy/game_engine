#include "tilemap.h"
#include "editor.h"
#include "engine.h"
#include "font.h"
//#include "color.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

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

typedef struct{
    //int ptsize;
    //char* font[255];
    int value;
    SDL_Rect rect;
    SDL_Color fill;
    SDL_Color outline;
    SDL_Color text_color;
}IntInputBox;

IntInputBox grid_size_button;

//100x100 until redefined
Tile tiles[100][100];

void tilemap_init(int width, int height){
    window_width = width;
    window_height = height;
    start_y = editor_get_toolbar().h;
    start_x = 0;
    boundary_y = window_height;
    boundary_x = window_width - editor_get_sidebar().w;

    //Rest of init is broken
    tiles_width = (boundary_x - start_x) / 32;
    tiles_height = (boundary_y - start_y) / 32;
    tiles_size = 32;

    grid_size_button = (IntInputBox){32, 0,0,30,20, 0,0,0,255, 50,50,50,255, 71,250,71,255};

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
    tilemap_set_tools_pos();
}

void tilemap_set_tiles_width(int width);
void tilemap_set_tiles_height(int height);
void tilemap_set_tiles_dimensions(int width, int height);
void tilemap_set_size(int size);

void tilemap_set_tools_pos(){
    //tool to reset position of tools if sidebar changes for some reason
    SDL_Rect sidebar = editor_get_sidebar();
    int x = sidebar.x + 20;
    int y = sidebar.y + 20;

    grid_size_button.rect.x = x; x = grid_size_button.rect.x + 20;
    grid_size_button.rect.y = y; y = grid_size_button.rect.y + 20;
}


void tilemap_handle_input(){
}

void tilemap_update(){
}

void tilemap_render(){
    SDL_Renderer *renderer = engine_get_renderer();

    //Draws grid to screen
    for (int x = 0; x < tiles_width; x++){
        for(int y = 0; y < tiles_height; y++){
            Tile tile = tiles[x][y];
            editor_fill_draw_rect(tile.rect, tile.fill, tile.outline);
        }
    }

    editor_fill_draw_rect(grid_size_button.rect, grid_size_button.fill, grid_size_button.outline);
}