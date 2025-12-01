#include "Turtles.h"
#include "Collision.h"

//Turtles::Turtles(Game* g, const SDL_FRect& rect, Vector2D<float> vx, Texture* tex): Platform(g, rect, vx.getX(), tex), m_sinkingPeriod(SDL_GetTicks()), estado(0)
//{
//}
Turtles::Turtles(Game* g, GameState* gs, PlayState* ps, std::istream& is): Platform(g, gs, ps, is), m_sinkingPeriod(SDL_GetTicks()), estado(0)
{
	int num, hun; float vel;
	is >> vel >> num >> hun;
	
	n = num;
	hundir = hun;
	velocidad = Vector2D<float>(vel, 0);
	textura = g->getTexture(g->TURTLE);
}


Turtles::~Turtles() {}

void Turtles::update(){
	Platform::update();

	if (hundir == 1 && SDL_GetTicks() >= m_sinkingPeriod + 400)
	{
		if (estado != 6) estado++;
		else estado = 0; 
		m_sinkingPeriod = SDL_GetTicks();
	}
}

void Turtles::render() const
{
	
	for (int i = 0; i < n; i++)
	{
		SDL_FRect tronco = { posicion.getX() + (i * 31),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
		textura->renderFrame(tronco, 0, estado);
	}
}



Collision Turtles::checkCollision(const SDL_FRect& ref) const
{
	Texture* tex = game->getTexture(game->TURTLE);
	SDL_FRect log = { posicion.getX(),posicion.getY(), tex->getFrameWidth() * n, tex->getFrameHeight()};
	
	if (SDL_HasRectIntersectionFloat(&ref, &log) && estado != 5) {
		return Collision(PLATFORM, Vector2D<float>(velocidad.getX(), 0));
	}

	return Collision(NONE, Vector2D<float>(0, 0));

}



