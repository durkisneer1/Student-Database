#pragma once

#include "Entity.hpp"


class Text {
public:
    Text(Vector2f pos, TTF_Font *font, float scaleFactor, SDL_Renderer *renderer, const std::string &text);
    void generateText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text);
    void centerDstRect();

    void animateWave(float amplitude, float frequency, bool x, bool y);
    void animateHide();
    void animateShow();
    void draw(SDL_Renderer *renderer) { SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect); };

    void resetExponent() { exponent = 0; }

    bool hide = false;
    bool hidden = false;
private:
    Vector2f currentPos;
    Vector2f originalPos;
    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_FRect dstRect = {0, 0, 0, 0};
    SDL_Texture *texture = nullptr;
    float scaleFactor;
    float theta = 0;
    float exponent = 0;
};
