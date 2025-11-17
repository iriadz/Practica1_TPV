#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
#include "Platform.h"


class Game;

class Turtles : public Platform
{
public:
	Turtles(Game* game, const SDL_FRect& rect, Vector2D<float> vx, Texture* tex = nullptr);
	virtual ~Turtles();
	//Constructora por lectura de archivo
	Turtles(Game* j, std::istream& in);
	virtual void update(float dt) override;
	virtual void render(SDL_Renderer* renderer) const override;

	bool isSunk() const { return estado==5; }
	virtual Collision checkCollision(const SDL_FRect& ref) const override;

private:
	int estado;
	float m_sinkingPeriod;
};
