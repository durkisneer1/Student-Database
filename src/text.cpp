#include "../include/Text.hpp"


Text::Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: Entity(pos, entityInfo, scaleFactor) {}

void Text::waveVertical(SDL_Renderer *renderer, float amplitude, float frequency) {
    SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect);
    dstRect.y = currentPos.y + sinf((float)(theta * (M_PI / 180))) * amplitude;
    theta += frequency;
    if (theta >= 360)
        theta = 0;
}
