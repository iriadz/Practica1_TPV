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
#include "HomedFrog.h"
#include "Collision.h"
#include "InfoBar.h"
#include "Turtles.h"
#include "GameError.h"


using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/Original.txt";

uint64_t startTime, frameTime;

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
	{"turtle.png", 1, 7},
	//{"turtle.png"},
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
	for (SceneObject* so : sceneObjects) delete so;
	for (Texture* t : textures) delete t;
	delete infoBar;
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}


void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[1]->render(); // fondo

	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->render();
	frog->render();
	infoBar->setLives(frog->getLifes());
	infoBar->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->update(1.0f);
	frog->update(1.0f);
	infoBar->update(1.0f);
	if (frog->getLifes() <= -10) {
		exit = true;
	}


}

void
Game::run()
{
	while (!exit) { // Bucle principal del juego
		startTime = SDL_GetTicks();
		update();
		//manageWasps();
		handleEvents();
		render();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
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
		else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_0) confirmReset();
		frog->handleEvent(event);
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{

	Collision collision;
	collision.tipo = NONE;
	auto it = sceneObjects.begin();
	while (it != sceneObjects.end() && collision.tipo == NONE) {
		collision = (*it)->checkCollision(rect);
		it++;
	}
	return collision;
}

//Carga el mapa desde el archivo default, llamando a las constructoras correspondientes de cada elemento
void
Game::loadMap() {
	std::ifstream file; file.open(MAP_FILE);
	if (!file.is_open()) throw FileNotFoundError(name);

	char id;
	while (file >> id) {
		//if (id == '#') { file.ignore(11, '\n'); }
		line++;
		if (id == 'F') {
			frog = new Frog(this, file);
			sceneObjects.push_back(frog);
		}
		else if (id == 'V') { 
			sceneObjects.push_back(new Vehiculo(this, file));
		}
		else if (id == 'L') { 
			sceneObjects.push_back(new Log(this, file));
		}
		else if (id == 'T') {
			sceneObjects.push_back(new Turtles(this, file));
		}
		else if (id== '#')file.ignore('#', '\n');
		else  throw FileFormatError(name, line, "Error de lectura sobre el tipo de elemento");
		//else throw std::string("Formato erroneo");

	}
	
	Point2D pos(14, 22); // posicion del primer nenufar
	for (int i = 0; i < HOMED_NUM; i++) {
		sceneObjects.push_back(new HomedFrog(this));
		pos = pos + Point2D(96, 0); // va al siguiente nenufar
	}

	
	infoBar = new InfoBar(this);

	
}

//Carga los elementos en el mapa con valores dados por nosotros
void
Game::manageWasps() {
	//if (wasps.size() == 0) {
	//	int i = getRandomRange(0, 4);
	//	while (homedFrogs[i]->getOcupado()) {
	//		i = getRandomRange(0, 4);
	//	}
	//	Point2D p;
	//	p = p + homedFrogs[i]->getPos();
	//	sceneObjects.push_back(new Wasp(this, getRandomRange(1000, 3000))); // Crea una avispa en posicion aleatoria
	//																				  // con duracion aleatoria entre 1 y 3 secs
	//}
	//else if (wasps[0]->isAlive()) {
	//	delete wasps[0];
	//	wasps.pop_back();
	//}
}

void Game::addObject(SceneObject* obj) {
	sceneObjects.push_back(obj);
	// si es avispa, necesita su Anchor
	auto it = sceneObjects.end();
	--it;
	// intentaremos downcast seguro en tiempo de ejecución
	/*Wasp* w = dynamic_cast<Wasp*>(obj);
	if (w) w->setAnchor(it);*/
}


//void
//Game::waspUpdate() {
//	if (SDL_GetTicks() - waspSpawn >= nextWasp)
//	{
//		waspSpawn = SDL_GetTicks();
//		if (frog->getHomesReached() != Game::HOMED_NUM - 1)
//		{
//			// Genera nueva avispa
//			nextWasp = (float)getRandomRange(1000, 3000);
//			float lifeTime = (float)getRandomRange(1000, 3000);
//			bool encontrado = false;
//			int hf = getRandomRange(0, Game::HOMED_NUM - 1);
//
//			while (!encontrado)
//			{
//				if (!homeFrogsPos[hf].second) encontrado = true;
//				else {
//					hf++;
//					if (hf > Game::HOMED_NUM - 1) hf = 0;
//				}
//			}
//			Vector2D<float> pos = homeFrogsPos[hf].first;
//
//			pos = pos + Vector2D<float>(0, 4);
//			Vector2D<float> speed(0, 0);
//
//			sceneObjects.push_back(nullptr);  // reserva un hueco
//			It it = --sceneObjects.end();
//			*it = new Wasp(this, pos, lifeTime, speed);
//		}
//	}
//}

// Método para guardar los it de avispas a eliminar, para eliminar al terminar el update
//void
//Game::deleteAfter(It it) {
//
//	waspToDelete.push_back(it);
//}

//void
//Game::waspDelete()
//{
//	for (auto it : waspToDelete) {
//		delete* it;             // primero liberar memoria
//		sceneObjects.erase(it); // luego borrar de la lista
//	}
//	waspToDelete.clear();       // vaciar vector
//}

void
Game::reset() {
	for (SceneObject* s : sceneObjects) {
		delete s;
	}
	sceneObjects.clear();
	//delete frog;
	//delete infoBar;
	loadMap();
}

void
Game::confirmReset() {

	SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Aceptar" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancelar" }
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		"Quieres reiniciar la partida?",
		"Pulsa Aceptar para reiniciar la partida.",
		SDL_arraysize(buttons),
		buttons,
		NULL                          // Esquema de colores 
	};

	int buttonid = -1;

	// Mostrar la caja de mensaje
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
	if (buttonid == 1) {
		reset();
	}
}

//void
//Game::homeReached(Point2D<float> position) {
//	homeFrogsPos[position.getX() / POS_X_HOMEFROG].second = true;
//}
//
//int
//Game::getArchiveLine() {
//	return ArchiveLine;
//}