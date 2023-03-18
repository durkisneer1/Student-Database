#include "../include/Text.hpp"


Text::Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: Entity(pos, entityInfo, scaleFactor) {}

void Text::animateWave(SDL_Renderer *renderer, float amplitude, float frequency, bool x, bool y) {
    SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect);
    if (y)
        dstRect.y = currentPos.y + sinf((float)(theta * (M_PI / 180))) * amplitude;
    if (x)
        dstRect.x = currentPos.x + cosf((float)(theta * (M_PI / 180))) * amplitude;
    theta += frequency;
    if (theta >= 360)
        theta = 0;
}

void Text::animateHide(float minHeight) {
    if (currentPos.y <= minHeight - dstRect.h) {
        return;
    }
    currentPos.y -= powf(1.1, exponent);
    exponent += 1.2;
    dstRect.y -= powf(1.1, exponent);
}
