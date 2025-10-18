#include "Wasp.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"

void Wasp::render() {
    SDL_FRect avispa = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->render(avispa);
}

void Wasp::update() {


    //1. Bajar contador vida
    //2. MOver aleatorialiemte dentro de la pantalla
    //posicion = posicion + direccion * 32;

   
}



bool Wasp::isAlive() const{
    return vida < CADUCIDAD ;
}

//detectar colisiones(bool checkCollision(const SDL_FRect&)).
bool Wasp::checkCollision(const SDL_FRect& ref)
{
    SDL_FRect avispa = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    return SDL_HasRectIntersectionFloat(&ref, &avispa);
}
