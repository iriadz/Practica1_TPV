#include "Vehiculo.h"
#include "Collision.h"

//Vehiculo::Vehiculo(Game* j, Texture* t, Point2D p, Point2D v) : juego(j), textura(t), posicion(p), velocidad(v) {};

Vehiculo::Vehiculo(Game* j, GameState* gs, PlayState* ps, std::istream& in) : Crosser(j, gs, ps, in) {
	int tipo; float vel;
	in >> vel >> tipo;
	
	velocidad = Vector2D<float>(vel, 0);

	switch (tipo) {
		case 1: textura = j->getTexture(j->CAR1); break;
		case 2: textura = j->getTexture(j->CAR2); break;
		case 3: textura = j->getTexture(j->CAR3); break;
		case 4: textura = j->getTexture(j->CAR4); break;
		default: textura = j->getTexture(j->CAR1); break;
	}

	//lanzar excepcion
}

//void Vehiculo::render()const
//{
//	SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
//	textura->render(coche);
//}
//
//void Vehiculo::update()
//{
//	posicion = posicion + Point2D(velocidad.getX() /15, velocidad.getY() /15);
//
//	//Recalcular posicion si llegan al limite
//	if (posicion.getX() <= -150) posicion = posicion + Point2D(748, 0);
//	if (posicion.getX() >= 750) posicion = posicion - Point2D(748, 0);
//}
//
//Collision Vehiculo::checkCollision(const SDL_FRect& ref)
//{
//	SDL_FRect coche = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
//	//return ;
//	if (SDL_HasRectIntersectionFloat(&ref, &coche)) {
//		Collision col(ENEMY, Vector2D<int>(0, 0));
//		return col;
//	}
//
//	return Collision(NONE, Vector2D<int>(0, 0));
//}