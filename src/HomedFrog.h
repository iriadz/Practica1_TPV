#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SceneObject.h"
class Game;

class HomedFrog : public SceneObject
{
public:
    /*HomedFrog(Game* g, Texture* t, Point2D p) :
        juego(g),
        textura(t),
        posicion(p),
        ocupado(false)
    { }*/
    //Constructora por lectura de archivo
    HomedFrog(Game* g);
    // Frog(Game* game, const SDL_FRect& rect, Texture* tex = nullptr);
    virtual ~HomedFrog() = default;

    virtual void update(float dt) override;
    virtual void render() const override;
    bool getOcupado() const;
    Point2D getPos() const;
    void onOcupar();
    void setPosition(Point2D pos);
  virtual Collision checkCollision(const SDL_FRect& other) const;


private:
    bool ocupado;        // si hay una rana
};