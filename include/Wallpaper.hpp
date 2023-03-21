#pragma once

#include "Utils.hpp"


class Wallpaper {
public:
    Wallpaper(EntityInfo entityInfo, float scaleFactor);
    void scaleDstRect();

    void draw(SDL_Renderer *renderer) { SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect); };
    void animateScroll(SDL_Renderer *renderer, float xSpeed, float ySpeed);
protected:
    SDL_Rect srcRect;
    SDL_FRect dstRect = {0, 0, 0, 0};
    SDL_Texture *texture;
    float scaleFactor;
    float xOffset = 0;
    float yOffset = 0;
};