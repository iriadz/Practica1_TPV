#pragma once
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
#include "SceneObject.h"

class Game;

class HomedFrog : public SceneObject
{
public:
    //Constructora por lectura de archivo
    HomedFrog(Game* g, GameState* gs, PlayState* ps, std::istream& is, Point2D pos);
    // Frog(Game* game, const SDL_FRect& rect, Texture* tex = nullptr);
    virtual ~HomedFrog() = default;

    virtual void update() override;
    virtual void render() const override;
    bool getOcupado() const;
    Point2D getPos() const;
    void onOcupar();
    void setPosition(Point2D pos);
    virtual Collision checkCollision(const SDL_FRect& other) const override;


private:
    bool ocupado;        // si hay una rana
};