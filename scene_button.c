#include "scene_button.h"
#include "engine.h"
#include <SDL2/SDL_ttf.h>
#include <string.h>

void scene_button_render(SDL_Renderer* renderer, SceneButton* button) {
    SDL_SetRenderDrawColor(renderer, button->hovered ? 200 : 100, 100, 255, 255);
    SDL_RenderFillRect(renderer, &button->bounds);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &button->bounds);

    // Text rendering omitted — can be added using SDL_ttf
}

bool scene_button_check_click(SceneButton* button, int mx, int my) {
    return (mx >= button->bounds.x && mx <= button->bounds.x + button->bounds.w &&
            my >= button->bounds.y && my <= button->bounds.y + button->bounds.h);
}

bool scene_button_check_hover(SceneButton* button, int mx, int my) {
    return scene_button_check_click(button, mx, my);
}
