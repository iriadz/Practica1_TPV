#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
class Game;
class Frog
{
public:
    Frog() { }
    Frog(Game* g, Texture* t, Point2D p);

    //Constructora por lectura de archivo
    Frog(Game* g, std::istream& in);

    void render();
    void update();
    void handleEvent(const SDL_Event&);
    void loseLife();
    int getLifes() const;
    float getPosition() const;
    SDL_FRect frogHitbox() const;

private:
    Game* juego = nullptr;         // Referencia al juego principal
    Texture* textura = nullptr;    // Textura de la rana
    Point2D posicion;    // Posición actual (en píxeles)
    Point2D direccion;   // Dirección actual del movimiento
    int vidas;           // Vidas restantes
    Point2D lastPosition;
    int sprite;
    int angle; 
};