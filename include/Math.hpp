#pragma once

struct Vector2f
{
    Vector2f()
        : x(0.0f), y(0.0f) {}

    Vector2f(float x, float y)
        : x(x), y(y) {}

    float x, y;
};
