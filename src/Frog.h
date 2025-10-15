#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Frog
{
public:
    Frog() { }
    Frog(Game* g, Texture* t) :
        juego(g),
        textura(t),
        vidas(3)
    { }

    void render();
    void update();
    void handleEvent(const SDL_Event&);
    SDL_FRect frogHitbox() const;

private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
    Point2D direccion;   // Dirección actual del movimiento
    int vidas;           // Vidas restantes
};
