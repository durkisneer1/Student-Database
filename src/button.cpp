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

void Button::setPos(Vector2f pos, SDL_FRect rectReference) {
    dstRect.x = pos.x + rectReference.w / 2 - dstRect.w / 2;
    dstRect.y = pos.y + rectReference.h / 2 - dstRect.h / 2;
}

void Button::animateHide(float maxHeight) {
    if (currentPos.y >= maxHeight + dstRect.h / 2) {
        hidden = true;
        return;
    }
    currentPos.y += powf(1.1, exponent);
    exponent += 1.2;
    dstRect.y = currentPos.y;
}

void Button::animateShow() {
    if (currentPos.y <= originalPos.y + dstRect.h / 4) {
        clicked = false;
        hidden = false;
        return;
    }
    currentPos.y -= powf(1.1, exponent);
    exponent += 1.2;
    dstRect.y = currentPos.y;
}
