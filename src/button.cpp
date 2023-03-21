#include "../include/Button.hpp"

Button::Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: currentPos(pos), texture(entityInfo.texture), srcRect{0, 0, entityInfo.w, entityInfo.h}, scaleFactor(scaleFactor) {
    centerDstRect();
    idlePos = currentPos;
    hoveredPos = {idlePos.x, idlePos.y + 10};
}

void Button::centerDstRect() {
    dstRect.w = (float)srcRect.w * scaleFactor;
    dstRect.h = (float)srcRect.h * scaleFactor;
    currentPos = {currentPos.x - dstRect.w / 2, currentPos.y - dstRect.h / 2};
    dstRect.x = currentPos.x;
    dstRect.y = currentPos.y;
}

void Button::animateHover(SDL_FPoint mousePos) {
    if (clickable) {
        if (SDL_PointInFRect(&mousePos, &dstRect)) {
            currentPos = hoveredPos;
        } else {
            currentPos = idlePos;
        }
        dstRect.y = currentPos.y;
    }
}

void Button::setPos(Vector2f pos, SDL_FRect rectReference) {
    dstRect.x = pos.x + rectReference.w / 2 - dstRect.w / 2;
    dstRect.y = pos.y + rectReference.h / 2 - dstRect.h / 2;
}

void Button::animateHide(float maxHeight) {
    if (currentPos.y > maxHeight) {
        hidden = true;
        return;
    }
    clickable = false;
    currentPos.y += powf(2, exponent);
    dstRect.y = currentPos.y;
    exponent += 0.2;
}

void Button::animateShow() {
    if (currentPos.y < idlePos.y) {
        clickable = true;
        return;
    }
    hidden = false;
    currentPos.y -= powf(2, exponent);
    dstRect.y = currentPos.y;
    exponent -= 0.2;
}
