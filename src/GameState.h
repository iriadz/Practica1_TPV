#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include
class GameState
{
private:
	std::list<GameObject*> objects;
	std::list<EventHandler*> events;
	std::list<DelayedCallback> 
	Game* game;
};

