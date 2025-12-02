#include "Wasp.h"
#include "vector2D.h"
#include "game.h"
#include "Collision.h"
#include "PlayState.h"
#include "GameState.h"

Wasp::Wasp(Game* g, GameState* gs, PlayState* ps, std::istream& is) : SceneObject(g, gs, ps, is)
{
    float vx, vy; int vida;
    is >> vx >> vy >> vida;
    velocidad = Vector2D<float>(vx, vy);
    textura = game->getTexture(Game::WASP);
    isdead = false;
}


bool Wasp::isDead() const {
    return false;
}

void Wasp::update() {
    posicion = posicion + Point2D(velocidad.getX() , velocidad.getY() );

    //Recalcular posicion si llegan al limite
    if (posicion.getX() > Game::WINDOW_WIDTH) isdead = true;
    if (posicion.getX() < Game::WINDOW_WIDTH) isdead = true;
    if (posicion.getX() > Game::WINDOW_HEIGHT) isdead = true;

    if (isdead)
    {
        gameState->runLater([this]() {
            });
    }

}

void Wasp::render() const{
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
   
    textura->render(r);
}

void Wasp::setAnchor(It i) {
    it = i;
}
