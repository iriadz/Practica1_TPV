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
	loadElems();

	//loadMap();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Game::~Game()
{
	for (Vehiculo* c : coches) delete c;
	for (Log* t : troncos) delete t;
	delete frog;
	for (Wasp* w : wasps) delete w;
   //DESTRUIR TEXTURAS
}


void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[1]->render(); // fondo

	for (int i = 0; i < coches.size(); i++) coches[i]->render();

	for (int i = 0; i < troncos.size(); i++) troncos[i]->render();

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
		handleEvents();
		render();
		if (frog->getLifes() <= 0) {
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
	int i = 0; int j = 0;
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
		if (id == 'F') frog = new Frog(this, file, textures[0]);
	//	else if (id == 'V') coches.push_back(new Vehiculo(this, file));
	//	else if (id == 'L') troncos.push_back(new Log(this, file));
		else file.ignore('#', '\n');
		//else throw std::string("Formato erroneo");

	}
}

//Carga los elementos en el mapa con valores dados por nosotros
void
Game::loadElems() {

	
	//for (int i = 0; i < CAR_NUM; i++) // Cargar coches
	//{
	//	if (i % 2 == 0)coches[i] = new Vehiculo(this, getTexture(static_cast<TextureName>(i + 2)), Point2D(410, 372 - (i * 30)), Vector2D<float>(-6, 0));
	//	else coches[i] = new Vehiculo(this, getTexture(static_cast<TextureName>(i + 2)), Point2D(0, 372 - (i * 30)), Vector2D<float>(6, 0));
	//}
	coches[0] = new Vehiculo(this, getTexture(static_cast<TextureName>(2)), Point2D(50, 372), Vector2D<float>(-48, 0));
	coches [1] = new Vehiculo(this, getTexture(static_cast<TextureName>(2)), Point2D(200, 372), Vector2D<float>(-48, 0));
	coches[2] = new Vehiculo(this, getTexture(static_cast<TextureName>(2)), Point2D(350, 372), Vector2D<float>(-48, 0));
	coches[3] = new Vehiculo(this, getTexture(static_cast<TextureName>(3)), Point2D(25, 342), Vector2D<float>(48, 0));
	coches[4] = new Vehiculo(this, getTexture(static_cast<TextureName>(3)), Point2D(175, 342), Vector2D<float>(48, 0));
	coches[5] = new Vehiculo(this, getTexture(static_cast<TextureName>(3)), Point2D(325, 342), Vector2D<float>(48, 0));
	coches[6] = new Vehiculo(this, getTexture(static_cast<TextureName>(4)), Point2D(175, 312), Vector2D<float>(-72, 0));
	coches[7] = new Vehiculo(this, getTexture(static_cast<TextureName>(4)), Point2D(325, 312), Vector2D<float>(-72, 0));
	coches[8] = new Vehiculo(this, getTexture(static_cast<TextureName>(4)), Point2D(475, 312), Vector2D<float>(-72, 0));
	coches[9] = new Vehiculo(this, getTexture(static_cast<TextureName>(5)), Point2D(150, 280), Vector2D<float>(48, 0));
	coches[10] = new Vehiculo(this, getTexture(static_cast<TextureName>(5)), Point2D(0, 280), Vector2D<float>(48, 0));
	coches[11] = new Vehiculo(this, getTexture(static_cast<TextureName>(5)), Point2D(-150, 280), Vector2D<float>(48, 0));
	coches[12] = new Vehiculo(this, getTexture(static_cast<TextureName>(6)), Point2D(165, 252), Vector2D<float>(-72, 0));
	coches[13] = new Vehiculo(this, getTexture(static_cast<TextureName>(6)), Point2D(365, 252), Vector2D<float>(-72, 0));


	//Carga rana
	Point2D iniPos(205, 402);
	frog = new Frog(this, textures[0], iniPos);

	troncos[0] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(-100, 60), Vector2D<float>(72.6, 0));
	troncos[1] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(75, 60), Vector2D<float>(72.6, 0));
	troncos[2] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(250, 60), Vector2D<float>(72.6, 0));
	troncos[3] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(425, 60), Vector2D<float>(72.6, 0));
	troncos[4] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(370, 121), Vector2D<float>(96, 0));
	troncos[5] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(460, 121), Vector2D<float>(96, 0));
	troncos[6] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(120, 121), Vector2D<float>(96, 0));
	troncos[7] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(210, 121), Vector2D<float>(96, 0));
	troncos[8] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(-130, 121), Vector2D<float>(96, 0));
	troncos[9] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(-40, 121), Vector2D<float>(96, 0));
	troncos[10] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(30, 153), Vector2D<float>(48, 0));
	troncos[11] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(180, 153), Vector2D<float>(48, 0));
	troncos[12] = new Log(this, getTexture(static_cast<TextureName>(7)), Point2D(330, 153), Vector2D<float>(48, 0));

	troncos[13] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(0, 185), Vector2D<float>(48, 0));
	troncos[14] = new Log(this, getTexture(static_cast<TextureName>(8)), Point2D(0, 90), Vector2D<float>(48, 0));
	//for (int i = 0; i < LOG_NUM; i++) //Cargar tronco5
	//{
	//	if (i % 2 == 0)troncos[i] = new Log(this, getTexture(LOG1), Point2D(410, 180 - (i * 30)), Vector2D<float>(-6, 0));
	//	else troncos[i] = new Log(this, getTexture(LOG2), Point2D(410, 170 - (i * 30)), Vector2D<float>(-6, 0));
	//}

	

}