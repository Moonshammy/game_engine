#include "scene.h"
#include "engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SCENES 64

static TTF_Font* ui_font = NULL;

static Scene scenes[MAX_SCENES];
static int scene_count = 0;
static int current_scene_index = 0;

void scene_init() {
    scene_count = 0;
    current_scene_index = 0;

    ui_font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    if (!ui_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

void scene_add(Scene scene) {
    if (scene_count < MAX_SCENES) {
        scenes[scene_count++] = scene;
    }
}

Scene* scene_get(int index) {
    if (index >= 0 && index < scene_count) {
        return &scenes[index];
    }
    return NULL;
}

int scene_get_count() {
    return scene_count;
}

void scene_update(float dt) {
    // Placeholder for animations, timers, etc.
}

void scene_handle_input() {
    Scene* scene = &scenes[current_scene_index];
    if (!scene->is_interactive || scene->button_count == 0) return;

    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);

    for (int i = 0; i < scene->button_count; i++) {
        SceneButton* btn = &scene->buttons[i];
        btn->hovered = scene_button_check_hover(btn, mx, my);

        if ((mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) && scene_button_check_click(btn, mx, my)) {
            current_scene_index = btn->target_scene_index;
        }
    }
}

void scene_render() {
    SDL_Renderer* renderer = get_engine_renderer();
    Scene* scene = &scenes[current_scene_index];

    for (int i = 0; i < scene->button_count; i++) {
        scene_button_render(renderer, ui_font, &scene->buttons[i]);
    }
}