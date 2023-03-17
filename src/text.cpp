#include "../include/Text.hpp"


Text::Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor)
: Entity(pos, entityInfo, scaleFactor) {}

void Text::waveVertical(float amplitude, float frequency) {
    dstRect.y = currentPos.y + sinf((float)(theta * (M_PI / 180))) * amplitude;
    theta += frequency;
    if (theta >= 360)
        theta = 0;
}
