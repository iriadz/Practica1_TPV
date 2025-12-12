#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
#include "SceneObject.h"

class Wasp: public SceneObject
{
public:
   
    Wasp(Game* g, GameState* gs, PlayState* ps, std::istream& is);
    virtual ~Wasp() = default;
    //void render();
    bool isDead() const;
    void update() override;
    void render()const override;
    void setAnchor(It it);
   /* Collision checkCollision(const SDL_FRect&);*/
private:
    Vector2D<float>velocidad;
    bool isdead;
    It it;
};
