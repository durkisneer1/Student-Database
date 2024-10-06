#pragma once

#include "Utils.hpp"
#include "Math.hpp"

class MajorSelect
{
public:
    MajorSelect(
        Vector2f pos,
        const EntityInfo &idleOptionImageInfo,
        const EntityInfo &selectOptionImageInfo,
        const EntityInfo &optionTextInfo,
        float scaleFactor);

    void draw(SDL_Renderer *renderer);
    void setDstRect(SDL_Rect srcRect, SDL_FRect &dstRect, float scale);
    bool collide(SDL_FPoint mousePos) { return SDL_PointInFRect(&mousePos, &imgDstRect); };
    void setTextPos();

    bool selected = false;
    std::string major;

private:
    Vector2f pos;

    SDL_Texture *idleImgTexture;
    SDL_Texture *selectImgTexture;
    SDL_Texture *currImgTexture = idleImgTexture;
    SDL_Rect imgSrcRect = {0, 0, 0, 0};
    SDL_FRect imgDstRect = {0, 0, 0, 0};

    SDL_Texture *textTexture;
    SDL_Rect textSrcRect = {0, 0, 0, 0};
    SDL_FRect textDstRect = {0, 0, 0, 0};

    std::string buttonText;
};