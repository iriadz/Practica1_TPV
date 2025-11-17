#include "Log.h"
#include "Collision.h"

//Log::Log(Game* j, Texture* t, Point2D p, Vector2D<int> v) : juego(j), textura(t), posicion(p), velocidad(v) {};
Log::Log(Game* j, std::istream& in) : Platform(j){
	int x, y, tipo; float vel;
	in >> x >> y >> vel >> tipo;
	posicion = Point2D((int)x, (int)y);
	//velocidad = Vector2D<float>(vel, 0);ç
	velocidad = Vector2D<float>(vel, 0);

	switch (tipo) {
	case 1: textura = j->getTexture(j->LOG1); break;
	case 2: textura = j->getTexture(j->LOG2); break;
	default: textura = j->getTexture(j->LOG1); break;
	}
}
