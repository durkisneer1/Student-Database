#pragma once

#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <json.hpp>

#include "Math.hpp"
#define WIN_WIDTH 880.0f
#define WIN_HEIGHT 640.0f


struct EntityInfo {
    SDL_Texture *texture;
    int w, h;
    std::string text;
};

enum States {
    MENU,
    LOGIN,
    SIGNUP,
};
