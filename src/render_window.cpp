#include <iostream>

#include "../include/RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
: window(), renderer() {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
    SDL_Texture* texture;
    texture = IMG_LoadTexture(renderer, filePath);
    if (texture == nullptr)
        std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::cls() {
    SDL_RenderClear(renderer);
}

void RenderWindow::draw(Entity& entity) {
    SDL_Rect srcRect;
    srcRect.x = entity.getCurrentFrame().x;
    srcRect.y = entity.getCurrentFrame().y;
    srcRect.w = entity.getCurrentFrame().w;
    srcRect.h = entity.getCurrentFrame().h;

    SDL_Rect dstRect;
    dstRect.x = (int)entity.getX();
    dstRect.y = (int)entity.getY();
    dstRect.w = srcRect.w / 4;
    dstRect.h = srcRect.h / 4;
    SDL_RenderCopy(renderer, entity.getTexture(), &srcRect, &dstRect);
}

void RenderWindow::flip() {
    SDL_RenderPresent(renderer);
}