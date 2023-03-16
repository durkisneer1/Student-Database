#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"


class RenderWindow {
public:
    RenderWindow(const char *title, int width, int height);
    EntityInfo loadEntityInfo(const char *filePath);

    void cleanUp();
    static SDL_FPoint getMousePos();
    void cls() { SDL_RenderClear(renderer); };
    void draw(Entity& entity);
    void flip() { SDL_RenderPresent(renderer); };
    void scroll(Entity& entity);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};