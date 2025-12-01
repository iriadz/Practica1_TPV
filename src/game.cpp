#include "game.h"
#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Vehiculo.h"
#include "Vector2D.h"
#include "Wasp.h"
#include "Log.h"
#include "Frog.h"
#include "HomedFrog.h"
#include "Collision.h"
#include "InfoBar.h"
#include "Turtles.h"
#include "GameError.h"
#include "GameState.h"
#include "PlayState.h"
#include "MainMenuState.h"

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
	{"wasp.png"},
	{"CONTINUAR.png"},		// textureList[11] 
	{"ELIGE_UN_MAPA.png"},
	{"VOLVER_AL_MENU.png"},
	{"Original.png"},
	{"Practica_1.png"},
	{"Trivial.png"},
	{"Veloz.png"},
	{"Avispado.png"},
	{"REINICIAR.png"},
	{"GAME_OVER.png"},
	{"HAS_GANADO.png"},
	{"SALIR.png"},
	{"left.png"},
	{"right.png"},
	{"menuBackground.png"}
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

	pushState(std::make_shared<MainMenuState>(this));


	//Cargar elementos -> rana, coches, troncos y avispas por archivo o a mano
	//loadElems();

	//loadMap();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Game::~Game()
{
//	for (auto p: homes) delete begin();
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

	//textures[1]->render(); // fondo

	//for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->render();
	////frog->render();
	//infoBar->setLives(frog->getLifes());
	//infoBar->render();

	GameStateMachine::render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	//for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->update();
	//infoBar->update();
	//manageWasps();
	//if (frog->getLifes() <= 0) {
	//	exit = true;
	//}
	//waspsDelete();

	GameStateMachine::update();
}

void
Game::run()
{
	while (!exit) { // Bucle principal del juego
		startTime = SDL_GetTicks();
		update();
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

	//// Only quit is handled directly, everything else is delegated
	//while (SDL_PollEvent(&event)) {
	//	if (event.type == SDL_EVENT_QUIT)
	//		exit = true;

	//	// TODO
	//	else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_0) reiniciarMsg();
	//	frog->handleEvent(event);
	//}

	GameStateMachine::handleEvent(event);
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

	PlayState* ps = getCurrentState<PlayState>();
    GameState* gs = ps;

	char id;
	while (file >> id) {
		//if (id == '#') { file.ignore(11, '\n'); }
		line++;
		if (id == 'F') {
			frog = new Frog(this, gs, ps, file);
			sceneObjects.push_back(frog);
		}
		else if (id == 'V') { 
			sceneObjects.push_back(new Vehiculo(this, gs, ps, file));
		}
		else if (id == 'L') { 
			sceneObjects.push_back(new Log(this, gs, ps, file));
		}
		else if (id == 'T') {
			sceneObjects.push_back(new Turtles(this, gs, ps, file));
		}
		else if (id== '#')file.ignore('#', '\n');
		else  throw FileFormatError(name, line, "Error de lectura sobre el tipo de elemento");
		//else throw std::string("Formato erroneo");

	}
	
	Point2D pos(14, 22); // posicion del primer nenufar
	homes.push_back({ pos, false });
	for (int i = 0; i < HOMED_NUM; i++) {
		HomedFrog* hf = new HomedFrog(this, gs, ps, file, homes[i].first);
		sceneObjects.push_back(hf);
		
		pos = pos + Point2D(96, 0); // va al siguiente nenufar
		homes.push_back({ pos, false });
	}

	ps->setSceneObjectList(sceneObjects);

	infoBar = new InfoBar(this, gs);
}

//Carga los elementos en el mapa con valores dados por nosotros
void
Game::manageWasps() {
	/*if (!waspAlive)
	{
		waspsSpawn = SDL_GetTicks();
		
		lifeTime = getRandomRange(1000, 3000);
		int home = getRandomRange(0, Game::HOMED_NUM - 1);
		while (homes[home].second)
		{
			home = getRandomRange(0, Game::HOMED_NUM - 1);
		}
		Point2D pos = homes[home].first;
		pos = pos + Point2D(0, 4);

		Wasp* w = new Wasp(this, lifeTime, waspsSpawn, pos);
		sceneObjects.push_back(w);
		
		waspAlive = true;
	}*/

}


void
Game::deleteAfter(It it) {
	waspsDel.push_back(it);
}

void
Game::waspsDelete()
{
	for (auto it : waspsDel) {
		delete (*it);             
		sceneObjects.erase(it);
		waspAlive = false;
	}
	waspsDel.clear();
}

//Reinicia la partida
void
Game::reiniciar() {
	for (SceneObject* s : sceneObjects) {
		delete s;
	}
	sceneObjects.clear();
	delete infoBar;
	loadMap();
}

//Muestra una ventana con dos botones para confirmar si se quiere reiniciar la partida
void
Game::reiniciarMsg() {

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
		NULL                         
	};

	int buttonid = -1;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
	if (buttonid == 1) {
		reiniciar();
	}
}

void
Game::homeReached(Point2D position) {
	homes[position.getX() / 14].second = true;
}