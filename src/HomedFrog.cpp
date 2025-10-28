#include "HomedFrog.h"

void HomedFrog::render() {
	SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(rana, 0, 0);
}

bool HomedFrog::getOcupado() const {
	return ocupado;
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