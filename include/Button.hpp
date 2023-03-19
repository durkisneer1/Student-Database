#pragma once

#include "Entity.hpp"
#include "Text.hpp"


class Button : public Entity {
public:
    Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor);

    void animateHover(SDL_FPoint mousePos);
    void animateHide(float maxHeight);
    void animateShow();
    void resetExponent() { exponent = 0; }
    Vector2f getPos() { return currentPos; }
    void setPos(Vector2f pos, SDL_FRect rectReference);
    bool isHovered(SDL_FPoint mousePos) { return SDL_PointInFRect(&mousePos, &dstRect); }

    bool clicked = false;
    bool hidden = false;
private:
    Vector2f originalPos = currentPos;
    Vector2f idlePos = currentPos;
    Vector2f hoveredPos = {currentPos.x, currentPos.y + 10};
    float exponent = 0;
};