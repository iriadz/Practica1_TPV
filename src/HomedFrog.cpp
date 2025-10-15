#include "HomedFrog.h"

void Frog::render() {
	SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(rana, 0, 1);
}