#include "Frog.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"

void Frog::render() {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->renderFrame(rana, 0, 1);
}

void Frog::update() {
    posicion = posicion + direccion * 32;
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    if (juego->checkCollision(rana) == Collision::Type::ENEMY) {
        loseLife();
    }
    Point2D p(0, 0);
    direccion = p;
}

void Frog::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_UP:    direccion = { 0, -1 }; break;
        case SDLK_DOWN:  direccion = { 0, 1 };  break;
        case SDLK_LEFT:  direccion = { -1, 0 }; break;
        case SDLK_RIGHT: direccion = { 1, 0 };  break;
        }
    }
}

void Frog::loseLife() {
    vidas--;
    //Point2D p(juego->WINDOW_HEIGHT, juego->WINDOW_WIDTH / 2);
    Point2D p(0, 0);
    posicion = p;
}

SDL_FRect Frog::frogHitbox() const {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth() / 2, textura->getFrameHeight() };
    return rana;
}