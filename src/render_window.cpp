#include <iostream>
#include <vector>

#include "../include/RenderWindow.hpp"


RenderWindow::RenderWindow(const char *title, int width, int height)
: window(), renderer() {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

EntityInfo RenderWindow::loadEntityInfo(const char* filePath) {
    SDL_Texture *texture;
    int w, h;
    texture = IMG_LoadTexture(renderer, filePath);
    if (texture == nullptr)
        std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    return EntityInfo{texture, w, h};
}

SDL_Point RenderWindow::getMousePos() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return {x, y};
}

void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::cls() {
    SDL_RenderClear(renderer);
}

void RenderWindow::draw(Entity &entity) {
    SDL_Rect srcRect = entity.getSrcRect();
    SDL_Rect dstRect = entity.getDstRect();
    SDL_RenderCopy(renderer, entity.getTexture(), &srcRect, &dstRect);
}

void RenderWindow::flip() {
    SDL_RenderPresent(renderer);
}