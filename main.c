#include "engine.h"

int main(int argc, char *argv[]) {
    if (!engine_init("My Engine", 800, 600)) {
        return 1;
    }

    while (engine_is_running()) {
        engine_update();
        engine_render();
        SDL_Delay(16); // Roughly 60 FPS
    }

    engine_shutdown();
    return 0;
}
