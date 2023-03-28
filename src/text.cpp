#include "../include/Text.hpp"


Text::Text(Vector2f pos, TTF_Font *font, float scaleFactor, SDL_Renderer *renderer, const std::string &text)
: currentPos(pos), scaleFactor(scaleFactor), originalPos(pos) {
    generateText(renderer, font, text);
}

void Text::centerDstRect() {
    dstRect.w = (float)srcRect.w * scaleFactor;
    dstRect.h = (float)srcRect.h * scaleFactor;
    currentPos = {originalPos.x - dstRect.w / 2, originalPos.y - dstRect.h / 2};
    dstRect.x = currentPos.x;
    dstRect.y = currentPos.y;
}

void Text::animateWave(float amplitude, float frequency, bool x, bool y) {
    if (y)
        dstRect.y = currentPos.y + sinf((float)(theta * (M_PI / 180))) * amplitude;
    if (x)
        dstRect.x = currentPos.x + cosf((float)(theta * (M_PI / 180))) * amplitude;
    theta += frequency;
    if (theta >= 360)
        theta = 0;
}

void Text::generateText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text) {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);

    SDL_Surface *shadowSurface = TTF_RenderText_Solid(font, text.c_str(), {7, 54, 66});
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), {253, 246, 227});
    SDL_Surface *dstSurface = SDL_CreateRGBSurface(0, textSurface->w + 2, textSurface->h + 2, 32,
                                                     0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

    SDL_Rect textRect = {2, 2, textSurface->w, textSurface->h};
    SDL_BlitSurface(shadowSurface, nullptr, dstSurface, &textRect);
    SDL_BlitSurface(textSurface, nullptr, dstSurface, nullptr);
    srcRect = {0, 0, dstSurface->w, dstSurface->h};
    texture = SDL_CreateTextureFromSurface(renderer, dstSurface);
    centerDstRect();

    SDL_FreeSurface(shadowSurface);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(dstSurface);
}
