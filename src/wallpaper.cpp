#include "Wallpaper.hpp"

Wallpaper::Wallpaper(const EntityInfo &entityInfo, float scaleFactor)
    : texture(entityInfo.texture), srcRect{0, 0, entityInfo.w, entityInfo.h}, scaleFactor(scaleFactor)
{
    scaleDstRect();
}

void Wallpaper::scaleDstRect()
{
    dstRect.w = (float)srcRect.w * scaleFactor;
    dstRect.h = (float)srcRect.h * scaleFactor;
}

void Wallpaper::animateScroll(SDL_Renderer *renderer, float xSpeed, float ySpeed)
{
    for (int i = -1; i < 2; i++)
    {
        dstRect.x = (float)i * dstRect.w + xOffset;
        for (int j = -1; j < 2; j++)
        {
            dstRect.y = (float)j * dstRect.h + yOffset;
            draw(renderer);
        }
    }
    xOffset += xSpeed;
    yOffset += ySpeed;
    if (xOffset > dstRect.w)
        xOffset = 0;
    if (yOffset > dstRect.h)
        yOffset = 0;
}
