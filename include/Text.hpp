#pragma once

#include "Entity.hpp"


class Text : public Entity {
public:
    Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
    void animateWave(SDL_Renderer *renderer, float amplitude, float frequency, bool x, bool y);
    void animateHide(float minHeight);
    bool hide = false;
private:
    float theta = 0;
    float exponent = 0;
};