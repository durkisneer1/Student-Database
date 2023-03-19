#include "../include/Text.hpp"


Text::Text(Vector2f pos, TTF_Font *font, float scaleFactor, SDL_Renderer *renderer, const std::string &text)
: currentPos(pos), scaleFactor(scaleFactor), originalPos(pos) {
    generateText(renderer, font, text);
    centerDstRect();
}

void Text::centerDstRect() {
    dstRect.w = (float)srcRect.w * scaleFactor;
    dstRect.h = (float)srcRect.h * scaleFactor;
    currentPos = {currentPos.x - dstRect.w / 2, currentPos.y - dstRect.h / 2};
    dstRect.x = currentPos.x;
    dstRect.y = currentPos.y;
};

void Text::animateWave(float amplitude, float frequency, bool x, bool y) {
    if (y)
        dstRect.y = currentPos.y + sinf((float)(theta * (M_PI / 180))) * amplitude;
    if (x)
        dstRect.x = currentPos.x + cosf((float)(theta * (M_PI / 180))) * amplitude;
    theta += frequency;
    if (theta >= 360)
        theta = 0;
}

void Text::animateHide() {
    if (currentPos.y <= -dstRect.h) {
        hidden = true;
        return;
    }
    currentPos.y -= powf(1.1, exponent);
    exponent += 1.2;
    dstRect.y -= powf(1.1, exponent);
}

void Text::animateShow() {
    if (currentPos.y >= originalPos.y - dstRect.h / 2) {
        hidden = false;
        return;
    }
    currentPos.y += powf(1.1, exponent);
    exponent += 1.2;
    dstRect.y += powf(1.1, exponent);
}

void Text::generateText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text) {
    SDL_Surface *shadowSurface = TTF_RenderText_Solid(font, text.c_str(), {0, 43, 54});
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), {238, 232, 213});
    SDL_Surface *dstSurface = SDL_CreateRGBSurface(0, shadowSurface->w + 2, shadowSurface->h + 2, 32,
                                                     0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    SDL_Rect textRect = {2, 2, shadowSurface->w, shadowSurface->h};
    SDL_BlitSurface(shadowSurface, nullptr, dstSurface, &textRect);
    SDL_BlitSurface(textSurface, nullptr, dstSurface, nullptr);
    srcRect = {0, 0, dstSurface->w, dstSurface->h};
    texture = SDL_CreateTextureFromSurface(renderer, dstSurface);
    SDL_FreeSurface(shadowSurface);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(dstSurface);
}
