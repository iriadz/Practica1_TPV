#include <stdexcept>
#include <SDL3/SDL.h>
#include <limits>

#include "PlayState.h"
#include "SceneObject.h"
#include "PauseState.h"
#include "game.h"
#include "Frog.h"
#include "Wasp.h"
#include "Collision.h"
#include "InfoBar.h"

#include "HomedFrog.h"
#include "Vehiculo.h"
#include "Log.h"
#include "Turtles.h"
#include "GameError.h"
#include "EndState.h"

PlayState::PlayState(Game* g, std::string fileName) : GameState(g) 
{
	loadMap(fileName);
	file = fileName;
}

PlayState::~PlayState() {
	delete infobar;
}


void PlayState::update() {
    // update game objects
    GameState::update();
    // update scene objects separately if needed
	if (frog->getLifes() <= 0) game->exitGame();
	infobar->update();

	int i = 0;
	while (i<homesList.size() && homesList[i]->getOcupado()) {
		i++;
	}
	if (i == homesList.size()) game->swapState(new EndState(game, true));
}

void PlayState::render() const {
	GameState::render();
	Texture* fondo = game->getTexture(Game::BACKGROUND);
	fondo->render();
	for (auto so : sceneObjects) so->render();
	PlayState::infobar->setLives(frog->getLifes());
	PlayState::infobar->render();
}

void PlayState::handleEvent(const SDL_Event& e) {
	GameState::handleEvent(e);
	// if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_0) reiniciarMsg();
	if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_P)game->pushState(new PauseState (game));
		 return;
}

void PlayState::loadMap(std::string fileName) {
	std::ifstream file; file.open(fileName);
	if (!file.is_open()) throw FileNotFoundError(fileName);

	GameState* gs = static_cast<GameState*>(this);

	homesList.clear();

	char id;
	int line = 0;
	while (file >> id) {
		//if (id == '#') { file.ignore(11, '\n'); }
		line++;
		if (id == 'F') {
			frog = new Frog(game, gs, this, file);
			sceneObjects.push_back(frog);
			addEventListener(frog);
		}
		else if (id == 'V') {
			sceneObjects.push_back(new Vehiculo(game, gs, this, file));
		}
		else if (id == 'L') {
			sceneObjects.push_back(new Log(game, gs, this, file));
		}
		else if (id == 'T') {
			sceneObjects.push_back(new Turtles(game, gs, this, file));
		}
		else if (id == 'W') {
			sceneObjects.push_back(new Wasp(game, gs, this, file));
		}
		else if (id == '#')file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else  throw FileFormatError(fileName, line, "Error de lectura sobre el tipo de elemento");
		//else throw std::string("Formato erroneo");

	}

	Point2D pos(14, 22); // posicion del primer nenufar
	for (int i = 0; i < HOMED_NUM; i++) {
		HomedFrog* hf = new HomedFrog(game, gs, this, file, pos);
		sceneObjects.push_back(hf);
		homesList.push_back(hf);

		pos = pos + Point2D(96, 0); // va al siguiente nenufar
	}

	setSceneObjectList(sceneObjects);

	infobar = new InfoBar(game, gs);
}


void PlayState::addSceneObject(SceneObject* so) {
    sceneObjects.push_back(so);
    addObject(so);
}

void PlayState::setSceneObjectList(std::list<SceneObject*> so) {
    sceneObjects = so;
    for (auto i : so) {
        addObject(i);
    }
}

void PlayState::removeSceneObject(SceneObject* so) {
    sceneObjects.remove(so);
    removeObject(so);
}

Collision 
PlayState::checkCollision(const SDL_FRect& rect) const {
	Collision collision;
	collision.tipo = NONE;
	auto it = sceneObjects.begin();
	while (it != sceneObjects.end() && collision.tipo == NONE) {
		collision = (*it)->checkCollision(rect);
		it++;
	}
	if (collision.tipo == HOME) {
		it--;
		SceneObject* obj = *it;

		if (auto homed = dynamic_cast<HomedFrog*>(obj)) {
			homed->onOcupar();
		}
	}
	return collision;
	//return Collision(NONE, Vector2D<float>(0, 0));
}

//Reinicia la partida
void
PlayState::reiniciar() {
	for (SceneObject* s : sceneObjects) {
		delete s;
	}
	sceneObjects.clear();
	homesList.clear();
	delete PlayState::infobar;
	//loadMap(file);
	game->pushState(new PlayState(game, file));
}

//Muestra una ventana con dos botones para confirmar si se quiere reiniciar la partida
void
PlayState::reiniciarMsg() {
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
PlayState::manageWasps() {
	
}
