#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <list>


// Declaraciones anticipadas
class Texture;
class Vehiculo;
class Log;
class Frog;
class HomedFrog;
class Collision;
class Wasp;
class InfoBar;
class Turtles;
class SceneObject;


using It = std::list<SceneObject*>::iterator;

class Game
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río LO HE AJUSTADO
	//static constexpr int RIVER_LOW = 210;
	static constexpr int RIVER_LOW = 200;
	
	static constexpr char MAP_PATH[] = "../assets/maps/default.txt";

	//QUITAR LEER ARCHIVOS
	//Coches. Ahora mismo esta a 5 (uno de cada) pero tienen q ser mas 
	static constexpr int CAR_NUM = 14;
	static constexpr int LOG_NUM = 15;
	static constexpr int HOMED_NUM = 5;
	static constexpr int WASP_NUM = 1;
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


public:
	std::list<SceneObject*> sceneObjects;

	
	

	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	

	void manageWasps();
	void loadMap();
	void addObject(SceneObject* obj);
	void deleteAfter(It a); // llamado por un objeto al morir

	// Ejecuta el bucle principal del juego
	void run();

	int getRandomRange(int min, int max);

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;



	// Elementos del juego
	std::vector<Vehiculo*> coches;
	std::vector<Log*> troncos;
	Frog* frog;
	std::vector<HomedFrog*> homedFrogs;
	std::vector<Wasp*> wasps;
	InfoBar* infoBar;
	std::vector<Turtles*> tortugas;

	//Generador numeros aleatorios
	std::mt19937 generator;

	//Metodos game
	void render() const;
	void update();
	void handleEvents();

	bool exit;

	std::list<It> m_toDelete; // anchors a borrar al final de update

};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
