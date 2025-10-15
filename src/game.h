#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include "Vehiculo.h"
#include "Log.h"
#include "Frog.h"
#include "HomedFrog.h"
#include "Collision.h"

// Declaraciones anticipadas
class Texture;
class Vehiculo;
class Log;
class Frog;
class HomedFrog;
class Collision;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río
	//static constexpr int RIVER_LOW = 210;
	static constexpr int RIVER_LOW = 180;
	static constexpr int RIVER_HIGH = 50;
	//Coches. Ahora mismo esta a 5 (uno de cada) pero tienen q ser mas 
	static constexpr int CAR_NUM = 5;
	static constexpr int LOG_NUM = 4;
	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		LOG1,
		LOG2,
		TURTLE,
		WASP,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	std::array<Vehiculo*, CAR_NUM> coches;
	std::array<Log*, LOG_NUM> troncos;
	//Vehiculo* v1; 
	Frog* frog;
	HomedFrog* homedFrog;

	void render() const;
	void update();
	void handleEvents();

	bool exit;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision::Type checkCollision(const SDL_FRect& rect) const;
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
