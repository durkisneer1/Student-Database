#include "../include/Entity.hpp"


Entity::Entity(float x, float y, SDL_Texture* texture)
: x(x), y(y), texture(texture) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 1200;
    currentFrame.h = 1200;
}

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}