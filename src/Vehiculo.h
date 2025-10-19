#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Game;

class Vehiculo
{
public:
	Vehiculo(Game* j, Texture* t, Point2D p, Vector2D<float> v) : juego(j), textura(t), posicion(p), velocidad(v) {};

	//Constructora por lectura de archivo
	Vehiculo(Game* j, std::istream& in) : juego(j) {
		float x, y;
		int vel, tipo;
		in >> x >> y >> vel >> tipo;
		posicion = { x, y };
		velocidad = { static_cast<float>(vel), 0.0f };

		switch (tipo) {
		case 1: textura = juego->getTexture(Game::CAR1); break;
		case 2: textura = juego->getTexture(Game::CAR2); break;
		case 3: textura = juego->getTexture(Game::CAR3); break;
		case 4: textura = juego->getTexture(Game::CAR4); break;
		default: textura = juego->getTexture(Game::CAR1); break;
		}
	}

	void render()const
	{
		SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() }; // AJUSTAR
		textura->render(coche);
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
		SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		return SDL_HasRectIntersectionFloat(&ref, &coche);
	}

private:
	Game* juego;
	Texture* textura;
	Point2D posicion;
	Vector2D<float> velocidad;
};

