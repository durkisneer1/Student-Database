#include <iostream>
#include <vector>

#include "../include/RenderWindow.hpp"


RenderWindow::RenderWindow(const std::string &title, int width, int height)
: window(), renderer() {
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

EntityInfo RenderWindow::loadImageInfo(const std::string &filePath) {
    SDL_Texture *texture;
    int w, h;
    texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (texture == nullptr)
        std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    return EntityInfo{texture, w, h};
}

EntityInfo RenderWindow::loadTextInfo(const std::string &text, TTF_Font *font, SDL_Color color) {
    SDL_Texture *texture;
    int w, h;
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
        std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_FreeSurface(surface);
    return EntityInfo{texture, w, h};
}

void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_FPoint RenderWindow::getMousePos() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return {(float)x, (float)y};
}

void RenderWindow::draw(Entity &entity) {
    SDL_Rect srcRect = entity.getSrcRect();
    SDL_FRect dstRect = entity.getDstRect();
    SDL_RenderCopyF(renderer, entity.getTexture(), &srcRect, &dstRect);
}

void RenderWindow::scroll(Entity &entity) {
    SDL_Rect srcRect = entity.getSrcRect();
    SDL_FRect dstRect = entity.getDstRect();
    for (int i = -1; i < 1; i++) {
        dstRect.x = (float)i * dstRect.w + entity.xOffset;
        for (int j = -1; j < 1; j++) {
            dstRect.y = (float)j * dstRect.h + entity.yOffset;
            SDL_RenderCopyF(renderer, entity.getTexture(), &srcRect, &dstRect);
        }
    }
    entity.xOffset += 0.5;
    entity.yOffset += 0.5;
    if (entity.xOffset > dstRect.w)
        entity.xOffset = 0;
    if (entity.yOffset > dstRect.h)
        entity.yOffset = 0;
}
