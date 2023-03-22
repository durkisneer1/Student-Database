#pragma once

#include "Text.hpp"


class Button {
public:
    Button(Vector2f pos, EntityInfo buttonImageInfo, EntityInfo buttonTextInfo, float scaleFactor);
    void setDstRect(SDL_Rect srcRect, SDL_FRect &dstRect, float scale);

    void animateHover(SDL_FPoint mousePos);
    void animateHide(float maxHeight);
    void animateShow();
    void draw(SDL_Renderer *renderer);

    Vector2f getPos() { return currentPos; }
    SDL_FRect getDstRect() { return imgDstRect; }
    void setTextPos();
    void resetExponent() { exponent = 0; }

    bool isHovered(SDL_FPoint mousePos) { return SDL_PointInFRect(&mousePos, &imgDstRect); }
    bool hide = false;
    bool hidden = false;
private:
    Vector2f currentPos;
    Vector2f idlePos;
    Vector2f hoveredPos;

    SDL_Texture *imgTexture;
    SDL_Rect imgSrcRect = {0, 0, 0, 0};
    SDL_FRect imgDstRect = {0, 0, 0, 0};

    SDL_Texture *textTexture;
    SDL_Rect textSrcRect = {0, 0, 0, 0};
    SDL_FRect textDstRect = {0, 0, 0, 0};

    float exponent = 0;
    bool clickable = true;
};