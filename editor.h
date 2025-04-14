#ifndef EDITOR_H
#define EDITOR_H

void editor_init();
void switch_to_tilemap();
void switch_to_scene();
void switch_to_option();
void quit_editor();
int get_toolbar_height();
void editor_handle_input();
void editor_update(float dt);
void editor_render();

#endif