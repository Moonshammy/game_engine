#ifndef TILEMAP_H
#define TILEMAP_H

void tilemap_init(int rows, int cols, int size, int sidebar_width);
void tilemap_handle_input();
void tilemap_render(SDL_Renderer *renderer);


#endif