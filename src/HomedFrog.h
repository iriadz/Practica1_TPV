#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class HomedFrog
{
public:
    HomedFrog(Game* g, Texture* t, Point2D p) :
        juego(g),
        textura(t),
        posicion(p),
        ocupado(false)
    { }

    void render();
    bool getOcupado() const;
    Point2D getPos() const;
    void onOcupar();
    bool checkCollision(const SDL_FRect& ref);


private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
    bool ocupado;        // si hay una rana
};