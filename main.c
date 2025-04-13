#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "engine.h"
#include "bubble.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char *argv[]) {
    if (!engine_init("My Engine", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    Bubble bubble;
    srand((unsigned int)time(NULL));
    bubble_init(&bubble, 400.0f, 300.0f, 250.0f, 25.0f);

    while (engine_is_running()) {
        engine_update();

        float dt = get_engine_delta_time();
        bubble_update(&bubble, dt, WINDOW_WIDTH, WINDOW_HEIGHT);

        SDL_Renderer *renderer = get_engine_renderer();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        bubble_render(renderer, &bubble);

        SDL_Delay(16); // Roughly 60 FPS
        SDL_RenderPresent(renderer);
    }

    engine_shutdown();
    return 0;
}
