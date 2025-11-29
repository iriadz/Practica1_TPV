#include "Wasp.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"


Wasp::Wasp(Game* g, GameState* gs, PlayState* ps, std::istream& is, int max, int cr, Point2D pos) : SceneObject(g, gs, ps, is)
{
    posicion = pos;
    textura = g->getTexture(g->WASP);
    tiempoCreacion = cr;
    tiempoVidaMax = max;
}

bool Wasp::isDead() const {
    return SDL_GetTicks() >= tiempoVidaMax + tiempoCreacion;
}

void Wasp::update() {
    if (isDead) {
        game->deleteAfter(it);
    }
}

void Wasp::setAnchor(It i) {
    it = i;
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
