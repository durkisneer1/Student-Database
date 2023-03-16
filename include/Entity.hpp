#pragma once
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
    Entity(Vector2f pos, EntityInfo entityInfo, int scaleFactor);

    Vector2f getPos() { return currentPos; };
    SDL_Texture *getTexture() { return texture; };
    SDL_Rect getSrcRect() { return srcRect; };
    void setDstRect();
    SDL_FRect getDstRect() { return dstRect; };
    void update(SDL_FPoint mousePos);
    float xOffset = 0;
    float yOffset = 0;
private:
    Vector2f idlePos;
    Vector2f hoveredPos;
    Vector2f currentPos;
    SDL_Rect srcRect;
    SDL_FRect dstRect;
    SDL_Texture *texture;
    int scaleFactor;
};