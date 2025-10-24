#include "Log.h"

Log::Log(Game* j, Texture* t, Point2D p, Vector2D<float> v) : juego(j), textura(t), posicion(p), velocidad(v) {};
Log::Log(Game* j, std::istream& in) : juego(j) {
	int x, y, tipo;
	float vel;
	in >> x >> y >> vel >> tipo;
	posicion = Point2D((int)x, (int)y);
	//velocidad = { static_cast<float>(vel), 0.0f };
	velocidad = Vector2D<float>(vel, 0.0f);
	switch (tipo) {
	case 1: textura = j->getTexture(juego->LOG1); break;
	case 2: textura = juego->getTexture(juego->LOG2); break;
	default: textura = juego->getTexture(juego->LOG1); break;
	}
}
void Log::update()
{
	//Suamas velocidad si quieres q avance
	posicion = posicion + Point2D(velocidad.getX()/20, velocidad.getY()/20);

	//Recalcular posicion si llegan al limite
//	if (posicion.getX() <= -150) posicion = posicion + Point2D(600, 0);
	if (posicion.getX() >= 750) posicion = posicion - Point2D(juego -> WINDOW_WIDTH * 2, 0);
}

void Log::render() const
{
	SDL_FRect tronco = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(tronco);
}

bool Log::checkCollision(const SDL_FRect& ref)
{
	SDL_FRect log = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	//return ;
	return SDL_HasRectIntersectionFloat(&ref, &log);

}