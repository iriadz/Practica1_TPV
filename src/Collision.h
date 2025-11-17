#pragma once
#include <SDL3_image/SDL_image.h>
#include "vector2D.h"
enum Type { NONE, ENEMY, PLATFORM, HOME };

struct Collision
{
public:
	Type tipo;
	Vector2D<float> velocidad;
	Collision(Type t, Vector2D<float> v): tipo(t), velocidad(v) { }
	Collision(): tipo(ENEMY), velocidad(Vector2D<float>(0,0)) { }
};

