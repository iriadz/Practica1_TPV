#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
class GameState
{
private:
	std::list<GameObject*> objects;
	std::list<EventHandler*> events;
	Game* game;
};

