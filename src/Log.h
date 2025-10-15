#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Game;

class Log
{
public:
	Log(Game* j, Texture* t, Point2D p, Vector2D<float> v) : juego(j), textura(t), posicion(p), velocidad(v) {};

	void render()const
	{
		SDL_FRect tronco = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() }; // AJUSTAR
		textura->render(tronco);
	}
	void update()
	{
		//Suamas velocidad si quieres q avance
		posicion = posicion + Point2D(velocidad.getX(), velocidad.getY());

		//Recalcular posicion si llegan al limite
		if (posicion.getX() <= -150) posicion = posicion + Point2D(748, 0);
		if (posicion.getX() >= 750) posicion = posicion - Point2D(748, 0);
	}
	//detectar colisiones(bool checkCollision(const SDL_FRect&)).
	bool checkCollision(const SDL_FRect& ref)
	{
		SDL_FRect log = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		//return ;
		if (SDL_HasRectIntersectionFloat(&ref, &log)) return true;
		else return false; 
	}

private:
	Game* juego;
	Texture* textura;
	Point2D posicion;
	Vector2D<float> velocidad;
};

