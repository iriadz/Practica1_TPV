#pragma once

#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
#include "GameObject.h"
#include "game.h"

class InfoBar: public GameObject
{
public: 
	//InfoBar(Texture* t, int n);
	
	InfoBar(Game* g, GameState* gs);
	void render() const override;
	void update() override;

	void setLives(int n);

private:
	Texture* textura;
	int numVidas;
};

