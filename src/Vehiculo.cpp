#include "Vehiculo.h"

Vehiculo::Vehiculo(Game* j, Texture* t, Point2D p, Point2D v) : juego(j), textura(t), posicion(p), velocidad(v) {};

Vehiculo::Vehiculo(Game* j, std::istream& in) : juego(j) {
	int x, y, tipo, vel;
	in >> x >> y >> vel >> tipo;
	posicion = Point2D((int)x, (int)y);
	//velocidad = Vector2D<float>(vel, 0);ç
	velocidad = Point2D((int)vel, 0);

	switch (tipo) {
	case 1: textura = j->getTexture(juego->CAR1); break;
	case 2: textura = juego->getTexture(juego->CAR2); break;
	case 3: textura = juego->getTexture(juego->CAR3); break;
	case 4: textura = juego->getTexture(juego->CAR4); break;
	default: textura = juego->getTexture(juego->CAR1); break;
	}
}

void Vehiculo::render()const
{
	SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(coche);
}

void Vehiculo::update()
{
	posicion = posicion + Point2D(velocidad.getX() /15, velocidad.getY() /15);

	//Recalcular posicion si llegan al limite
	if (posicion.getX() <= -150) posicion = posicion + Point2D(748, 0);
	if (posicion.getX() >= 750) posicion = posicion - Point2D(748, 0);
}

bool Vehiculo::checkCollision(const SDL_FRect& ref)
{
	SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	return SDL_HasRectIntersectionFloat(&ref, &coche);
}