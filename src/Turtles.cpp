#include "Turtles.h"
#include "Collision.h"

//Turtles::Turtles(Game* g, const SDL_FRect& rect, Vector2D<float> vx, Texture* tex): Platform(g, rect, vx.getX(), tex), m_sinkingPeriod(SDL_GetTicks()), estado(0)
//{
//}
Turtles::Turtles(Game* g, std::istream& is): Platform(g), m_sinkingPeriod(SDL_GetTicks()), estado(0)
{
	int x, y, tipo; float vel;
	is >> x >> y >> vel >> tipo;
	posicion = Point2D((int)x, (int)y);
	//velocidad = Vector2D<float>(vel, 0);ç
	velocidad = Vector2D<float>(vel, 0);
}


Turtles::~Turtles() {}

void Turtles::update(float dt){

	Platform::update(dt);


	if (SDL_GetTicks() >= m_sinkingPeriod + 400)
	{
		if (estado != 6) estado++;
		else estado = 0; 
		m_sinkingPeriod = SDL_GetTicks();
	}
}

void Turtles::render() const
{
	
	for (int i = 0; i < 5; i++)
	{
		SDL_FRect tronco = { posicion.getX() + (i * 31),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
		textura->renderFrame(tronco, 0, estado);
	}
}



Collision Turtles::checkCollision(const SDL_FRect& ref) const
{
	Texture* tex = game->getTexture(game->LOG2);
	SDL_FRect log = { posicion.getX(),posicion.getY(), tex->getFrameWidth(), tex->getFrameHeight() };
	
	if (SDL_HasRectIntersectionFloat(&ref, &log) && estado != 5) {
		return Collision(PLATFORM, Vector2D<float>(velocidad.getX(), 0));
		
	}

	return Collision(ENEMY, Vector2D<float>(0, 0));

}



