#include "tilemap.h"
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

typedef struct{
    char tool_name[32];
    void (*on_click)();  // Function pointer to execute when clicked
    bool selected;
}ToolSlot;

enum Channel { CHANNEL_R = 0, CHANNEL_G = 1, CHANNEL_B = 2 };

//FIXME!
//static ToolSlot slotmap[MAX_ROWS_TOOLS][MAX_COLS_TOOLS];


static Tile tilemap[MAX_ROWS][MAX_COLS];
static int tile_rows = 0;
static int tile_cols = 0;
static int tile_size = 32;

static int previous_mouse_state = 0;

static int window_width;
static int window_height;


void tilemap_init(){
    window_width = get_engine_window_width();
    window_height = get_engine_window_height();


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
        if (my > toolbar_height_start){ //prevents first row from being selected from tool bar

            int col = mx / tile_size;
            int row = (my-toolbar_height_start) / tile_size;

            if (row >= 0 && row < tile_rows && col >= 0 && col < tile_cols) {
                tilemap[row][col].color = get_current_color();
                tilemap[row][col].filled = get_color_fill();
            }
        }
    }
    color_handle_input();
    previous_mouse_state = current_mouse_state;
}

void tilemap_render(SDL_Renderer *renderer){
    for (int y = 0; y < tile_rows; y++) {
        for (int x = 0; x < tile_cols; x++) {
            SDL_Rect cell = { x * tile_size, y * tile_size+toolbar_height_start, tile_size, tile_size };

            if (tilemap[y][x].filled) {
                SDL_Color c = tilemap[y][x].color;
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderFillRect(renderer, &cell);
            }

            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &cell);
            SDL_Rect sidebar = {window_width - SIDEBAR_WIDTH, toolbar_height_start, SIDEBAR_WIDTH, window_height};
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark gray sidebar
            SDL_RenderFillRect(renderer, &sidebar);  
            color_render(renderer);
        }
    }
}