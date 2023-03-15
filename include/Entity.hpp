#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"


struct EntityInfo {
    SDL_Texture *texture;
    int w, h;
};


class Entity {
public:
    Entity(Vector2f pos, EntityInfo entityInfo, int scaleFactor);

    Vector2f getPos() {
        return pos;
    }
    SDL_Texture *getTexture();
    SDL_Rect getSrcRect();
    SDL_Rect getDstRect();
    bool isColliding(SDL_Point mousePos);
private:
    Vector2f pos;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_Texture *texture;
};