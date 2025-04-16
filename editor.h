#ifndef EDITOR_H
#define EDITOR_H

void editor_init(int window_width, int window_height);
void editor_quit();
void editor_handle_input();
void editor_update(float dt);
void editor_render();

#endif