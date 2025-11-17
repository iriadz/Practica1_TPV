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
    posicion = posicion + Point2D(velocidad.getX()/20, velocidad.getY()/20);

    //Recalcular posicion si llegan al limite
//	if (posicion.getX() <= -150) posicion = posicion + Point2D(600, 0);
    if (posicion.getX() >= 750) posicion = posicion - Point2D(game->WINDOW_WIDTH * 2, 0);
}
