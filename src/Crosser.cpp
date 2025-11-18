#include "Crosser.h"
#include "Crosser.h"
#include "Game.h"

Crosser::Crosser(Game* g)
    : SceneObject(g), ancho(0.0f) {

    velocidad = Vector2D<float>(0, 0);
}
Crosser::~Crosser() {}

void Crosser::update(float dt) {
	posicion = posicion + Point2D(velocidad.getX() * Game::DT, velocidad.getY());
    
	//Recalcular posicion si llegan al limite
	if (posicion.getX() >= 750) posicion = posicion - Point2D(game->WINDOW_WIDTH * 2, 0);
	if (posicion.getX() <= -150) posicion = posicion + Point2D(game->WINDOW_WIDTH * 2, 0);
}
Collision
Crosser::checkCollision(const SDL_FRect& other) const {
 
  //  SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    SDL_FRect r = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&other, &r)) {
        Collision col(ENEMY, Vector2D<float>(0, 0));
        return col;
    }

    return Collision(NONE, Vector2D<float>(0, 0));
}

