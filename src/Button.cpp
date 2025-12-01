#include "Button.h"
#include <SDL3/SDL.h>

	Button::~Button() {
		m_callbacks.clear();
	}

	void Button::update() {
		float mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_FRect mouseRect{ static_cast<float>(mouseX), static_cast<float>(mouseY), 1.0f, 1.0f};
		SDL_FRect button{ posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		if (SDL_HasRectIntersectionFloat(&mouseRect, &button)) {
			m_hover = true;
		}
		else m_hover = false;
	}

	void Button::render() const {
		SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		textura->render(r);
	}