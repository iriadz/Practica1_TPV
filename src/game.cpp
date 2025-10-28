#include "game.h"
#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Vehiculo.h"
#include "vector2D.h"
#include "Wasp.h"
#include "Log.h"
#include "Frog.h"
#include "Collision.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2}, // parte a la mitad la imagen a lo largo
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 6},
	{"wasp.png"},

};

Game::Game()
	: exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();


	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	//Cargar elementos -> rana, coches, troncos y avispas por archivo o a mano
	//loadElems();

	loadMap();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Game::~Game()
{
	delete frog;
	for (Texture* tex : textures) {
		delete tex;   // Libera las texturas
	}
	for (Vehiculo* c : coches) {
		delete c;   // Libera los coches
	}
	for (Log* t : troncos) {
		delete t;   // Libera los troncos
	}
	for (HomedFrog* h : homedFrogs) {
		delete h;   // Libera las ranas salvadas
	}
	for (Wasp* w : wasps) {
		delete w;   // Libera las avispas
	}
}


void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[1]->render(); // fondo

	for (int i = 0; i < coches.size(); i++) coches[i]->render();

	for (int i = 0; i < troncos.size(); i++) troncos[i]->render();

	for (int i = 0; i < homedFrogs.size(); i++) if (homedFrogs[i]->getOcupado()) { homedFrogs[i]->render(); }

	for (int i = 0; i < wasps.size(); i++) wasps[i]->render();

	frog->render();


	/*for (int i = 0; i < wasps.size(); i++) wasps[i]->render();*/

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (int i = 0; i < coches.size(); i++) coches[i]->update();

	for (int i = 0; i < troncos.size(); i++) troncos[i]->update();

	frog->update();

	//for (int i = 0; i < wasps.size(); i++)
	//{
	//	wasps[i]->update();
	//	if (!wasps[i]->isAlive()) delete wasps[i]; // Borrar de la memoria las avispas muertas
	//}

}

void
Game::run()
{
	while (!exit) { // Bucle principal del juego
		update();
		loadElems();
		handleEvents();
		render();
		if (frog->getLifes() <= 0) {
			exit = true;
		}
		int i = 0;
		while (i < HOMED_NUM - 1 && !homedFrogs[i]->getOcupado()) {
			i++;
		}
		if (homedFrogs[i]->getOcupado() && i == HOMED_NUM - 1) {
			exit = true;
		}
		SDL_Delay(30);
	}
}

int
Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(generator);
}


void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
		frog->handleEvent(event);
	}
}

Collision::Type
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	int i = 0, j = 0, k = 0;
	while (!coches[i]->checkCollision(rect) && i < CAR_NUM - 1) {
		i++;
	}
	if (coches[i]->checkCollision(rect)) {
		return Collision::Type::ENEMY;
	}

	while (!troncos[j]->checkCollision(rect) && j < LOG_NUM - 1) {
		j++;
	}
	if (troncos[j]->checkCollision(rect)) {
		return Collision::Type::PLATFORM;
	}
	while (!homedFrogs[k]->checkCollision(rect) && k < HOMED_NUM - 1) {
		k++;
	}
	if (homedFrogs[k]->checkCollision(rect)) {
		if (!homedFrogs[k]->getOcupado() && !wasps[0]->checkCollision(rect)) {
			homedFrogs[k]->onOcupar();
			return Collision::Type::HOME;
		}
		return Collision::Type::ENEMY;
	}
	return Collision::Type::NONE;
}

//Carga el mapa desde el archivo default, llamando a las constructoras correspondientes de cada elemento
void
Game::loadMap() {
	std::ifstream file; file.open(MAP_FILE);
	if (!file.is_open())
		throw std::string("No se encuentra el mapa: ");

	char id;
	while (file >> id) {
		//if (id == '#') { file.ignore(11, '\n'); }
		if (id == 'F') frog = new Frog(this, file);
		else if (id == 'V') coches.push_back(new Vehiculo(this, file));
		else if (id == 'L') troncos.push_back(new Log(this, file));
		else file.ignore('#', '\n');
		//else throw std::string("Formato erroneo");

	}
	
	Point2D pos(14, 22); // posicion del primer nenufar
	for (int i = 0; i < HOMED_NUM; i++) {
		homedFrogs.push_back(new HomedFrog(this, textures[0], pos));
		pos = pos + Point2D(96, 0); // va al siguiente nenufar
	}
}

//Carga los elementos en el mapa con valores dados por nosotros
void
Game::loadElems() {
	if (wasps.size() == 0) {
		int i = getRandomRange(0, 4);
		while (homedFrogs[i]->getOcupado()) {
			i = getRandomRange(0, 4);
		}
		Point2D p;
		p = p + homedFrogs[i]->getPos();
		wasps.push_back(new Wasp(this, textures[10], p, getRandomRange(1000, 3000))); // Crea una avispa en posicion aleatoria
																					  // con duracion aleatoria entre 1 y 3 secs
	}
	else if (wasps[0]->isAlive()) {
		delete wasps[0];
		wasps.pop_back();
	}
}