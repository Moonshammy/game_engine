#ifndef TILEMAP_H
#define TILEMAP_H

void tilemap_init(int rows, int cols, int size);
void tilemap_handle_input();
void tilemap_render(SDL_Renderer *renderer);


#endif