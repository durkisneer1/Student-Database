#include "../include/Button.hpp"

Button::Button(Vector2f pos, EntityInfo buttonImageInfo, EntityInfo buttonTextInfo, float scaleFactor)
: currentPos(pos), imgTexture(buttonImageInfo.texture), textTexture(buttonTextInfo.texture) {
    this->imgSrcRect = {0, 0, buttonImageInfo.w, buttonImageInfo.h};
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
    if (SDL_PointInFRect(&mousePos, &imgDstRect)) {
        currentPos = hoveredPos;
    } else {
        currentPos = idlePos;
    }
    imgDstRect.y = currentPos.y;
}

void Button::setTextPos() {
    textDstRect.x = currentPos.x + imgDstRect.w / 2;
    textDstRect.y = currentPos.y + imgDstRect.h / 2 - textDstRect.h / 2;
}

void Button::draw(SDL_Renderer *renderer) {
    setTextPos();
    SDL_RenderCopyF(renderer, imgTexture, &imgSrcRect, &imgDstRect);
    SDL_RenderCopyF(renderer, textTexture, &textSrcRect, &textDstRect);
}
