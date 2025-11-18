#include "Crosser.h"
#include "Crosser.h"
#include "Game.h"

//Crosser::Crosser(Game* game, const SDL_FRect& rect, float vx, Texture* tex)
//    : SceneObject(game, rect, tex), ancho(0.0f) {
//
//    velocidad = Vector2D<float>(vx, 0);
//}
Crosser::Crosser(Game* g)
    : SceneObject(g), ancho(0.0f) {

    velocidad = Vector2D<float>(0, 0);
}
Crosser::~Crosser() {}

void Crosser::update(float dt) {

	posicion = posicion + Point2D(velocidad.getX() / 20, velocidad.getY() / 20);

	//Recalcular posicion si llegan al limite
	if (posicion.getX() >= 750) posicion = posicion - Point2D(game->WINDOW_WIDTH * 2, 0);
	if (posicion.getX() <= -150) posicion = posicion + Point2D(game->WINDOW_WIDTH * 2, 0);
}
Collision
Crosser::checkCollision(const SDL_FRect& other) const {
    ///* SDL_FRect a = getBoundingBox();
    // SDL_FRect b = other;
    // bool ch = !(a.x + a.w <= b.x || b.x + b.w <= a.x || a.y + a.h <= b.y || b.y + b.h <= a.y);*/

   // SDL_FRect _rect = getBoundingBox();
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    if (SDL_HasRectIntersectionFloat(&other, &r)) {
        Collision col(NONE, Vector2D<float>(0, 0));
        return col;
    }

    return Collision(NONE, Vector2D<float>(0, 0));
}

