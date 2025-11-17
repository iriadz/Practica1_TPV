#include "InfoBar.h"

InfoBar::InfoBar(Texture* t, int n) : textura(t), numVidas(n)
{

}

void InfoBar::render(int lives)
{
	for (int i = 0; i < lives; i++)
	{
		SDL_FRect rana = {10 + (i * 30),440 , textura->getFrameWidth(), textura->getFrameHeight()};
		textura->renderFrame(rana, 0, 0);
	}
}