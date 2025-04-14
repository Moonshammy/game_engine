#ifndef SCENE_BUTTON_H
#define SCENE_BUTTON_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    SDL_Rect bounds;
    char label[32];
    int target_scene_index;
    bool hovered;
} SceneButton;

void scene_button_render(SDL_Renderer* renderer, TTF_Font* font, SceneButton* button);
bool scene_button_check_click(SceneButton* button, int mx, int my);
bool scene_button_check_hover(SceneButton* button, int mx, int my);

#endif