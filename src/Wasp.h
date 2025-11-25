#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SceneObject.h"

class Wasp: public SceneObject
{
public:
    Wasp(Game* g, int max, int cr, Point2D pos);
    virtual ~Wasp() = default;
    //void render();
    bool isDead() const;
    void update(float dt);
    void setAnchor(It it);
   /* Collision checkCollision(const SDL_FRect&);*/
private:
    int tiempoVidaMax;
    int tiempoCreacion;
    It it;
};
