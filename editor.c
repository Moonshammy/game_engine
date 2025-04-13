#include "editor.h"
#include "engine.h"
#include "color.h"
#include "scene.h"
#include "tilemap.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SIDEBAR_WIDTH 300
#define SIDEBAR_PADDING 10


typedef enum {
    EDITOR_MODE_TILEMAP,
    EDITOR_MODE_SCENE,
    EDITOR_MODE_COLOR
} EditorMode;

static EditorMode current_mode = EDITOR_MODE_SCENE;
static int previous_mouse_state = 0;

void editor_init(){
    scene_init();
    tilemap_init(20,25,36,SIDEBAR_WIDTH);
}

void editor_handle_input() {
    if (current_mode == EDITOR_MODE_SCENE) {
        scene_handle_input();
    }

    else if(current_mode == EDITOR_MODE_COLOR){
        color_handle_input();
    }
    
    else if (current_mode == EDITOR_MODE_TILEMAP) {
         tilemap_handle_input();
    }
}

void editor_update(float dt){
    if (current_mode == EDITOR_MODE_SCENE) {
        scene_update(dt);
    }
}

void editor_render() {

    int window_width = get_engine_window_width();
    int window_height = get_engine_window_height();
    SDL_Renderer *renderer = get_engine_renderer();
    

    if (current_mode == EDITOR_MODE_SCENE) {
        scene_render();
    }
    
    if (current_mode == EDITOR_MODE_TILEMAP) {
        scene_render(renderer);
        SDL_Rect sidebar = {window_width - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, window_height};
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark gray sidebar
        SDL_RenderFillRect(renderer, &sidebar);  
    }

    
}
