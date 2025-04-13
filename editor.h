#ifndef EDITOR_H
#define EDITOR_H

void editor_init(int rows, int cols, int tile_size);
void editor_handle_input();
void editor_update(float dt);
void editor_render();

#endif