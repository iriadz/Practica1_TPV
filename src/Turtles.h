#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"

class Game;

class Turtles
{
public:
	Turtles(Game* j, Texture* t, Point2D p, Vector2D<int> v);

	//Constructora por lectura de archivo
	Turtles(Game* j, std::istream& in);
	void render()const;
	void update();
	Collision checkCollision(const SDL_FRect& ref);

private:
	Game* juego;
	Texture* textura;
	Point2D posicion;
	Vector2D<int> velocidad;
};
