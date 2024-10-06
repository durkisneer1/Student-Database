#pragma once

#include <SDL.h>
#include <string>

#define WIN_WIDTH 880.0f
#define WIN_HEIGHT 640.0f

struct EntityInfo
{
    SDL_Texture *texture;
    int w, h;
    std::string text;
};

enum States
{
    MENU,
    LOGIN,
    SIGNUP,
};
