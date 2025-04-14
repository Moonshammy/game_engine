#include "engine.h"

#include <stdbool.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static bool running = false;

static Uint64 last_time = 0;
static float delta_time = 0.0f;
static int window_width;
static int window_height;

bool engine_init(const char *title, int width, int height) {
    window_width = width;
    window_height = height;
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    running = true;
    return true;
}

void engine_update() {
    //gets and sets system times to utilize for delta time
    Uint64 now = SDL_GetPerformanceCounter();
    if(last_time == 0) last_time = now;
    Uint64 freq = SDL_GetPerformanceFrequency();

    //uses the system times to set the delta_time
    delta_time = (float)(now - last_time) / (float)(freq);
    last_time = now;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void engine_render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Add rendering here in future steps

    SDL_RenderPresent(renderer);
}

void engine_shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    running = false;
    SDL_Quit();
}

bool engine_is_running() {
    return running;
}

SDL_Renderer* get_engine_renderer() {
    return renderer;
}

float get_engine_delta_time(){
    return delta_time;
}

int get_engine_window_width(){
    return window_width;
}

int get_engine_window_height(){
    return window_height;
}
