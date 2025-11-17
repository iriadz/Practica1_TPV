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
    // mover horizontalmente
    rect.x += velocidad.getX() * dt;

    // reaparecer si sale por un lado (ejemplo simple)
    // usamos ancho de ventana desde Game
   // int w = game->getWindowWidth();
    int w = game->WINDOW_WIDTH;
    if (velocidad.getX() > 0 && rect.x > w) {
        rect.x = -rect.w + fmodf(rect.x - w, ancho + rect.w);
    }
    else if (velocidad.getX() < 0 && rect.x + rect.w < 0) {
        rect.x = w + fmodf((rect.x + rect.w), ancho + rect.w);
    }
}
