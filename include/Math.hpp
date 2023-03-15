#pragma once

#include <iostream>


struct Vector2f {
    Vector2f()
    : x(0.0f), y(0.0f)
    {}

    Vector2f(float x, float y)
    : x(x), y(y)
    {}

    float x, y;
};


struct Vector2i {
    Vector2i()
    : x(0), y(0)
    {}

    Vector2i(int x, int y)
    : x(x), y(y)
    {}

    int x, y;
};