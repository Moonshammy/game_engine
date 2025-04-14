#include "scene_button.h"
#include "engine.h"
#include <SDL2/SDL_ttf.h>
#include <string.h>

void scene_button_render(SDL_Renderer* renderer, TTF_Font* font, SceneButton* button) {
    SDL_SetRenderDrawColor(renderer, button->hovered ? 180 : 100, 100, 255, 255);
    SDL_RenderFillRect(renderer, &button->bounds);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &button->bounds);

    if (!font) return;

    SDL_Color text_color = {255, 255, 255, 255};
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, button->label, text_color);
    if (!text_surface) return;

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    int text_w = text_surface->w;
    int text_h = text_surface->h;
    SDL_Rect text_rect = {
        button->bounds.x + (button->bounds.w - text_w) / 2,
        button->bounds.y + (button->bounds.h - text_h) / 2,
        text_w,
        text_h
    };

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

bool scene_button_check_click(SceneButton* button, int mx, int my) {
    return (mx >= button->bounds.x && mx <= button->bounds.x + button->bounds.w &&
            my >= button->bounds.y && my <= button->bounds.y + button->bounds.h);
}

bool scene_button_check_hover(SceneButton* button, int mx, int my) {
    return scene_button_check_click(button, mx, my);
}
