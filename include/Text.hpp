#pragma once

#include "Entity.hpp"


class Text : public Entity {
public:
    Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
    void waveVertical(SDL_Renderer *renderer, float amplitude, float frequency);
private:
    float theta = 0;
};