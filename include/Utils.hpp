#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Math.hpp"


struct EntityInfo {
    SDL_Texture *texture;
    int w, h;
};
