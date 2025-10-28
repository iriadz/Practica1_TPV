#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Wasp
{
public:
    Wasp() {}
    Wasp(Game* g, Texture* t, Point2D p, int v) :
        juego(g),
        textura(t),
        posicion(p),
        tiempoVidaMax(SDL_GetTicks() + v)
    { }
    void render();
    bool isAlive() const;
    bool checkCollision(const SDL_FRect&);
    

private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
   
    int tiempoVidaMax;
};
