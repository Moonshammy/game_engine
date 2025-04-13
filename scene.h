#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "scene_button.h"

typedef enum {
    SCENE_MENU,
    SCENE_GAMEPLAY,
    SCENE_CUTSCENE
} SceneType;

typedef struct {
    char name[64];
    SceneType type;
    bool is_interactive;
    int next_scene_index;
    int button_count;
    SceneButton* buttons;
} Scene;

void scene_init();
void scene_update(float dt);
void scene_render();
void scene_handle_input();

void scene_add(Scene scene);
Scene* scene_get(int index);
int scene_get_count();

#endif