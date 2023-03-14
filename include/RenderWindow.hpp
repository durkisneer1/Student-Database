#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

class RenderWindow {
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    void cleanUp();
    void cls();
    void draw(Entity& entity);
    void flip();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};