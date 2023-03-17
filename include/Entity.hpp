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

    SDL_Texture *getTexture() { return texture; };
    SDL_Rect getSrcRect() { return srcRect; };
    void centerDstRect();
    SDL_FRect getDstRect() { return dstRect; };
    float xOffset = 0;
    float yOffset = 0;
protected:
    Vector2f currentPos;
    SDL_Rect srcRect;
    SDL_FRect dstRect = {0, 0, 0, 0};
    SDL_Texture *texture;
    float scaleFactor;
};