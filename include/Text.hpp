#pragma once

#include "Entity.hpp"


class Text : public Entity {
public:
    Text(Vector2f pos, EntityInfo entityInfo, float scaleFactor);
};