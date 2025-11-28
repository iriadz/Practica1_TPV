#pragma once
#include <list>
#include <functional>
#include "GameObject.h"
#include "EventHandler.h"
class GameState
{
public:
	GameState(Game* g):
		game(g)
	{ }
	virtual void update();
	virtual void render() const;
	virtual void handleEvent();
private:
	std::list<GameObject*> objects;
	std::list<EventHandler*> events;
	std::list<DelayedCallBack> callBacks;
	Game* game;
};

using DelayedCallBack = std::function<void()>;