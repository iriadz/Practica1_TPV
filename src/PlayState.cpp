#include <stdexcept>
#include <SDL3/SDL.h>
#include <limits>

#include "PlayState.h"
#include "SceneObject.h"
#include "game.h"
#include "Frog.h"
#include "Collision.h"
#include "InfoBar.h"
#include "HomedFrog.h"
#include "Vehiculo.h"
#include "Log.h"
#include "Turtles.h"
#include "GameError.h"

PlayState::PlayState(Game* g, std::string fileName) : GameState(g) 
{
	loadMap(fileName);
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
}

void PlayState::render() const {
	GameState::render();
	Texture* fondo = game->getTexture(Game::BACKGROUND);
	fondo->render();
	for (auto so : sceneObjects) so->render();
	/*infoBar->setLives(frog->getLifes());
	infoBar->render();*/
}

void PlayState::handleEvent(const SDL_Event& e) {
	GameState::handleEvent(e);
}

void PlayState::loadMap(std::string fileName) {
	std::ifstream file; file.open(fileName);
	if (!file.is_open()) throw FileNotFoundError(fileName);

	GameState* gs = static_cast<GameState*>(this);

	homes.clear();

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
		else if (id == '#')file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else  throw FileFormatError(fileName, line, "Error de lectura sobre el tipo de elemento");
		//else throw std::string("Formato erroneo");

	}

	Point2D pos(14, 22); // posicion del primer nenufar
	homes.push_back({ pos, false });
	for (int i = 0; i < HOMED_NUM; i++) {
		HomedFrog* hf = new HomedFrog(game, gs, this, file, homes[i].first);
		sceneObjects.push_back(hf);

		pos = pos + Point2D(96, 0); // va al siguiente nenufar
		homes.push_back({ pos, false });
	}

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
	return collision;
}