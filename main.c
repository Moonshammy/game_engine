#include <SDL2/SDL.h>
#include <stdlib.h>
#include "engine.h"
#include "editor.h"
#include "font.h"
#include "text.h"
#include "tilemap.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


int main(int argc, char *argv[]) {
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    SDL_Log("Complied with SDL Version %d.%d.%d", compiled.major,compiled.minor,compiled.patch);
    SDL_Log("Linked with SDL Version %d.%d.%d", linked.major,linked.minor,linked.patch);

    if (!engine_init("My Little Engine", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    editor_init(WINDOW_WIDTH, WINDOW_HEIGHT);
    font_init();
    tilemap_init(WINDOW_WIDTH, WINDOW_HEIGHT);

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
