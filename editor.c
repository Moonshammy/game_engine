#include "editor.h"
#include "engine.h"
#include "font.h"

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
int num_tools; //Used to dictate how many tools can be onscreen due to monitor size

typedef enum {
    MODE_TILEMAP,
    MODE_SCENE,
    MODE_QUIT
} Editor_Mode;

typedef struct {
    SDL_Rect bounds;
    char name[32];
    void (*onclick)();
    bool selected;
}Tool;

//Used 55 to initialize, maximum supported by ultrawide monitors
Tool tools[55];

void editor_init(int window_width, int window_height){
    w_width = window_width;
    w_height = window_height;
    
    int x = tool_padding;
    int y = 0;
    toolbar_width = window_width;
    tool_padding = 10;
    num_tools = window_width / (tool_padding+tool_width);
        
    tools[0] = (Tool){x,y,tool_width,tool_height,"Tilemap",NULL,false}; x = x + tool_padding + tool_width;
    tools[1] = (Tool){x,y,tool_width,tool_height,"Scene",NULL,false}; x = x + tool_padding + tool_width;
    tools[2] = (Tool){x,y,tool_width,tool_height,"Options",NULL,false}; x = x + tool_padding + tool_width;
    tools[3] = (Tool){x,y,tool_width,tool_height,"Quit",NULL,false}; x = x + tool_padding + tool_width;


}

void editor_quit(){
    engine_shutdown();
}

void editor_handle_input(){

}

void editor_update(float dt){

}

void editor_create_text_rect(SDL_Color color, char *name, SDL_Rect rect){
    SDL_Renderer *renderer = engine_get_renderer();
    SDL_Surface* text_surface = TTF_RenderText_Blended(font_get(), name, color);
    if (text_surface){
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);

        int text_w = text_surface->w;
        int text_h = text_surface->h;
        SDL_Rect text_rect = {
            rect.x + (rect.w - text_w) / 2,
            rect.y + (rect.h - text_h) / 2,
            text_w,
            text_h
       };

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    }

}

void editor_render(){
    SDL_Renderer *renderer = engine_get_renderer();
    //Draw Toolbar
    SDL_Rect toolbar = {0,0,toolbar_width,tool_height};
    SDL_SetRenderDrawColor(renderer,45,45,45,225);
    //SDL_RenderDrawRect(renderer,&toolbar);
    SDL_RenderFillRect(renderer,&toolbar);

    for (int i = 0; i <num_tools; i++){
        Tool *button = &tools[i];
        //Fills the tool rectangles
        SDL_SetRenderDrawColor(renderer,79,79,79,255);
        SDL_RenderFillRect(renderer, &button->bounds);
        //Outlines the tool rectangles
        SDL_SetRenderDrawColor(renderer,55,55,55,255);
        SDL_RenderDrawRect(renderer, &button->bounds);

        SDL_Color tooltext_color = {51,255,51,255};
        editor_create_text_rect(tooltext_color, button->name, button->bounds);
        
    }

}