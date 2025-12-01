#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "game.h"
class Frog : public SceneObject, public EventHandler
{
public:
  /*  Frog(Game* g, Texture* t, Point2D p);*/

    //Constructora por lectura de archivo
    Frog(Game* g, GameState* gs, PlayState* ps, std::istream& in);
   // Frog(Game* game, const SDL_FRect& rect, Texture* tex = nullptr);
    virtual ~Frog();

    virtual void update() override;
    virtual void render() const override;
    void handleEvent(const SDL_Event&) override;
    void loseLife();
    void resetPosition();
    int getLifes() const;
    int getHomesReached();
    Point2D getPosition() const;
    SDL_FRect frogHitbox() const;
    Collision checkCollision(const SDL_FRect& other) const override;
private:
    Point2D direccion;   // Dirección actual del movimiento
    int vidas;           // Vidas restantes
    int sprite;
    int angle; 
};