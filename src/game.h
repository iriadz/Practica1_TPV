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
#include <map>

#include "Vector2D.h"
#include "gameStateMachine.h"
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

class Game : private GameStateMachine
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr float FRAME_RATE = 30;
	static constexpr float DT = FRAME_RATE /1000;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río LO HE AJUSTADO
	//static constexpr int RIVER_LOW = 210;
	static constexpr int RIVER_LOW = 200;
	
	static constexpr char MAP_PATH[] = "../assets/maps/Original.txt";

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
		CONTINUAR,
		ELIGE_UN_MAPA,
		VOLVER_AL_MENU,
		ORIGINAL,
		PRACTICA_1,
		TRIVIAL,
		VELOZ,
		AVISPADO,
		REINICIAR,
		GAME_OVER,
		HAS_GANADO,
		SALIR,
		LEFT,
		RIGHT,
		MENUBACKGROUND,
		NUM_TEXTURES
	};


public:


	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	void manageWasps();
	void loadMap();
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

	Frog* frog;
	InfoBar* infoBar;

	//Generador numeros aleatorios
	std::mt19937 generator;

	//Metodos game
	void render() const;
	void update();
	void handleEvents();
	//Reiniciar partida
	void reiniciar();
	//Mensaje reinicio
	void reiniciarMsg();
	// Ha alcanzado una casa
	void homeReached(Point2D pos);
	void waspsDelete();

	bool exit;
	int line; 
	std::string name = "../assets/maps/Original.txt";
	std::list<SceneObject*> sceneObjects;
	std::list<It> m_toDelete; // it a borrar al final de update
	std::list<It> waspsDel; // avistpas a borrar al final del update
	int numTotalObjects;
	float waspsSpawn = 3;
	int lifeTime = 0;
	bool waspAlive = false;
	/*std::vector<int>homedFrogs;*/
	int homedfrogs;
	
	std::vector<std::pair<Point2D, bool>> homes;// par con las posiciones de las casas y si estan ocupadas
	
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
