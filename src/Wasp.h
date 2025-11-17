#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"

class Wasp: public SceneObject
{
public:
    Wasp(Game* g, int v);
    virtual ~Wasp() = default;
    //void render();
    bool isAlive() const;
   /* Collision checkCollision(const SDL_FRect&);*/
private:
    int tiempoVidaMax;
};
