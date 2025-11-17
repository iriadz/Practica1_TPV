#include "HomedFrog.h"
#include "vector2D.h"


void HomedFrog::render() const {
	SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(rana, 0, 0);
}

bool HomedFrog::getOcupado() const {
	return ocupado;
}

Point2D HomedFrog::getPos() const {
	return posicion;
}

void HomedFrog::onOcupar() {
	ocupado = true;
}

 Collision HomedFrog::checkCollision(const SDL_FRect& ref) const
{
	SDL_FRect home = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	//return ;
	if (SDL_HasRectIntersectionFloat(&ref, &home)) {
		Collision col(HOME, Vector2D<float>(0, 0));
		return col;
	}

	return Collision(NONE, Vector2D<float>(0, 0));

}