#include "Turtles.h"

#include "Collision.h"

Turtles::Turtles(Game* j, Texture* t, Point2D p, Vector2D<int> v) : juego(j), textura(t), posicion(p), velocidad(v) {};
Turtles::Turtles(Game* j, std::istream& in) : juego(j) {
	int x, y, tipo; float vel;

	in >> x >> y >> vel >> tipo;

	posicion = Point2D((int)x, (int)y);
	velocidad = Vector2D<int>(vel / 20, 0.0f);
	textura = juego->getTexture(juego->TURTLE);

	estado = 0;
	tiempoEstado = SDL_GetTicks();
}
void Turtles::update()
{
	posicion = posicion + Point2D(velocidad.getX(), velocidad.getY());

	//Recalcular posicion si llegan al limite
//	if (posicion.getX() <= -150) posicion = posicion + Point2D(600, 0);
	if (posicion.getX() >= 750) posicion = posicion - Point2D(juego->WINDOW_WIDTH * 2, 0);

	if (SDL_GetTicks() >= tiempoEstado + 400)
	{
		if (estado != 6) estado++;
		else estado = 0; 
		tiempoEstado = SDL_GetTicks();
	}
}

void Turtles::render() const
{
	
	for (int i = 0; i < 5; i++)
	{
		SDL_FRect tronco = { posicion.getX() + (i * 31),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
		textura->renderFrame(tronco, 0, estado);
	}
}



Collision Turtles::checkCollision(const SDL_FRect& ref)
{
	Texture* tex = juego->getTexture(juego->LOG2);
	SDL_FRect log = { posicion.getX(),posicion.getY(), tex->getFrameWidth(), tex->getFrameHeight() };
	//return ;
	if (SDL_HasRectIntersectionFloat(&ref, &log) && estado != 5) {
		Collision col(PLATFORM, velocidad);
		return col;
	}

	return Collision(ENEMY, Vector2D<int>(0, 0));

}