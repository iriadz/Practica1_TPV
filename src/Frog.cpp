#include "Frog.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"
#include "Log.h"

Frog::Frog(Game* g, Texture* t, Point2D p) :
    juego(g),
    textura(t),
    posicion(p),
    vidas(3)
{
    sprite = 0;
    angle = 0; 
    lastPosition = posicion;
}


Frog::Frog(Game* g, std::istream& in) : juego(g) {
    int x, y;
     direccion = Point2D(0, 0);
    in >> x >> y;
    posicion = Point2D(x, y);
    textura = juego->getTexture(juego->FROG);
    vidas = 3;
    sprite = 0;
    angle = 0;
}
void Frog::render() {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->renderFrame(rana, 0, sprite, angle);
}

void Frog::update() {

    posicion = posicion + direccion * 32;

    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };


    // Cambiar posicion con los troncos
    if (juego->checkCollision(rana) == Collision::Type::NONE)
    {
        // BORDES
        if (posicion.getX() < 0) posicion = Point2D(0, posicion.getY()); //izq
        if (posicion.getX() > 420) posicion = Point2D(420, posicion.getY()); //der
        if (posicion.getY() > 402) posicion =Point2D(posicion.getX(), 402); //der

        if (posicion.getY() < juego->RIVER_LOW) loseLife();
    }
    if (juego->checkCollision(rana) == Collision::Type::PLATFORM) posicion = posicion + Vector2D<int>(2, 0);
    if (juego->checkCollision(rana) == Collision::Type::ENEMY) {
        loseLife();
    }
       Point2D p(0, 0);
       direccion = p;

   /* if (lastPosition.getX() != posicion.getX() && lastPosition.getY() != posicion.getY()) {
        lastPosition = posicion;
    }*/
}

void Frog::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_UP: {
            direccion = { 0, -1 };
            sprite = 1;
            angle = 0; 
            //posicion = posicion + Vector2D<int>(0, -10);
        } break;
        case SDLK_DOWN: {
            direccion = { 0, 1 }; 
            sprite = 1;
            angle = 180;
            //posicion = posicion + Vector2D<int>(0, 32);
        } break;
        case SDLK_LEFT: {
           direccion = { -1, 0 };
            sprite = 1;
            angle = -90;
            //posicion = posicion + Vector2D<int>(-32, 0);
        } break;
        case SDLK_RIGHT: {
            direccion = { 1, 0 };
            sprite = 1;
            angle = 90;
            //posicion = posicion + Vector2D<int>(32, 0);
            break;
        }
        }
    }
    else sprite = 0;
}

void Frog::loseLife() {
    vidas--;
    Point2D p(205, 402);
    //Point2D p(0, 0);
    posicion = p;
}

int Frog::getLifes() const {
    return vidas;
}

float Frog::getPosition() const {
    return posicion.getY();
}
SDL_FRect Frog::frogHitbox() const {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth() / 2, textura->getFrameHeight() };
    return rana;
}