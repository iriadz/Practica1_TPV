#include "InfoBar.h"

InfoBar::InfoBar(Game* g): GameObject(g), numVidas(3)
{
	textura = g->getTexture(g->FROG);
}

void InfoBar::render() const
{
	for (int i = 0; i < numVidas; i++)
	{
		SDL_FRect rana = {10 + (i * 30),440 , textura->getFrameWidth(), textura->getFrameHeight()};
		textura->renderFrame(rana, 0, 0);
	}
}

void InfoBar::update(float dt)
{

}

void InfoBar::setLives(int n)
{
	numVidas = n;
}