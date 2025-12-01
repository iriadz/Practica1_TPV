#include "Frog.h"
#include "Vector2D.h"
#include "game.h"
#include "Collision.h"
#include "Log.h"
#include "SceneObject.h"
#include "PlayState.h"
#include <iostream>





Frog::Frog(Game* g, GameState* gs, PlayState* ps, std::istream& is) : SceneObject(g, gs, ps, is), sprite(0), angle(0)
{
    int v;
    is >> v;
    textura = g->getTexture(g->FROG);
    vidas = v;
}

Frog::~Frog() {}

void Frog::render() const {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->renderFrame(rana, 0, sprite, angle);
}

void Frog::update() {
    posicion = posicion + direccion * 32;

    SDL_FRect rana = frogHitbox();
    Collision col = playState->checkCollision(rana);
    

    // Reinicia la direccion a 0
    direccion = Point2D(0, 0); 
    
    // Mata a la rana si se sale de los bordes
    if (posicion.getX() < 0 || posicion.getX() > game->WINDOW_WIDTH || posicion.getY() < 0 || posicion.getY() > game->WINDOW_HEIGHT) loseLife();

    // Update dependiendo del tipo de colision
    if (col.tipo == HOME) {
        resetPosition();
    }
    else if (col.tipo == PLATFORM) { 
        float p = col.velocidad.getX() * Game::DT;
        posicion = posicion +  Point2D(p, 0); 
    }
    else if (col.tipo == ENEMY) {
        loseLife();
    }
    else if (col.tipo == NONE && posicion.getY() < game->RIVER_LOW) {
        loseLife();
    }
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

void Frog::resetPosition() {
    Point2D p(205, 402);
    //Point2D p(0, 0);
    posicion = p;
}

int Frog::getLifes() const {
    return vidas;
}

int Frog::getHomesReached() {
    int homes = 0;
    /*game->homeReached(posicion);
    if ()*/
    return homes;
}


Point2D Frog::getPosition() const {
    return posicion;
}

SDL_FRect Frog::frogHitbox() const {
    SDL_FRect rana = { posicion.getX(), posicion.getY(), textura->getFrameWidth() / 2, textura->getFrameHeight()};
    return rana;
}

Collision
Frog::checkCollision(const SDL_FRect& other) const {
    return Collision(NONE, Vector2D<float>(0, 0));
}

