#include "Label.h"


void Label::render() const {
	SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(r);
}