#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Game;

class Vehiculo
{
	//Contiene un puntero al juego, a su textura, una posición (tipo Point2D) y una velocidad (tipo Vector2D).
	//Implementa un constructor y métodos para dibujarse (void render() const), actualizarse (void update()) 
	// y detectar colisiones (bool checkCollision(const SDL_FRect&)).
public:
	Vehiculo(Game* j, Texture* t, Point2D p, Vector2D<float> v) : juego(j), textura(t), posicion(p), velocidad(v) {};

	void render()const
	{
		SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() }; // AJUSTAR
		textura->render(coche);
	}
	void update()
	{
		//Suamas velocidad si quieres q avance
		posicion = posicion + Point2D(velocidad.getX(), velocidad.getY());

		if (posicion.getX() <= -150) posicion = posicion + Point2D(748, 0);
	}
	bool checkCollision(const SDL_FRect& ref)
	{
	
	}

private:
	Game* juego;
	Texture* textura;
	Point2D posicion;
	Vector2D<float> velocidad;
};

