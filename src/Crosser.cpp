#include "Crosser.h"
#include "game.h"

Crosser::Crosser(Game* g, GameState* gs, PlayState* ps, std::istream& is)
    : SceneObject(g, gs, ps, is), ancho(0.0f) {

    velocidad = Vector2D<float>(0, 0);
}
Crosser::~Crosser() {}

void Crosser::update() {
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

