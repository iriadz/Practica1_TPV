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
		if (m_hover) {
			SDL_SetTextureColorMod(textura->getTexture(), 255, 255, 0); // Color amarillo
		}
		else {
			SDL_SetTextureColorMod(textura->getTexture(), 255, 255, 255); // Color normal
		}
		SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		textura->render(r);
	}

	void Button::handleEvent(const SDL_Event &event) {
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && m_hover) {

		}
	}