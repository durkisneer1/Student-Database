#pragma once

#include "Text.hpp"


class Button {
public:
    Button(Vector2f pos, EntityInfo entityInfo, float scaleFactor);

    void animateHover(SDL_FPoint mousePos);
    void animateHide(float maxHeight);
    void animateShow();
    void centerDstRect();
    bool isHovered(SDL_FPoint mousePos) { return SDL_PointInFRect(&mousePos, &dstRect); }
    Vector2f getPos() { return currentPos; }
    SDL_FRect getDstRect() { return dstRect; }

    void setPos(Vector2f pos, SDL_FRect rectReference);
    void resetExponent() { exponent = 0; }
    void draw(SDL_Renderer *renderer) { SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect); };

    bool hide = false;
    bool hidden = false;
private:
    Vector2f currentPos;
    SDL_Rect srcRect;
    SDL_FRect dstRect = {0, 0, 0, 0};
    SDL_Texture *texture;
    float scaleFactor;

    Vector2f idlePos;
    Vector2f hoveredPos;
    float exponent = 0;
    bool clickable = true;
};