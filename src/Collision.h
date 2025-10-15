#pragma once
#include <SDL3_image/SDL_image.h>
#include "vector2D.h"
struct Collision
{
public:
	enum Type{NONE, ENEMY, PLATFORM, HOME};
	Vector2D<int> velocidad;
};

