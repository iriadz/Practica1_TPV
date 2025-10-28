#include "HomedFrog.h"
#include "vector2D.h"

void HomedFrog::render() {
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

bool HomedFrog::checkCollision(const SDL_FRect& ref)
{
	SDL_FRect frog = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	//return ;
	return SDL_HasRectIntersectionFloat(&ref, &frog);

}