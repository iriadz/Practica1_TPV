#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Collision.h"
class InfoBar
{
public: 
	InfoBar(Texture* t, int n);
	

	void render(int lives);

private:
	Texture* textura;
	int numVidas;
};

