#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class HomedFrog
{
public:
    HomedFrog() {}
    HomedFrog(Game* g, Texture* t, Point2D p) :
        juego(g),
        textura(t),
        posicion(p)
    { }

    void render();

private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
};