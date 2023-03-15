#include <tuple>

#include "../include/Entity.hpp"


Entity::Entity(Vector2f pos, EntityInfo entityInfo, int scaleFactor)
: pos(pos), texture(entityInfo.texture), srcRect{0, 0, entityInfo.w, entityInfo.h} {
    float new_x = getPos().x - (float)(srcRect.w * scaleFactor) / 2;
    float new_y = getPos().y - (float)(srcRect.h * scaleFactor) / 2;
    dstRect.x = (int)new_x;
    dstRect.y = (int)new_y;
    dstRect.w = srcRect.w * scaleFactor;
    dstRect.h = srcRect.h * scaleFactor;
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

SDL_Rect Entity::getSrcRect() {
    return srcRect;
}

SDL_Rect Entity::getDstRect() {
    return dstRect;
}

bool Entity::isColliding(SDL_Point mousePos) {
    return SDL_PointInRect(&mousePos, &dstRect);
}