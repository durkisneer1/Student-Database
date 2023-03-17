#pragma once

#include "Entity.hpp"
#include "Text.hpp"


class Button : public Entity {
public:
    Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
    void animateHover(SDL_FPoint mousePos);
    Vector2f getPos() { return {dstRect.x, dstRect.y}; }
    void setPos(Vector2f pos, SDL_FRect rectReference);
    bool isClicked(SDL_FPoint mousePos) { return SDL_PointInFRect(&mousePos, &dstRect); }
private:
    Vector2f idlePos = currentPos;
    Vector2f hoveredPos = {currentPos.x, currentPos.y + 10};
};