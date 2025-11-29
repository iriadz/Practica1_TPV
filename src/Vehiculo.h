#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
#include "Crosser.h"

class Game;
class Vehiculo : public Crosser
{
public:
	//Vehiculo(Game* j, Texture* t, Point2D p, Point2D v);
	using Crosser::Crosser;
	virtual ~Vehiculo() = default;
	//Constructora por lectura de archivo
	Vehiculo(Game* j, GameState* gs, PlayState* ps, std::istream& in);


};

