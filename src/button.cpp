#include "../include/Button.hpp"

Button::Button(Vector2f pos, EntityInfo buttonImageInfo, EntityInfo buttonTextInfo, float scaleFactor) {
    this->currentPos = pos;

    this->imgTexture = buttonImageInfo.texture;
    this->imgSrcRect = {0, 0, buttonImageInfo.w, buttonImageInfo.h};

    this->textTexture = buttonTextInfo.texture;
    this->textSrcRect = {0, 0, buttonTextInfo.w, buttonTextInfo.h};

    setDstRect(imgSrcRect, imgDstRect, scaleFactor);
    setDstRect(textSrcRect, textDstRect, scaleFactor * 0.6f);
    idlePos = currentPos;
    hoveredPos = {idlePos.x, idlePos.y + 10};
}

void Button::setDstRect(SDL_Rect srcRect, SDL_FRect &dstRect, float scale) {
    dstRect.w = (float)srcRect.w * scale;
    dstRect.h = (float)srcRect.h * scale;
    currentPos = {currentPos.x - dstRect.w / 2, currentPos.y - dstRect.h / 2};
    dstRect.x = currentPos.x;
    dstRect.y = currentPos.y;
}

void Button::animateHover(SDL_FPoint mousePos) {
    if (clickable) {
        if (SDL_PointInFRect(&mousePos, &imgDstRect)) {
            currentPos = hoveredPos;
        } else {
            currentPos = idlePos;
        }
        imgDstRect.y = currentPos.y;
    }
}

void Button::setTextPos() {
    textDstRect.x = currentPos.x + imgDstRect.w / 2;
    textDstRect.y = currentPos.y + imgDstRect.h / 2 - textDstRect.h / 2;
}

void Button::animateHide(float maxHeight) {
    if (currentPos.y > maxHeight) {
        hidden = true;
        return;
    }
    clickable = false;
    currentPos.y += powf(2, exponent);
    imgDstRect.y = currentPos.y;
    exponent += 0.2;
}

void Button::animateShow() {
    if (currentPos.y < idlePos.y) {
        clickable = true;
        return;
    }
    hidden = false;
    currentPos.y -= powf(2, exponent);
    imgDstRect.y = currentPos.y;
    exponent -= 0.2;
}

void Button::draw(SDL_Renderer *renderer) {
    setTextPos();
    SDL_RenderCopyF(renderer, imgTexture, &imgSrcRect, &imgDstRect);
    SDL_RenderCopyF(renderer, textTexture, &textSrcRect, &textDstRect);
}
