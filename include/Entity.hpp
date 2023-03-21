#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Math.hpp"


struct EntityInfo {
    SDL_Texture *texture;
    int w, h;
};


class Entity {
public:
    Entity(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
    void centerDstRect();

    SDL_FRect getDstRect() { return dstRect; };
    void draw(SDL_Renderer *renderer) { SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect); };
    void animateScroll(SDL_Renderer *renderer, float xSpeed, float ySpeed);
protected:
    Vector2f currentPos;
    SDL_Rect srcRect;
    SDL_FRect dstRect = {0, 0, 0, 0};
    SDL_Texture *texture;
    float scaleFactor;
    float xOffset = 0;
    float yOffset = 0;
};