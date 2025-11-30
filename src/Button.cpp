	#include "Button.h"

	Button::~Button() {

	}

	void Button::render() const {
		if (visible) {
			SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
			textura->render(r);
		}
	}

	void Button::swapVisbility() {
		visible = !visible;
	}