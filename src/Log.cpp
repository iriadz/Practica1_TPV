#include "Log.h"
#include "Collision.h"

Log::Log(Game* j, Texture* t, Point2D p, Vector2D<int> v) : juego(j), textura(t), posicion(p), velocidad(v) {};
Log::Log(Game* j, std::istream& in) : juego(j) {
	int x, y, tipo;
	float vel;
	in >> x >> y >> vel >> tipo;
	posicion = Point2D((int)x, (int)y);
	//velocidad = { static_cast<float>(vel), 0.0f };
	velocidad = Vector2D<int>(vel/20, 0.0f);
	switch (tipo) {
	case 1: textura = j->getTexture(juego->LOG1); break;
	case 2: textura = juego->getTexture(juego->LOG2); break;
	default: textura = juego->getTexture(juego->LOG1); break;
	}
}
void Log::update()
{
	//Suamas velocidad si quieres q avance
	posicion = posicion + Point2D(velocidad.getX(), velocidad.getY());

	//Recalcular posicion si llegan al limite
//	if (posicion.getX() <= -150) posicion = posicion + Point2D(600, 0);
	if (posicion.getX() >= 750) posicion = posicion - Point2D(juego -> WINDOW_WIDTH * 2, 0);
}

void Log::render() const
{
	SDL_FRect tronco = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(tronco);
}

Collision Log::checkCollision(const SDL_FRect& ref)
{
	SDL_FRect log = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	//return ;
	if (SDL_HasRectIntersectionFloat(&ref, &log)) {
		Collision col(PLATFORM, velocidad);
		return col;
	}

	return Collision(ENEMY, Vector2D<int>(0,0));

}