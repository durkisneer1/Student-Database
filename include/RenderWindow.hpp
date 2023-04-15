#pragma once

#include "Utils.hpp"
#include "Wallpaper.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "MajorSelect.hpp"


class RenderWindow {
public:
    RenderWindow(const std::string &title, int width, int height);
    EntityInfo loadImageInfo(const std::string &filePath);
    EntityInfo loadTextInfo(const std::string &text, TTF_Font *font, SDL_Color color);

    void cleanUp();
    void cls() { SDL_RenderClear(renderer); };
    void flip() { SDL_RenderPresent(renderer); };

    SDL_Renderer *getRenderer() { return renderer; };
    static SDL_FPoint getMousePos();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};