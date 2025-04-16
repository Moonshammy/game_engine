#include <SDL2/SDL.h>
#include <stdlib.h>
#include "engine.h"
#include "editor.h"
#include "font.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


int main(int argc, char *argv[]) {
    if (!engine_init("My Little Engine", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    editor_init(WINDOW_WIDTH, WINDOW_HEIGHT);
    font_init();

    while (engine_is_running()) {
        engine_update();

        float dt = engine_get_delta_time();
        editor_handle_input();
        editor_update(dt);

        SDL_Renderer *renderer = engine_get_renderer();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        editor_render();
        SDL_Delay(16); // Roughly 60 FPS
        SDL_RenderPresent(renderer);
    }
    font_shutdown();
    engine_shutdown();
    return 0;
}
