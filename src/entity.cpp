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
