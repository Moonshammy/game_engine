#include "editor.h"
#include "engine.h"
#include "color.h"
#include "scene.h"
#include "tilemap.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

//These values only get tweaked.
#define TOOLBAR_HEIGHT 40
#define TOOL_HEIGHT TOOLBAR_HEIGHT
#define TOOL_WIDTH 100
#define TOOL_PADDING 8
typedef struct {
    SDL_Rect bounds;
    char label[32];
    void (*on_click)();  // Function pointer to execute when clicked
    bool selected;
} ToolbarButton;

typedef enum {
    EDITOR_MODE_TILEMAP,
    EDITOR_MODE_SCENE,
    EDITOR_MODE_OPTION
} EditorMode;

static int num_tools;

//default 55, since technically an ultrawide could support that many tools... I don't see having more than 15 or so tools ever being displayed.
ToolbarButton toolbar_buttons[55];

static EditorMode current_mode = EDITOR_MODE_SCENE;
static int previous_mouse_state = 0;

static TTF_Font* ui_font = NULL;

void editor_init(){
    num_tools = get_engine_window_width();
    
    int x = TOOL_PADDING;
    int y = 0;    
 
    toolbar_buttons[0] = (ToolbarButton){x, y, TOOL_WIDTH, TOOL_HEIGHT, "Scene", switch_to_scene, false}; x += TOOL_WIDTH + TOOL_PADDING;
    toolbar_buttons[1] = (ToolbarButton){x, y, TOOL_WIDTH, TOOL_HEIGHT, "Tilemap", switch_to_tilemap, false}; x += TOOL_WIDTH + TOOL_PADDING;
    toolbar_buttons[2] = (ToolbarButton){x, y, TOOL_WIDTH, TOOL_HEIGHT, "Option", switch_to_option, false}; x += TOOL_WIDTH + TOOL_PADDING;
    toolbar_buttons[3] = (ToolbarButton){x, y, TOOL_WIDTH, TOOL_HEIGHT, "Quit", quit_editor, false};

    if (TTF_Init() < 0) {
        SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
    }
    
    ui_font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    if (!ui_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    scene_init();
    tilemap_init(20,25,36);
}

//switch_to function used for toolbar buttons
void switch_to_tilemap(){
    current_mode = EDITOR_MODE_TILEMAP;
}
void switch_to_scene(){
    current_mode = EDITOR_MODE_SCENE;
}
void switch_to_option(){
    current_mode = EDITOR_MODE_OPTION;
}
void quit_editor(){
    if (ui_font) {TTF_CloseFont(ui_font);}
    engine_shutdown();
}

//Used for tools to know how far to go down
int get_toolbar_height(){
    return TOOLBAR_HEIGHT;
}


void editor_handle_input() {
    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);

    if ((mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        !(previous_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {

        for (int i = 0; i < num_tools; i++) {
            SDL_Rect *r = &toolbar_buttons[i].bounds;
            if (mx >= r->x && mx <= r->x + r->w &&
                my >= r->y && my <= r->y + r->h) {
                if (toolbar_buttons[i].on_click) {
                    toolbar_buttons[i].on_click();
                }
            }
        }
    }

    previous_mouse_state = mouse;

    if (current_mode == EDITOR_MODE_SCENE) {
        scene_handle_input();
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
    //Establishes window dimensions and renderer to use for later calculations
    int window_width = get_engine_window_width();
    int window_height = get_engine_window_height();
    SDL_Renderer *renderer = get_engine_renderer();

    //Creates toolbar for tools
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_Rect toolbar = {0, 0, window_width, TOOLBAR_HEIGHT};
    SDL_RenderFillRect(renderer, &toolbar);
    
    for (int i = 0; i < num_tools; i++) {
        ToolbarButton *btn = &toolbar_buttons[i];
    
        SDL_SetRenderDrawColor(renderer, 79, 79, 79, 255);
        SDL_RenderFillRect(renderer, &btn->bounds);
    
        SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
        SDL_RenderDrawRect(renderer, &btn->bounds);
    
        SDL_Color text_color = {51, 255, 51, 255};
        SDL_Surface* text_surface = TTF_RenderText_Blended(ui_font, btn->label, text_color);
        if (text_surface) {
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            int text_w = text_surface->w;
            int text_h = text_surface->h;
            SDL_Rect text_rect = {
                btn->bounds.x + (btn->bounds.w - text_w) / 2,
                btn->bounds.y + (btn->bounds.h - text_h) / 2,
                text_w,
                text_h
            };

        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
        }
    }


    if (current_mode == EDITOR_MODE_SCENE) {
        scene_render();
    }
    
    else if (current_mode == EDITOR_MODE_TILEMAP) {
        tilemap_render(renderer);
    }
  
}
