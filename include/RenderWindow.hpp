#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>

#include "Entity.hpp"


class RenderWindow {
public:
    RenderWindow(const char *title, int width, int height);
    EntityInfo loadEntityInfo(const char *filePath);

    void cleanUp();
    SDL_Point getMousePos();
    void cls();
    void draw(Entity& entity);
    void flip();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};