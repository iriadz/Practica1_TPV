#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"
class Game;
class Frog : public SceneObject
{
public:
  /*  Frog(Game* g, Texture* t, Point2D p);*/

    //Constructora por lectura de archivo
    Frog(Game* g, std::istream& in);
   // Frog(Game* game, const SDL_FRect& rect, Texture* tex = nullptr);
    virtual ~Frog();

    virtual void update(float dt) override;
    virtual void render() const override;
    void handleEvent(const SDL_Event&);
    void loseLife();
    void resetPosition();
    int getLifes() const;
    Point2D getPosition() const;
    SDL_FRect frogHitbox() const;
private:
    Point2D direccion;   // Dirección actual del movimiento
    int vidas;           // Vidas restantes
    int sprite;
    int angle; 
};