#include "Frog.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"

Frog::Frog(Game* g, Texture* t, Point2D p) :
    juego(g),
    textura(t),
    posicion(p),
    vidas(3)
{
    jump = false;
    lastPosition = posicion;
}


Frog::Frog(Game* g, std::istream& in, Texture* t) : juego(g), textura(t) {
    int x, y;
    // direccion = Point2D(0, 0);
    in >> x >> y;
    posicion = Point2D(x, y);
    vidas = 3;
    lastPosition = posicion;
    jump = false;
}
void Frog::render() {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->renderFrame(rana, 0, 1);
}

void Frog::update() {

    posicion = posicion + direccion * 32;

     // Cambiar posicion con los troncos
    if (posicion.getY() <= juego->RIVER_LOW && posicion.getY() >= juego->RIVER_HIGH) posicion = posicion + Vector2D<int>(-6, 0);

    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    if (juego->checkCollision(rana) == Collision::Type::PLATFORM || juego->checkCollision(rana) == Collision::Type::ENEMY) {
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
            jump = true;
            //posicion = posicion + Vector2D<int>(0, -10);
        } break;
        case SDLK_DOWN: {
            direccion = { 0, 1 }; 
            jump = true;
            //posicion = posicion + Vector2D<int>(0, 32);
        } break;
        case SDLK_LEFT: {
           direccion = { -1, 0 };
            jump = true;
            //posicion = posicion + Vector2D<int>(-32, 0);
        } break;
        case SDLK_RIGHT: {
            direccion = { 1, 0 };
            jump = true;
            //posicion = posicion + Vector2D<int>(32, 0);
            break;
        }
        }
    }
    else jump = false;
}

void Frog::loseLife() {
    vidas--;
    Point2D p(juego->WINDOW_WIDTH / 2 - 16, juego->WINDOW_HEIGHT - 32);
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