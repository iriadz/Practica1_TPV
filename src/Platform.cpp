#include "Platform.h"
//reescribir colisiones de las plataformas
Collision
Platform::checkCollision(const SDL_FRect& other) const {
	SDL_FRect log = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&other, &log)) {
			return Collision(PLATFORM, Vector2D<float>(velocidad.getX(), 0));
	}
	return Collision(NONE, Vector2D<float>(0, 0));
}