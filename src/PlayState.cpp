#include <stdexcept>
#include <SDL3/SDL.h>

#include "PlayState.h"
#include "SceneObject.h"
#include "Game.h"
#include "Frog.h"
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


void PlayState::update() {
    // update game objects
    GameState::update();
    // update scene objects separately if needed
    for (auto so : sceneObjects) so->update();
}

void PlayState::render() const {
    GameState::render();
    for (auto so : sceneObjects) so->render();
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
		else if (id == '#')file.ignore('#', '\n');
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
    for (auto so : sceneObjects) {
        Collision col = so->checkCollision(rect);  // col para cada objeto

        if (col.tipo != NONE) {
            // encontramos una colisión, la devolvemos inmediatamente
            return col;
        }
    }

    // Si ningún objeto colisiona
    return Collision(NONE, Vector2D<float>(0, 0));
}