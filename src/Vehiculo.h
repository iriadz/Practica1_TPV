#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"

class Game;
class Vehiculo
{
public:
	Vehiculo(Game* j, Texture* t, Point2D p, Point2D v);

	//Constructora por lectura de archivo
	Vehiculo(Game* j, std::istream& in);

	void render()const;
	void update();
	//detectar colisiones(bool checkCollision(const SDL_FRect&)).
	Collision checkCollision(const SDL_FRect& ref);

private:
	Game* juego;
	Texture* textura;
	Point2D posicion;
	Point2D velocidad;
	
};