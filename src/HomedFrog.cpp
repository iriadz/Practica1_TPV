#include "HomedFrog.h"
#include "Vector2D.h"
#include "SceneObject.h"

HomedFrog::HomedFrog(Game* g, GameState* gs, PlayState* ps, std::istream& is,  Point2D pos) :
	SceneObject(g, gs, ps, is),
	ocupado(false)
{
	textura = g->getTexture(g->FROG);
	posicion = pos;
}
void HomedFrog::render() const {
	if (ocupado) 
	{
		SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		textura->renderFrame(rana, 0, 0);
	}
}

void HomedFrog::update() {

}

bool HomedFrog::getOcupado() const {
	return ocupado;
}
void HomedFrog::setPosition(Point2D newPos) {
	posicion = newPos;
}

Point2D HomedFrog::getPos() const {
	return posicion;
}

void HomedFrog::onOcupar() {
	ocupado = true;
}


Collision HomedFrog::checkCollision(const SDL_FRect& ref) const
{
	/*SDL_FRect home = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };*/
	SDL_FRect home = getBoundingBox();;
	if (SDL_HasRectIntersectionFloat(&ref, &home)) {
		return Collision (HOME, Vector2D<float>(0, 0));
	}

	return Collision(NONE, Vector2D<float>(0, 0));
}