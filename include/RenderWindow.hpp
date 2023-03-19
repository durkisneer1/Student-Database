#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"
#include "Text.hpp"
#include "Button.hpp"


class RenderWindow {
public:
    RenderWindow(const std::string &title, int width, int height);
    EntityInfo loadImageInfo(const std::string &filePath);
    EntityInfo loadTextInfo(const std::string &text, TTF_Font *font, SDL_Color color);
    static EntityInfo loadTextureInfo(SDL_Texture *srcTexture);

    void cleanUp();
    void cls() { SDL_RenderClear(renderer); };
    void flip() { SDL_RenderPresent(renderer); };
    SDL_Renderer *getRenderer() { return renderer; };
    static SDL_FPoint getMousePos();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};