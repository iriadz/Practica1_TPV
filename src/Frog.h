#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
class Game;
class Frog
{
public:
    Frog() { }
    Frog(Game* g, Texture* t, Point2D p) :
        juego(g),
        textura(t),
        posicion(p),
        vidas(3)
    { }

    //Constructora por lectura de archivo
    Frog(Game* g, std::istream& in, Texture* t) : juego(g), textura(t) {
        int x, y;
        in >> x >> y >> vidas;
        posicion = { (int)x,(int) y };
    }
    void render();
    void update();
    void handleEvent(const SDL_Event&);
    void loseLife();
    int getLifes() const;
    float getPosition() const;
    SDL_FRect frogHitbox() const;

private:
    Game* juego;         // Referencia al juego principal
    Texture* textura;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
    Point2D direccion;   // Dirección actual del movimiento
    int vidas;           // Vidas restantes
};
