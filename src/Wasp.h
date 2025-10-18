#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Wasp
{
public:
    static constexpr float CADUCIDAD = 30;
    Wasp() {}
    Wasp(Game* g, Texture* t, Point2D p, float v) :
        juego(g),
        textura(t),
        posicion(p),
        vida(v)
    {
    }

    void render();
    void update();
    bool isAlive();
    

private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
    Point2D direccion;   // Dirección actual del movimiento
    float vida; // Vidas restantes
};
