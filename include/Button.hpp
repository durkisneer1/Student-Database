#pragma once

#include "Utils.hpp"


class Button {
public:
    Button(Vector2f pos, EntityInfo buttonImageInfo, EntityInfo buttonTextInfo, float scaleFactor);
    void setDstRect(SDL_Rect srcRect, SDL_FRect &dstRect, float scale);

    bool collide(SDL_FPoint mousePos);
    void animateHover(SDL_FPoint mousePos);
    void draw(SDL_Renderer *renderer);
    void setTextPos();
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

    std::string buttonText;
};
