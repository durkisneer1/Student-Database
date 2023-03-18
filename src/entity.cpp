#include "../include/Entity.hpp"


Entity::Entity(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: currentPos(pos), texture(entityInfo.texture), srcRect{0, 0, entityInfo.w, entityInfo.h}, scaleFactor(scaleFactor) {
    centerDstRect();
}

void Entity::centerDstRect() {
    dstRect.w = (float)srcRect.w * scaleFactor;
    dstRect.h = (float)srcRect.h * scaleFactor;
    currentPos = {currentPos.x - dstRect.w / 2, currentPos.y - dstRect.h / 2};
    dstRect.x = currentPos.x;
    dstRect.y = currentPos.y;
};

void Entity::drawScroll(SDL_Renderer *renderer, float xSpeed, float ySpeed) {
    for (int i = -1; i < 2; i++) {
        dstRect.x = (float)i * dstRect.w + xOffset;
        for (int j = -1; j < 2; j++) {
            dstRect.y = (float)j * dstRect.h + yOffset;
            SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect);
        }
    }
    xOffset += xSpeed;
    yOffset += ySpeed;
    if (xOffset > dstRect.w)
        xOffset = 0;
    if (yOffset > dstRect.h)
        yOffset = 0;
}
