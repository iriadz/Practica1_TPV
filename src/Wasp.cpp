#include "Wasp.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"

void Wasp::render() {
    SDL_FRect avispa = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->render(avispa);
}


bool Wasp::isAlive() const {
    return SDL_GetTicks() >= tiempoVidaMax;
}

//detectar colisiones(bool checkCollision(const SDL_FRect&)).
bool Wasp::checkCollision(const SDL_FRect& ref)
{
    SDL_FRect avispa = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    return SDL_HasRectIntersectionFloat(&ref, &avispa);
}
