#pragma once
#include <list>
#include <functional>
#include "GameObject.h"
#include "EventHandler.h"

using DelayedCallBack = std::function<void()>;

class Game;
class GameObject;

class GameState
{
public:

	GameState(Game* g):
		game(g)
	{ }

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(const SDL_Event& e);

	//getters
	Game* getGame() const { return game; }
	const GameState* getGameState() const { return this; }

	//manejar lista de gameObjects
	void addObject(GameObject* obj);
	void removeObject(GameObject* obj);

	//manejar eventos
	void addEventListener(EventHandler* h);
	void removeEventListener(EventHandler* h);

	//callbacks
	void runLater(DelayedCallBack cb);


private:
	//coleccion de objetos del juego
	std::list<GameObject*> gameObjects;
	//manejador de eventos
	std::list<EventHandler*> events;
	//callbacks pendientes
	std::list<DelayedCallBack> callBacks;
	Game* game;
};




