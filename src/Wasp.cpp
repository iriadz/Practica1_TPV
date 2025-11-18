#include "Wasp.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"


Wasp::Wasp(Game* g, float v, Point2D pos) : SceneObject(g), tiempoVidaMax(SDL_GetTicks() + v)
{
    posicion = pos;
    textura = g->getTexture(g->WASP);
}

bool Wasp::isAlive() const {
    return SDL_GetTicks() >= tiempoVidaMax;
}

void Wasp::update(float dt) {

}

////detectar colisiones(bool checkCollision(const SDL_FRect&)).
//Collision Wasp::checkCollision(const SDL_FRect& ref)
//{
//	SDL_FRect wasp = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
//	//return ;
//	if (SDL_HasRectIntersectionFloat(&ref, &wasp)) {
//		Collision col(ENEMY, Vector2D<float>(0, 0));
//		return col;
//	}
//
//	return Collision(NONE, Vector2D<float>(0, 0));
//}
