#pragma once

#include "Entity.hpp"
#include "Text.hpp"


class Button : public Entity {
public:
    Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
    void animateHover(SDL_FPoint mousePos);
private:
    Vector2f idlePos = currentPos;
    Vector2f hoveredPos = {currentPos.x, currentPos.y + 10};
};