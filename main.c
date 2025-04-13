#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "engine.h"
#include "editor.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main(int argc, char *argv[]) {
    if (!engine_init("Editor", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    editor_init(20,25,32);

    while (engine_is_running()) {
        engine_update();

        float dt = get_engine_delta_time();
        editor_handle_input();
        editor_update(dt);

        SDL_Renderer *renderer = get_engine_renderer();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        editor_render();
        SDL_Delay(16); // Roughly 60 FPS
        SDL_RenderPresent(renderer);
    }

    engine_shutdown();
    return 0;
}
