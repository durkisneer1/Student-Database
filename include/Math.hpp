#pragma once

#include <iostream>
#include <cmath>


struct Vector2f {
    Vector2f()
    : x(0.0f), y(0.0f)
    {}

    Vector2f(float x, float y)
    : x(x), y(y)
    {}

    float waveVertical(float amplitude, float theta) {
        return amplitude * sinf(theta) + y;
    }

    float x, y;
};
