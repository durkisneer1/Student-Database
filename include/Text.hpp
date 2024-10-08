#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Math.hpp"

class Text
{
public:
    Text(Vector2f pos, TTF_Font *font, float scaleFactor, SDL_Renderer *renderer, const std::string &text);
    void generateText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text);
    void centerDstRect();

    void animateWave(float amplitude, float frequency, bool x, bool y);
    void draw(SDL_Renderer *renderer) { SDL_RenderCopyF(renderer, texture, &srcRect, &dstRect); };
    void clear(SDL_Renderer *renderer, TTF_Font *font);

private:
    Vector2f currentPos;
    Vector2f originalPos;
    SDL_Texture *texture = nullptr;
    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_FRect dstRect = {0, 0, 0, 0};
    float scaleFactor;
    float theta = 0;
};
