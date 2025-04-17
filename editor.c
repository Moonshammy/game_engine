#include "editor.h"
#include "engine.h"
#include "font.h"
#include "tilemap.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

int w_width;
int w_height;

int toolbar_height = 45;
int toolbar_width;
int tool_height = 45;
int tool_width = 90;
int tool_padding = 10;
int max_tools; //Used to dictate how many tools can be onscreen due to monitor size
int num_tools;

int sidebar_x;
int sidebar_y;
int sidebar_height;
int sidebar_width = 300;

Uint32 previous_mouse_state = 0;

typedef enum {
    MODE_TILEMAP,
    MODE_SCENE,
    MODE_OPTIONS
} Editor_Mode;

typedef struct {
    SDL_Rect bounds;
    char name[32];
    void (*on_click)();
    bool selected;
}Tool;

typedef struct{
    SDL_Rect bounds;
    SDL_Color color;
    char name[32];
    bool active;
} Zones;

Zones toolbar;
Zones sidebar;

Editor_Mode mode = MODE_OPTIONS;

//Used 55 to initialize, maximum supported by ultrawide monitors
Tool tools[55];

void editor_init(int window_width, int window_height){
    w_width = window_width;
    w_height = window_height;
    
    int x = tool_padding;
    int y = 0;
    toolbar_width = window_width;
    tool_padding = 10;
    max_tools = window_width / (tool_padding+tool_width);
    
    toolbar = (Zones){0,0,toolbar_width,tool_height, 45,45,45,225, "Toolbar",true};
    sidebar = (Zones){w_width-sidebar_width, toolbar_height, sidebar_width, w_height-toolbar_height,
        30,30,30,225,"Sidebar",false};

    tools[0] = (Tool){x,y,tool_width,tool_height,"Tilemap",editor_start_tilemap,false}; x = x + tool_padding + tool_width;
    tools[1] = (Tool){x,y,tool_width,tool_height,"Scene",editor_start_scene,false}; x = x + tool_padding + tool_width;
    tools[2] = (Tool){x,y,tool_width,tool_height,"Options",editor_start_options,false}; x = x + tool_padding + tool_width;
    tools[3] = (Tool){x,y,tool_width,tool_height,"Quit",editor_quit,false}; x = x + tool_padding + tool_width;
    num_tools = 4;
}

void editor_quit(){
    engine_shutdown();
}

void editor_start_tilemap(){
    sidebar.active = true;
    mode = MODE_TILEMAP;
}
void editor_start_scene(){
    sidebar.active = false;
    mode = MODE_SCENE;
}
void editor_start_options(){
    sidebar.active = false;
    mode = MODE_OPTIONS;
}

SDL_Rect editor_get_toolbar(){
    return toolbar.bounds;
}
SDL_Rect editor_get_sidebar(){
    return sidebar.bounds;
}
void editor_set_color(SDL_Color c){
    SDL_SetRenderDrawColor(engine_get_renderer(), c.r,c.g,c.b,c.a);
}

void editor_draw_rect(SDL_Rect rect, SDL_Color c){
    editor_set_color(c);
    SDL_RenderDrawRect(engine_get_renderer(), &rect);
}

void editor_fill_rect(SDL_Rect rect, SDL_Color c){
    editor_set_color(c);
    SDL_RenderFillRect(engine_get_renderer(), &rect);
}

void editor_fill_draw_rect(SDL_Rect rect, SDL_Color fill, SDL_Color draw){
    editor_fill_rect(rect, fill);
    editor_draw_rect(rect, draw);
}

void editor_draw_text(SDL_Color color, char *name, SDL_Rect rect){
    SDL_Surface* text_surface = TTF_RenderText_Blended(font_get(), name, color);
    if (text_surface){
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(engine_get_renderer(),text_surface);

        int text_w = text_surface->w;
        int text_h = text_surface->h;
        SDL_Rect text_rect = {
            rect.x + (rect.w - text_w) / 2,
            rect.y + (rect.h - text_h) / 2,
            text_w,
            text_h
       };
    SDL_RenderCopy(engine_get_renderer(), text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    }
}

void editor_handle_input(){
    int mx, my;
    Uint32 current_mouse_state = SDL_GetMouseState(&mx,&my);
    if ((current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) && !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))){
        int y = my;
        int x = mx;
        for (int i = 0; i < num_tools; i++){
            Tool *tool = &tools[i];
            //compares the tool's starting x,y position and uses the tool_width/height to find bounds of each button 
            if(x>=tool->bounds.x && x<=tool->bounds.x+tool_width && y >= tool->bounds.y && y<=tool->bounds.y+tool_height){
                if (tools[i].on_click) {
                    tools[i].on_click();
                }
            }
        }
    }
}

void editor_update(float dt){

}

void editor_render(){
    SDL_Renderer *renderer = engine_get_renderer();
    //Draw Toolbar
    editor_draw_rect(toolbar.bounds, toolbar.color);

    SDL_Color fill ={79,79,79,25};
    SDL_Color draw = {105,105,105,255};
    SDL_Color text = {51,255,51,255};

    for (int i = 0; i <num_tools; i++){
        Tool *button = &tools[i];
        //Fills the tool rectangles
        editor_fill_draw_rect(button->bounds, fill, draw);
        //Adds text to tools
        editor_draw_text(text, button->name, button->bounds);        
    }

    if(sidebar.active){
        SDL_SetRenderDrawColor(renderer, 30,30,30,255);
        SDL_RenderFillRect(renderer, &sidebar.bounds);
    }
    
    switch (mode){
        case MODE_TILEMAP:
            tilemap_render(renderer);
            break;
        case MODE_SCENE:
            break;
        case MODE_OPTIONS:
            break;
    }


}