#include "Wasp.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"

void Wasp::render() {
    SDL_FRect avispa = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->render(avispa);
}


bool Wasp::isAlive() const {
    return SDL_GetTicks() >= tiempoVidaMax;
}

//detectar colisiones(bool checkCollision(const SDL_FRect&)).
Collision Wasp::checkCollision(const SDL_FRect& ref)
{
	SDL_FRect wasp = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	//return ;
	if (SDL_HasRectIntersectionFloat(&ref, &wasp)) {
		Collision col(ENEMY, Vector2D<int>(0, 0));
		return col;
	}

	return Collision(NONE, Vector2D<int>(0, 0));
}
