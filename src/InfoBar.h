#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
class InfoBar: public GameObject
{
public: 
	//InfoBar(Texture* t, int n);
	
	InfoBar(Game* g);
	void render() const override;
	void update(float dt) override {};

	void setLives(int n);

private:
	Texture* textura;
	int numVidas;
};

