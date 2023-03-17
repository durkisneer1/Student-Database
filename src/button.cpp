#include "../include/Button.hpp"

Button::Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: Entity(pos, entityInfo, scaleFactor) {}

void Button::animateHover(SDL_FPoint mousePos) {
    if (SDL_PointInFRect(&mousePos, &dstRect)) {
        currentPos = hoveredPos;
    } else {
        currentPos = idlePos;
    }
    dstRect.y = currentPos.y;
}