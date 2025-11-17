#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SceneObject.h"

class Wasp: public SceneObject
{
public:
    Wasp(Game* g, int v);
    virtual ~Wasp() = default;
    //void render();
    bool isAlive() const;
    void update(float dt);
   /* Collision checkCollision(const SDL_FRect&);*/
private:
    int tiempoVidaMax;
};
