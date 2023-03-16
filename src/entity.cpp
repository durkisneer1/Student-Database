#include "../include/Entity.hpp"


Entity::Entity(Vector2f pos, EntityInfo entityInfo, int scaleFactor)
: currentPos(pos), texture(entityInfo.texture), srcRect{0, 0, entityInfo.w, entityInfo.h}, scaleFactor(scaleFactor) {
    setDstRect();
}

void Entity::setDstRect() {
    dstRect.w = srcRect.w * scaleFactor;
    dstRect.h = srcRect.h * scaleFactor;
    float center_x = getPos().x - (float)(dstRect.w) / 2;
    float center_y = getPos().y - (float)(dstRect.h) / 2;
    idlePos = {center_x, center_y};
    hoveredPos = {center_x, center_y + 10};
    dstRect.x = (int)center_x;
    dstRect.y = (int)center_y;
};

void Entity::update(SDL_Point mousePos) {
    if (SDL_PointInRect(&mousePos, &dstRect)) {
        currentPos = hoveredPos;
    } else {
        currentPos = idlePos;
    }
    dstRect.y = (int)currentPos.y;
}
